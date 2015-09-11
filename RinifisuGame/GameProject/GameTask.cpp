#include "GameTask.h"

GameTask::GameTask(const TaskFunc update, const int updatePriority, const int drawPriority, const bool updatePriorityPushBack, const bool drawPriorityPushBack)
	: mp_UpdatePrev(nullptr)	, mp_UpdateNext(nullptr)	, m_UpdatePriority(updatePriority)
	, mp_DrawPrev(nullptr)		, mp_DrawNext(nullptr)		, m_DrawPriority(drawPriority)
	, m_Name("")				, m_Kill(false)				, m_Update(update)
	, m_Link(0)
{
	//更新タスクリストに登録
	GameTaskManager::Register_Update(this, updatePriorityPushBack);

	//負の値でなければ、描画タスクリストへ登録
	if (0 <= m_DrawPriority) GameTaskManager::Register_Draw(this, drawPriorityPushBack);
}

GameTask::~GameTask()
{

}

void GameTask::SetKill()
{
	//GameTaskPointer にリンクしているタスクは消去できない
	if (m_Link != 0) return;

	//消去フラグを有効にする
	m_Kill = true;
}

void GameTask::SetUpdate(const TaskFunc update)
{
	m_Update = update;
}

void GameTask::EmptyUpdate()
{
	//空にする
	m_Update.clear();
}

bool GameTask::isUpdateActive() const
{
	//空でないか確認
	return !m_Update.empty();
}

void GameTask::SetName(const std::string name)
{
	m_Name = name;
}

const std::string GameTask::name() const
{
	return m_Name;
}

void GameTask::SetUpdatePriority(const int updatePriority, const bool pushBack)
{
	//更新リストから登録を解除する
	GameTaskManager::Unregister_Update(this);

	//更新順番を変更
	m_UpdatePriority = updatePriority;

	//更新リストに再登録する
	GameTaskManager::Register_Update(this, pushBack);
}

void GameTask::SetDrawPriority(const int drawPriority, const bool pushBack)
{
	//登録を行っている場合は、描画リストから登録を解除する
	if (0 <= m_DrawPriority) GameTaskManager::Unregister_Draw(this);

	//描画順番を変更
	m_DrawPriority = drawPriority;

	//正の値なら、描画リストに登録する
	if (0 <= drawPriority) GameTaskManager::Register_Draw(this, pushBack);
}

void GameTask::Draw()
{
	//タスクの Draw 関数が呼ばれていない
	assert(false && !"GameTask -> タスクの Draw 関数が存在しません。");
}

//インスタンスの生成
GameTask* GameTaskManager::mp_UpdateBegin = nullptr;	//更新タスクリストの先頭ポインタ
GameTask* GameTaskManager::mp_DrawBegin = nullptr;	//描画タスクリストの先頭ポインタ

GameTask* GameTaskManager::Kill(GameTask* taskPointer)
{
	//更新リストから登録を解除する
	//return で返す次のタスクポインタを取得
	GameTask* returnTaskPointer = Unregister_Update(taskPointer);

	//登録を行っている場合は、描画リストから登録を解除する
	if (0 <= taskPointer->m_DrawPriority) Unregister_Draw(taskPointer);

	//タスクの消去
	delete taskPointer;

	//次のタスクポインタを返す
	return returnTaskPointer;
}

void GameTaskManager::Register_Update(GameTask* taskPointer, const bool pushBack)
{
	//最初のポインタが空の場合は新規タスクのポインタを設定
	if (mp_UpdateBegin == nullptr) mp_UpdateBegin = taskPointer;
	//登録処理
	else
	{
		GameTask* task = mp_UpdateBegin;	//現在のタスクポインタ
		GameTask* prev = nullptr;		//１つ前のタスクポインタ

		//最後までループする
		while (task != nullptr)
		{
			//優先度の関係でこれ以上進めない場合
			if ((pushBack && taskPointer->m_UpdatePriority < task->m_UpdatePriority)
				|| (!pushBack && taskPointer->m_UpdatePriority <= task->m_UpdatePriority))
			{
				//入れ替え対象のタスクが先頭だった場合は自身で上書き
				if (task == mp_UpdateBegin) mp_UpdateBegin = taskPointer;

				//次が無いポインタにタスクのポインタを代入
				taskPointer->mp_UpdateNext = task;

				//前が無いポインタに新規タスクのポインタを代入
				task->mp_UpdatePrev = taskPointer;

				break;
			}

			//前のタスクに現在のタスクを代入
			prev = task;

			//次のタスクへ移動
			task = task->mp_UpdateNext;

			//優先順位が決まらなかった場合は nullptr を代入
			//ここに到達するタスクは優先度が更新リストの中で１番最大である
			if (task == nullptr) taskPointer->mp_UpdateNext = nullptr;
		}

		//先頭を変更した場合は前が存在しないので nullptr を保持
		if (prev != nullptr)
		{
			//次が無いポインタに新規タスクのポインタを代入
			prev->mp_UpdateNext = taskPointer;

			//前が無いポインタにタスクのポインタを代入
			taskPointer->mp_UpdatePrev = prev;
		}
	}
}

