#pragma once

#include <map>			//std::map
#include <vector>		//std::vector
#include <string>		//std::string
#include <functional>	//std::function
#include <assert.h>		//assert

/// <summary>
/// <para>───────────────────</para>
/// <para>タスクの更新管理を行う関数ポインタ配列です。</para>
/// <para>───────────────────</para>
/// </summary>
typedef std::vector<std::function<void()>> TaskFunc;

/// <summary>
/// <para>──────────────────────</para>
/// <para>std::bind を省略できるマクロです。</para>
/// <para>継承クラス内限定で使用可能です。</para>
/// <para>──────────────────────</para>
/// </summary>
///
/// <param name="_Func_">
/// <para>関数</para>
/// <para>例：BIND(CPlayer::Move)</para>
/// </param>
#define BIND(_Func_) std::bind(&_Func_, this)

//プロトタイプ宣言
class GameTaskManager;

/// <summary>
/// <para>─────────────────</para>
/// <para>ゲームタスクシステム</para>
/// <para>オブジェクトを自動管理することができます。</para>
/// <para>─────────────────</para>
/// </summary>
class GameTask
{
	template<class TYPE>
	friend class GameTaskPointer;		//タスクのリンクや消去で必要

	friend class GameTaskManager;		//タスク登録や更新・描画で必要

private:
	GameTask*		mp_UpdatePrev;		//自身の前の更新タスクのポインタ
	GameTask*		mp_UpdateNext;		//自身の後の更新タスクのポインタ
	int				m_UpdatePriority;	//自身の更新優先順位

	GameTask*		mp_DrawPrev;		//自身の前の描画タスクのポインタ
	GameTask*		mp_DrawNext;		//自身の後の描画タスクのポインタ
	int				m_DrawPriority;		//自身の描画優先順位

	std::string		m_Name;				//デバッグやタスク一括消去等で使用する名前
	bool			m_Kill;				//タスク消去フラグ

	TaskFunc		m_Update;			//更新関数リスト

	unsigned int	m_Link;				//GameTaskPointer の接続確認

protected:
	/// <summary>
	/// <para>───────────────────────────────────────────</para>
	/// <para>タスクリストに登録を行います。</para>
	/// <para>───────────────────────────────────────────</para>
	/// <para>登録を行うことで、</para>
	/// <para>１．GameTaskManager::Update 呼び出し時に 引数や SetUpdate で設定した関数が呼び出される</para>
	/// <para>２．GameTaskManager::Draw 呼び出し時に 登録を行った継承クラスの Draw が呼び出される</para>
	/// <para>の２点が発生します。</para>
	/// <para>───────────────────────────────────────────</para>
	/// </summary>
	///
	/// <param name="update">
	/// <para>───────────────────────────────</para>
	/// <para>省略可能</para>
	/// <para>GameTaskManager::Update 呼び出し時に呼ばれる関数を設定します。</para>
	/// <para>複数の関数を指定することで、順番に呼び出すことが出来ます。</para>
	/// <para>───────────────────────────────</para>
	/// <para>BIND を使用してください。</para>
	/// <para>例：{ BIND(CPlayer::Move) }</para>
	/// <para>＿＿{ BIND(CPlayer::Move), BIND(CPlayer::Attack) }</para>
	/// <para>───────────────────────────────</para>
	/// </param>
	///
	/// <param name="updatePriority">
	/// <para>省略可能</para>
	/// <para>更新順番（値が少なければ少ないほど更新が先に行われる）</para>
	/// <para>負の値（マイナス）は非推奨</para>
	/// </param>
	///
	/// <param name="drawPriority">
	/// <para>省略可能</para>
	/// <para>描画順番（値が少なければ少ないほど描画が先に行われる）</para>
	/// <para>省略するか、負の値（マイナス）にすることで描画を行わないタスクになります。</para>
	/// </param>
	///
	/// <param name="updatePriorityPushBack">
	/// <para>省略可能</para>
	/// <para>同じ更新順番のタスクの集まりと競合した際の処理</para>
	/// <para>true  -> タスクの集まりの最後に設定</para>
	/// <para>false -> タスクの集まりの最初に設定</para>
	/// </param>
	///
	/// <param name="drawPriorityPushBack">
	/// <para>省略可能</para>
	/// <para>同じ描画順番のタスクの集まりと競合した際の処理</para>
	/// <para>true  -> タスクの集まりの最後に設定</para>
	/// <para>false -> タスクの集まりの最初に設定</para>
	/// </param>
	GameTask(const TaskFunc update = {}, const int updatePriority = 0, const int drawPriority = -1, const bool updatePriorityPushBack = true, const bool drawPriorityPushBack = true);

