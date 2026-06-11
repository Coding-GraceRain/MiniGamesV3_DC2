#include "Saveload.h"
namespace GAME02{
	int SAVELOAD::loadscore() {
		int HighScore = 0;
		std::ifstream fin("saveee.txt");
		if (fin)fin >> HighScore;
		fin.close();
		return HighScore;
	}

	void SAVELOAD::savescore(int i) {
		int HighScore = loadscore();
		if (i > HighScore) {
			std::ofstream fout("saveee.txt");
			if (fout)
			{
				fout << i;
			}
			fout.close();
		}
	}
}