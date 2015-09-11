#include "CSound.h"

#pragma comment(lib,"winmm")


CSoundBase::CSoundBase():m_pSourceVoice(NULL){
	
}
CSoundBase::~CSoundBase(){
	Release();
}
bool CSoundBase::load(char* path,int layer)
{
	if(m_pSourceVoice) {
		Release();
	}
	m_layer = layer;
	m_current = 0;
	m_pSourceVoice = new IXAudio2SourceVoice*[layer];
		HMMIO hMmio=NULL;//WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
		DWORD dwWavSize=0;//WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
		WAVEFORMATEX* pwfex;//WAVのフォーマット 例）16ビット、44100Hz、ステレオなど
		MMCKINFO ckInfo;//　チャンク情報
		MMCKINFO riffckInfo;// 最上部チャンク（RIFFチャンク）保存用
		PCMWAVEFORMAT pcmWaveForm;
		//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
		hMmio=mmioOpenA(path, NULL, MMIO_ALLOCBUF | MMIO_READ);
		if(!hMmio) {
			printf("%sの読み込みに失敗しました\n",path);
		}
		//ファイルポインタをRIFFチャンクの先頭にセットする
		mmioDescend( hMmio, &riffckInfo, NULL, 0 );
		// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
		ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );
		//フォーマットを読み込む
		mmioRead( hMmio, (HPSTR) &pcmWaveForm,sizeof(pcmWaveForm));
		pwfex = (WAVEFORMATEX*)new CHAR[ sizeof(WAVEFORMATEX) ];
		memcpy( pwfex, &pcmWaveForm, sizeof(pcmWaveForm) );
		pwfex->cbSize = 0;	
		mmioAscend( hMmio, &ckInfo, 0 );
		// WAVファイル内の音データの読み込み	
		ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//データチャンクにセット
		dwWavSize = ckInfo.cksize;
		m_pWavBuffer=new BYTE[ dwWavSize ];
		DWORD dwOffset=ckInfo.dwDataOffset;
		mmioRead( hMmio, (HPSTR)m_pWavBuffer,dwWavSize);
		m_dwWavSize=dwWavSize;

		for(int i=0;i<m_layer;i++) {
			//ソースボイスにデータを詰め込む	
			if(FAILED(CSound::getSound()->m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i],pwfex)))
			{
				printf("ソースボイス作成失敗\n");
				return FALSE;
			}
		}
		delete[] pwfex;
	return TRUE;
}

void CSoundBase::Release()
{
	if(!m_pSourceVoice) return;
	for(int i=0;i<m_layer;i++) {
		m_pSourceVoice[i]->DestroyVoice();
	}

	delete[] m_pSourceVoice;
	delete[] m_pWavBuffer;

}
int CSoundBase::play(bool boLoop ){
	XAUDIO2_BUFFER buffer={0};
	buffer.pAudioData=m_pWavBuffer;
	buffer.Flags=XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes=m_dwWavSize;
	if(boLoop)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	if(FAILED(m_pSourceVoice[m_current]->SubmitSourceBuffer(&buffer)))
	{
		printf("ソースボイスにサブミット失敗\n");
		return -1;
	}
	int c=m_current;
	m_pSourceVoice[m_current]->Start(0,XAUDIO2_COMMIT_NOW);
	printf("play %d\n",m_current);
	m_current = (m_current+1) % m_layer;

	return c;

}
void CSoundBase::stop(int layer){
	if(layer == -1) {
		for(int i=0;i<m_layer;i++) {
			m_pSourceVoice[i]->Stop(0,XAUDIO2_COMMIT_NOW);
			m_pSourceVoice[i]->FlushSourceBuffers();
		}
	} else {
		m_pSourceVoice[layer]->Stop(0,XAUDIO2_COMMIT_NOW);
		m_pSourceVoice[layer]->FlushSourceBuffers();
	}
}
void CSoundBase::pause(int layer){
	if(layer == -1) {
		for(int i=0;i<m_layer;i++) {
			m_pSourceVoice[i]->Stop(0,XAUDIO2_COMMIT_NOW);
		}
	} else {
		m_pSourceVoice[layer]->Stop(0,XAUDIO2_COMMIT_NOW);
	}
}

CSound*	CSound::m_sound = NULL;

bool CSound::create(int max){
	m_sound = new CSound();
	CoInitializeEx(NULL,COINIT_MULTITHREADED);	

	if(FAILED(XAudio2Create(&m_sound->m_pXAudio2)))
	{
		CoUninitialize();
		return FALSE;
	}
	if( FAILED(m_sound->m_pXAudio2->CreateMasteringVoice(&m_sound->m_pMasteringVoice)))
	{
		CoUninitialize();	
		return FALSE;
	}
	m_sound->m_core = new CSoundBase[max];
	return TRUE;

}
int CSound::play(int no,bool boLoop){
	return m_core[no].play(boLoop);
}
void CSound::stop(int no,int layer){
	return m_core[no].stop(layer);
}
void CSound::pause(int no,int layer){
	return m_core[no].pause(layer);
}
bool CSound::load(int no,char* path,int layer){
	return m_core[no].load(path,layer);
}