	//継承クラスのデストラクタが呼ばれる
	virtual ~GameTask();

	/// <summary>
	/// <para>────────────────────────</para>
	/// <para>消去フラグを立てます。</para>
	/// <para>GameTaskPointer のタスクは消去できません。</para>
	/// <para>────────────────────────</para>
	/// <para>次の GameTaskManager::Update 呼び出し時に</para>
	/// <para>１．タスクの更新リストと描画リストから除外</para>
	/// <para>２．タスク自身の消去</para>
	/// <para>が実行されます。</para>
	/// <para>────────────────────────</para>
	/// </summary>
	virtual void SetKill() final;

	/// <summary>
	/// <para>───────────────────────────────</para>
	/// <para>GameTaskManager::Update 呼び出し時に呼ばれる関数を変更します。</para>
	/// <para>複数の関数を指定することで、順番に呼び出すことが出来ます。</para>
	/// <para>前回の更新関数リストは消去され、新たに上書きされます。</para>
	/// <para>───────────────────────────────</para>
	/// <para>引数には BIND を使用してください。</para>
	/// <para>例：{ BIND(CPlayer::Move) }</para>
	/// <para>＿＿{ BIND(CPlayer::Move), BIND(CPlayer::Attack) }</para>
	/// <para>───────────────────────────────</para>
	/// </summary>
	///
	/// <param name="update">
	/// <para>BIND を使用してください。</para>
	/// <para>例：{ BIND(CPlayer::Move) }</para>
	/// <para>＿＿{ BIND(CPlayer::Move), BIND(CPlayer::Attack) }</para>
	/// </param>
	virtual void SetUpdate(const TaskFunc update) final;

	/// <summary>
	/// <para>─────────────────────────────────</para>
	/// <para>GameTaskManager::Update 呼び出し時に呼ばれる関数を全て消去します。</para>
	/// <para>IsUpdateActive で false が返されるようになります。</para>
	/// <para>─────────────────────────────────</para>
	/// </summary>
	virtual void EmptyUpdate() final;

public:
	/// <summary>
	/// <para>──────────────────────────────────</para>
	/// <para>GameTaskManager::Update 呼び出し時に呼ばれる関数の状態を確認します。</para>
	/// <para>──────────────────────────────────</para>
	/// <para>true  -> 有効</para>
	/// <para>false -> 関数が未設定</para>
	/// <para>──────────────────────────────────</para>
	/// </summary>
	virtual bool isUpdateActive() const final;

	/// <summary>
	/// <para>────────────────────────</para>
	/// <para>タスク名を変更します。</para>
	/// <para>GameTaskPointer のタスクは変更できません。</para>
	/// <para>────────────────────────</para>
	/// <para>１．GameTaskManager::Clear でグループ消去</para>
	/// <para>２．デバッグ時の名前確認</para>
	/// <para>等の機能に利用できます。</para>
	/// <para>────────────────────────</para>
	/// </summary>
	///
	/// <param name="name">
	/// <para>タスク名</para>
	/// </param>
	virtual void SetName(const std::string name) final;

	/// <summary>
	/// <para>─────────</para>
	/// <para>タスク名を取得します。</para>
	/// <para>─────────</para>
	/// </summary>
	///
	/// <returns>
	/// <para>タスク名</para>
	/// </returns>
	virtual const std::string name() const final;

