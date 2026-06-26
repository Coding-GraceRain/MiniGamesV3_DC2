#pragma once
namespace GAME02 {
	class BACK
	{
	private:
		int Img = 0;
		int TitleImg = 0;
		int ClearImg = 0;
		int SecImg = 0;
		int GameOverImg[5]{};
		int Px = 0, Py = 0;
		int i = 0;
	public:
		int Take = 0;
		void create();
		void draw();
		void titledraw();
		void cleardraw();
		void secdraw();
		void gameoverdraw();
	};
}

