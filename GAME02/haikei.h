#pragma once
namespace GAME02 {
	class BACK
	{
	private:
		int Img = 0;
		int ClearImg = 0;
		int SecImg = 0;
		int GameOverImg = 0;
		int Px = 0, Py = 0;
	public:
		void create();
		void draw();
		void cleardraw();
		void secdraw();
		void gameoverdraw();
	};
}

