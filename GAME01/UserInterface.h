#pragma once
namespace GAME01
{
	class GAME1;
	class PLAYER;
	class UserInterface
	{
	private:
		float Col;//横幅
		float Row;//縦幅
		int choiceCursor;
		int size;
		int entryNum;//項目数
		int index;//どこ表示してるか　1=UI表示した最初の画面　2=ステータス確認　3=所持アイテム（未実装）　4=所持武器（未実装）
		int wardCount;
	public:
		GAME1* game;
		PLAYER* player;
		~UserInterface();
		void init();
		void openUI();
		void setindex(int i) { index = i; }
	};
}