	/// <summary>
	/// <para>────────────────────────────────</para>
	/// <para>GameTaskManager::Update 呼び出し時のタスクの更新順番を変更します。</para>
	/// <para>────────────────────────────────</para>
	/// </summary>
	///
	/// <param name="updatePriority">
	/// <para>更新順番（値が少なければ少ないほど更新が先に行われる）</para>
	/// <para>負の値（マイナス）は非推奨</para>
	/// </param>
	///
	/// <param name="pushBack">
	/// <para>省略可能</para>
	/// <para>同じ更新順番のタスクの集まりと競合した時の処理</para>
	/// <para>true  -> タスクの集まりの最後に設定</para>
	/// <para>false -> タスクの集まりの最初に設定</para>
	/// </param>
	virtual void SetUpdatePriority(const int updatePriority, const bool pushBack = true) final;

	/// <summary>
	/// <para>─────────────────────────────────</para>
	/// <para>GameTaskManager::Update 呼び出し時のタスクの描画順番を操作します。</para>
	/// <para>─────────────────────────────────</para>
	/// <para>１．描画順番を変更 -> 登録が行われている状態で、正の値（プラス）を指定</para>
	/// <para>２．描画順番を登録 -> 登録が行われていない状態で、正の値（プラス）を指定</para>
	/// <para>３．描画順番を消去 -> 登録が行われている状態で、負の値（マイナス）を指定</para>
	/// <para>─────────────────────────────────</para>
	/// </summary>
	///
	/// <param name="drawPriority">
	/// <para>描画順番（値が少なければ少ないほど描画が先に行われる）</para>
	/// <para>負の値（マイナス）を指定することで、登録解除できます。</para>
	/// </param>
	///
	/// <param name="pushBack">
	/// <para>省略可能</para>
	/// <para>同じ描画順番のタスクの集まりと競合した時の処理</para>
	/// <para>true  -> タスクの集まりの最後に設定</para>
	/// <para>false -> タスクの集まりの最初に設定</para>
	/// </param>
	virtual void SetDrawPriority(const int drawPriority, const bool pushBack = true) final;

private:
	//継承先の Draw を呼び出す
	virtual void Draw();
};

/// <summary>
/// <para>─────────────────</para>
/// <para>ゲームタスクマネージャー</para>
/// <para>オブジェクト全体の設定・管理を行います。</para>
/// <para>─────────────────</para>
/// </summary>
class GameTaskManager
{
	friend class GameTask;				//様々な取得や参照で必要

private:
	static GameTask* mp_UpdateBegin;	//更新タスクリストの先頭ポインタ
	static GameTask* mp_DrawBegin;		//描画タスクリストの先頭ポインタ

private:
	//タスクの消去　次のタスクのポインタが返される
	static GameTask* Kill(GameTask* taskPointer);

	//更新タスクリストへの登録
	static void Register_Update(GameTask* taskPointer, const bool pushBack);

	//描画タスクリストへの登録
	static void Register_Draw(GameTask* taskPointer, const bool pushBack);

	//更新タスクリストから消去　次のタスクのポインタが返される
	static GameTask* Unregister_Update(GameTask* taskPointer);

	//描画タスクリストから消去
	static void Unregister_Draw(GameTask* taskPointer);

public:
	/// <summary>
	/// <para>───────────────────</para>
	/// <para>登録されているタスクを全て消去します。</para>
	/// <para>GameTaskPointer のタスクは消去されません。</para>
	/// <para>───────────────────</para>
	/// </summary>
	static void Clear();

	/// <summary>
	/// <para>─────────────────────────────</para>
	/// <para>GameTask::SetName で設定したタスク名と同じタスクを消去します。</para>
	/// <para>GameTaskPointer のタスクは消去できません。</para>
	/// <para>─────────────────────────────</para>
	///
	/// <param name="name">
	/// <para>消去するタスク名</para>
	/// <para>空の文字列（""）にすることで、GameTask::SetName で設定を行っていないタスクが消去されます。</para>
	/// </param>
	/// </summary>
	static void Clear(const std::string name);

