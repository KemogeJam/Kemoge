/*!
*	@brief	OBJ�p���f���N���X
*
*
**/
#pragma once
#include "CTexture.h"
#include "CModel.h"
/*!
		@brief	�}�e���A���N���X
**/
class CMaterialObj {
public:
	float m_ambient[4];		//�A���r�G���g�J���[
	float m_diffuse[4];		//�f�t���[�Y�J���[
	float m_specular[4];	//�X�y�L�����[�J���[
	float m_shininess;		//�X�y�L�����[�W��
	float m_alpha;
	CVector2D m_st;
	CTexture *m_pTex;		//�e�N�X�`���[
public:
	CMaterialObj();
	/*!
		@brief	�}�e���A���𔽉f
		@param	shader		[in]	�V�F�[�_�[�I�u�W�F�N�g
		@retval	����
	**/
	void Map(CShader *shader);
	
	/*!
		@brief	�}�e���A���i�̃e�N�X�`���[�j�𖳌���
		@retval	����
	**/
	void Unmap();

	/*!
		@brief	�}�e���A���i�̃e�N�X�`���[�j���

		@retval	����
	**/
	void Release();
};

class CMeshObj {
public:
	GLuint		m_buffers[3];
	CVector3D*	m_pVertexAry;		//���_���W�z��
	CVector3D*	m_pNormalAry;		//�@���z��
	CVector2D*	m_pTexCoordAry;		//�e�N�X�`���[�R�[�h�z��
	int			m_vertexNum;		//���_��
	CMaterialObj	m_material;		//�}�e���A���f�[�^
	char		m_materialname[32];	//�}�e���A����

	CMeshObj();
	void SendBuffer();
	void Render(CShader *shader);
	void Release();
};
/*!
		@brief	OBJ�t�@�C���p���f���N���X
**/
class CModelObj : public CModel {
private:
	
	CMeshObj *m_mesh;
	int		m_materialCnt;
	/*!
		@brief	�}�e���A���f�[�^�̓ǂݍ���
		@param	path		[in]	�t�@�C����
		@retval	����
	**/
	bool	LoadMaterial(char *path);
public:

	/*!
		@brief	�R���X�g���N�^
	**/
	CModelObj();

	/*!
		@brief	�f�X�g���N�^
	**/
	~CModelObj();

	/*!
		@brief	OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
		@param	path				[in] �t�@�C����
		@retval	����
	**/
	bool	Load(const char *path);

	/*!
		@brief	�`����s��
		@param	m				[in] ���[���h�s��
		@retval	����
	**/
	void	RenderM(CMatrix &m);

	/*!
		@brief	���f���f�[�^��j������
		@retval	����
	**/
	void	Release();

	CMaterialObj	*getMaterial(int no) {
		return &m_mesh[no].m_material;
	}
	void	setAlpha(float alpha,int no=-1);

};