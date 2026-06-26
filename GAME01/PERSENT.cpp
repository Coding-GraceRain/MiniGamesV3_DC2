#include"PERSENT.h"
namespace GAME01
{
	int rand100() {
		return ((rand() % 100) + 1);
	}
	int rand1000() {
		return ((rand() % 1000) + 1);
	}
	int rand100000() {
		return((rand() % 100000) + 1);
	}
	int customrand(int min, int max) {
		int finrand;//ここに最終結果を入れる
		finrand = (rand() % ((max + 1) - min)) + min;//例min = 25,max = 50  51-25=26 rand%26 = 0~25 +25 = 25~50
		return finrand;
	}
}