	/// <summary>
	/// <para>────────────────</para>
	/// <para>登録されているタスクを全て更新します。</para>
	/// <para>────────────────</para>
	/// </summary>
	static void Update();

	/// <summary>
	/// <para>────────────────</para>
	/// <para>登録されているタスクを全て描画します。</para>
	/// <para>────────────────</para>
	/// </summary>
	static void Draw();
};

/// <summary>
/// <para>─────────────────</para>
/// <para>ゲームタスクポインタ</para>
/// <para>オブジェクトを外部操作することができます。</para>
/// <para>─────────────────</para>
/// </summary>
template<class TYPE>
class GameTaskPointer
{
private:
	TYPE* mp_Task; //タスクポインタ

private:
	//タスクの消去と上書き
	void _Reset_(TYPE* taskPointer)
	{
		//タスクが既にリンクされている場合は、消去する
		if (mp_Task != nullptr)
		{
			//ロックを１つ減らす
			--mp_Task->m_Link;

			//リンクがない場合はタスクを消去
			if (mp_Task->m_Link == 0) mp_Task->m_Kill = true;
		}

		//タスクの代入
		mp_Task = taskPointer;

		//タスクが存在する場合は、ここ以外からの消去を出来ないようにロックを追加する
		if (mp_Task != nullptr) mp_Task->m_Link++;
	}

public:
	//タスクの初期化
	GameTaskPointer()
		: mp_Task(nullptr)
	{

	}

	/// <summary>
	/// <para>─────────────────────</para>
	/// <para>タスクとリンクします。</para>
	/// <para>既にリンク中であるタスクは消去、または開放されます。</para>
	/// <para>─────────────────────</para>
	/// </summary>
	///
	/// <param name="taskPointer">
	/// <para>リンク対象のタスク</para>
	/// </param>
	GameTaskPointer(TYPE* taskPointer)
	{
		_Reset_(taskPointer);
	}

	//タスクの消去
	~GameTaskPointer()
	{
		_Reset_(nullptr);
	}

	/// <summary>
	/// <para>─────────────────────</para>
	/// <para>タスクとリンクします。</para>
	/// <para>既にリンク中であるタスクは消去、または開放されます。</para>
	/// <para>─────────────────────</para>
	/// </summary>
	///
	/// <param name="taskPointer">
	/// <para>リンク対象のタスク</para>
	/// </param>
	void operator = (TYPE* taskPointer)
	{
		_Reset_(taskPointer);
	}

	/// <summary>
	/// <para>─────────────</para>
	/// <para>タスクを消去、または開放します。</para>
	/// <para>─────────────</para>
	/// </summary>
	void Clear()
	{
		_Reset_(nullptr);
	}

	/// <summary>
	/// <para>───────────────────────────────────────</para>
	/// <para>タスクポインタから切り離します。</para>
	/// <para>タスクは消去されないので、自身で GameTask::SetKill を呼び出して消去する必要があります。</para>
	/// <para>───────────────────────────────────────</para>
	/// </summary>
	void Free()
	{
		//タスクが存在しない場合は、実行しない
		if (mp_Task == nullptr) return;

		//ロックを解除する
		--mp_Task->m_Link;

		//タスク消去をしないまま、リンクを切断する
		mp_Task = nullptr;
	}

	/// <summary>
	/// <para>────────</para>
	/// <para>タスクを取得します。</para>
	/// <para>────────</para>
	/// </summary>
	TYPE* operator -> () const
	{
		return mp_Task;
	}

	/// <summary>
	/// <para>────────</para>
	/// <para>タスクを取得します。</para>
	/// <para>────────</para>
	/// </summary>
	TYPE* getTask() const
	{
		return mp_Task;
	}

