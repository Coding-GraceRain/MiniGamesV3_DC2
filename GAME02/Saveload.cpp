#include "Saveload.h"
namespace GAME02{
	int SAVELOAD::loadscore() {
		int HighScore = 0;
		std::ifstream fin("save.txt");
		if (fin)fin >> HighScore;
		fin.close();
		return HighScore;
	}

	void SAVELOAD::savescore(int i) {
		int HighScore = loadscore();
		if (i > HighScore) {
			std::ofstream fout("save.txt");
			if (fout)
			{
				fout << i;
			}
			fout.close();
		}
	}
}