void GameTaskManager::Register_Draw(GameTask* taskPointer, const bool pushBack)
{
	//最初のポインタが空の場合は新規タスクのポインタを設定
	if (mp_DrawBegin == nullptr) mp_DrawBegin = taskPointer;
	//登録処理
	else
	{
		GameTask* task = mp_DrawBegin;	//現在のタスクポインタ
		GameTask* prev = nullptr;		//１つ前のタスクポインタ

		//最後までループする
		while (task != nullptr)
		{
			//優先度の関係でこれ以上進めない場合
			if ((pushBack && taskPointer->m_DrawPriority < task->m_DrawPriority)
				|| (!pushBack && taskPointer->m_DrawPriority <= task->m_DrawPriority))
			{
				//入れ替え対象のタスクが先頭だった場合は自身で上書き
				if (task == mp_DrawBegin) mp_DrawBegin = taskPointer;

				//次が無いポインタにタスクのポインタを代入
				taskPointer->mp_DrawNext = task;

				//前が無いポインタに新規タスクのポインタを代入
				task->mp_DrawPrev = taskPointer;

				break;
			}

			//前のタスクに現在のタスクを代入
			prev = task;

			//次のタスクへ移動
			task = task->mp_DrawNext;

			//優先順位が決まらなかった場合は nullptr を代入
			//ここに到達するタスクは優先度が描画リストの中で１番最大である
			if (task == nullptr) taskPointer->mp_DrawNext = nullptr;
		}

		//先頭を変更した場合は前が存在しないので nullptr を保持
		if (prev != nullptr)
		{
			//次が無いポインタに新規タスクのポインタを代入
			prev->mp_DrawNext = taskPointer;

			//前が無いポインタにタスクのポインタを代入
			taskPointer->mp_DrawPrev = prev;
		}
	}
}

GameTask* GameTaskManager::Unregister_Update(GameTask* taskPointer)
{
	GameTask* updateNext = taskPointer->mp_UpdateNext; //タスクの次のポインタ
	GameTask* updatePrev = taskPointer->mp_UpdatePrev; //タスクの前のポインタ

	//次のポインタに前のポインタを代入してつなぎ合わせる
	if (updateNext != nullptr) updateNext->mp_UpdatePrev = updatePrev;

	//前のポインタに次のポインタを代入してつなぎ合わせる
	if (updatePrev != nullptr) updatePrev->mp_UpdateNext = updateNext;
	//null の場合は一番最初にあったタスクがなくなったので、次のタスクを先頭にする
	else mp_UpdateBegin = updateNext;

	//次のタスクのポインタを返す
	return updateNext;
}

void GameTaskManager::Unregister_Draw(GameTask* taskPointer)
{
	GameTask* drawNext = taskPointer->mp_DrawNext; //タスクの次のポインタ
	GameTask* drawPrev = taskPointer->mp_DrawPrev; //タスクの前のポインタ

	//次のポインタに前のポインタを代入してつなぎ合わせる
	if (drawNext != nullptr) drawNext->mp_DrawPrev = drawPrev;

	//前のポインタに次のポインタを代入してつなぎ合わせる
	if (drawPrev != nullptr) drawPrev->mp_DrawNext = drawNext;
	//null の場合は一番最初にあったタスクがなくなったので、次のタスクを先頭にする
	else mp_DrawBegin = drawNext;
}

void GameTaskManager::Clear()
{
	//現在のタスクポインタ
	GameTask* taskPointer = mp_UpdateBegin;

	//最後までループする
	while (taskPointer != nullptr)
	{
		//タスクを消去し、次のタスクへ移動
		//GameTaskPointer にリンクしているタスクは消去できない
		if (taskPointer->m_Link == 0) taskPointer = Kill(taskPointer);
		else taskPointer = taskPointer->mp_UpdateNext;
	}
}

void GameTaskManager::Clear(const std::string name)
{
	//現在のタスクポインタ
	GameTask* taskPointer = mp_UpdateBegin;

	//最後までループする
	while (taskPointer != nullptr)
	{
		//名前が一致しているタスクを消去し、次のタスクへ移動
		//GameTaskPointer にリンクしているタスクは消去できない
		if (taskPointer->m_Name == name && taskPointer->m_Link == 0) taskPointer = Kill(taskPointer);
		else taskPointer = taskPointer->mp_UpdateNext;
	}
}

void GameTaskManager::Update()
{
	//現在のタスクポインタ
	GameTask* taskPointer = mp_UpdateBegin;

	//最後までループする
	while (taskPointer != nullptr)
	{
		//消去フラグが立っている場合はタスクの消去し、次のタスクへ移動
		if (taskPointer->m_Kill) taskPointer = Kill(taskPointer);
		//更新処理
		else
		{
			//更新関数リストを順番に呼び出す
			for (unsigned int i = 0; i < taskPointer->m_Update.size(); i++) taskPointer->m_Update[i]();

			//次のタスクへ移動
			taskPointer = taskPointer->mp_UpdateNext;
		}
	}
}

void GameTaskManager::Draw()
{
	//現在のタスクポインタ
	GameTask* taskPointer = mp_DrawBegin;

	//最後までループする
	while (taskPointer != nullptr)
	{
		//継承クラスの描画関数を呼び出す
		taskPointer->Draw();

		//次のタスクへ移動
		taskPointer = taskPointer->mp_DrawNext;
	}
}