	/// <summary>
	/// <para>────────────────────────────────</para>
	/// <para>リンクしているタスクが、他の GameTaskPointer とリンクを行っているか取得します。</para>
	/// <para>他のリンクが存在する場合は、2 以上の値が返されます。</para>
	/// <para>────────────────────────────────</para>
	/// </summary>
	unsigned int link() const
	{
		return mp_Task->m_Link;
	}
};

/// <summary>
/// <para>───────────────</para>
/// <para>ゲームタスクポインタリスト</para>
/// <para>タスクの消去を防ぐ専用のリストです。</para>
/// <para>デストラクタの消去が発生しません。</para>
/// <para>───────────────</para>
/// </summary>
template<class TYPE>
class GameTaskPointerList
{
private:
	unsigned int									m_ID;			//代入する map の識別番号

	std::map<unsigned int, GameTaskPointer<TYPE>>	m_List;			//ゲームタスクポインタリスト
	std::vector<unsigned int>						m_RegistID;		//登録済みの番号一覧

public:
	//初期化
	GameTaskPointerList() : m_ID(0)
	{

	}

	/// <summary>
	/// <para>─────────────────</para>
	/// <para>識別番号を使用して、タスクを取得します。</para>
	/// <para>─────────────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの識別番号</para>
	/// </param>
	TYPE& operator ()(unsigned int number)
	{
		//インスタンスが生成されないように参照する
		return *m_List[number].getTask();
	}

	/// <summary>
	/// <para>────────</para>
	/// <para>タスクを取得します。</para>
	/// <para>────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの配列番号</para>
	/// </param>
	TYPE& operator [](unsigned int number)
	{
		//インスタンスが生成されないように参照する
		return *m_List[m_RegistID[number]].getTask();
	}

	/// <summary>
	/// <para>───────────────</para>
	/// <para>タスクとリンクし、リストに追加します。</para>
	/// <para>───────────────</para>
	/// </summary>
	///
	/// <param name="taskPointer">
	/// <para>リンク対象のタスク</para>
	/// </param>
	void Add(TYPE* taskPointer)
	{
		//識別番号の位置にタスクをリンク
		m_List[m_ID] = taskPointer;

		//新規識別番号を登録済みリストに追加
		m_RegistID.push_back(m_ID);

		//識別番号を次に移動する
		m_ID++;
	}

	/// <summary>
	/// <para>─────────────────</para>
	/// <para>識別番号を使用して、タスクを消去します。</para>
	/// <para>─────────────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの識別番号</para>
	/// </param>
	void Clear_ID(unsigned int number)
	{
		//タスクの消去
		m_List.erase(number);

		//登録済みリストから消去
		m_RegistID.erase(m_RegistID.begin() + toArrayNumber(number));
	}

	/// <summary>
	/// <para>────────</para>
	/// <para>タスクを消去します。</para>
	/// <para>────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの配列番号</para>
	/// </param>
	void Clear(unsigned int number)
	{
		//タスクの消去
		m_List.erase(m_RegistID[number]);

		//登録済みリストから消去
		m_RegistID.erase(m_RegistID.begin() + number);
	}

	/// <summary>
	/// <para>─────────</para>
	/// <para>タスクを全消去します。</para>
	/// <para>─────────</para>
	/// </summary>
	void Clear()
	{
		//タスクリストの全初期化
		m_List.clear();

		//登録済みリストの全初期化
		m_RegistID.clear();

		//識別番号を最初の位置へ移動
		m_ID = 0;
	}

	/// <summary>
	/// <para>─────────────────────────────────────</para>
	/// <para>識別番号を使用して、タスクリストからタスクを切り離します。</para>
	/// <para>タスクは消去されないので、自身で GameTask::SetKill を呼び出して消去する必要があります。</para>
	/// <para>─────────────────────────────────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの識別番号</para>
	/// </param>
	void Free_ID(unsigned int number)
	{
		//タスクの開放
		m_List[number].Free();

		//空のタスクリストの消去
		m_List.erase(number);

		//登録済みリストから消去
		m_RegistID.erase(m_RegistID.begin() + toArrayNumber(number));
	}

	/// <summary>
	/// <para>───────────────────────────────────────</para>
	/// <para>タスクリストから切り離します。</para>
	/// <para>タスクは消去されないので、自身で GameTask::SetKill を呼び出して消去する必要があります。</para>
	/// <para>───────────────────────────────────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの配列番号</para>
	/// </param>
	void Free(unsigned int number)
	{
		//タスクの開放
		m_List[m_RegistID[number]].Free();

		//空のタスクリストの消去
		m_List.erase(m_RegistID[number]);

		//登録済みリストから消去
		m_RegistID.erase(m_RegistID.begin() + number);
	}

	/// <summary>
	/// <para>──────────────────────</para>
	/// <para>識別番号を使用して、タスクの配列位置を入れ替えます。</para>
	/// <para>──────────────────────</para>
	/// </summary>
	///
	/// <param name="left">
	/// <para>リストの識別番号</para>
	/// </param>
	///
	/// <param name="right">
	/// <para>リストの識別番号</para>
	/// </param>
	void Swap_ID(unsigned int left, unsigned int right)
	{
		//識別番号を入れ替える
		m_RegistID[toArrayNumber(left)] = right;
		m_RegistID[toArrayNumber(right)] = left;
	}

	/// <summary>
	/// <para>──────────────</para>
	/// <para>タスクの配列位置を入れ替えます。</para>
	/// <para>──────────────</para>
	/// </summary>
	///
	/// <param name="left">
	/// <para>リストの配列番号</para>
	/// </param>
	///
	/// <param name="right">
	/// <para>リストの配列番号</para>
	/// </param>
	void Swap(unsigned int left, unsigned int right)
	{
		//識別番号を入れ替える
		unsigned int tmp = m_RegistID[left];
		m_RegistID[left] = m_RegistID[right];
		m_RegistID[right] = tmp;
	}

	/// <summary>
	/// <para>──────────</para>
	/// <para>識別番号を取得します。</para>
	/// <para>──────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの配列番号</para>
	/// </param>
	unsigned int toID(unsigned int number) const
	{
		return m_RegistID[number];
	}

	/// <summary>
	/// <para>───────────────────</para>
	/// <para>識別番号を使用して、配列番号を取得します。</para>
	/// <para>───────────────────</para>
	/// </summary>
	///
	/// <param name="number">
	/// <para>リストの識別番号</para>
	/// </param>
	unsigned int toArrayNumber(unsigned int number)
	{
		//配列番号を調べる
		unsigned int count = 0;

		//登録済みリストの位置が、識別番号の順にはなっていないので探索する
		std::vector<unsigned int>::iterator it = m_RegistID.begin();

		//最後までループ
		while (it != m_RegistID.end())
		{
			//識別番号が一致した場合は現時点の配列番号を返す
			if (number == *it)
			{
				return count;
			}

			//カウントアップ
			count++;

			//次のタスクへ移動
			it++;
		}

		//識別番号が一致しない
		assert(false && !"GameTaskPointerList -> 配列番号を取得できません。");

		//安全のため、最初の要素を返す
		return 0;
	}

	/// <summary>
	/// <para>────────────────────────────────</para>
	/// <para>GameTaskPointerList::Add で次に割り当てられる識別番号を取得します。</para>
	/// <para>────────────────────────────────</para>
	/// </summary>
	unsigned int nextID() const
	{
		return m_ID;
	}

	/// <summary>
	/// <para>─────────────</para>
	/// <para>空の状態であるかを取得します。</para>
	/// <para>─────────────</para>
	/// </summary>
	bool isEmpty() const
	{
		return m_RegistID.empty();
	}

	/// <summary>
	/// <para>─────────</para>
	/// <para>要素数を取得します。</para>
	/// <para>─────────</para>
	/// </summary>
	unsigned int size() const
	{
		return m_RegistID.size();
	}
};