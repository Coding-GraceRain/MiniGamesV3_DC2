#pragma once
#include "SAIKORO.h"
#include "MULTI.h"
//#include "SORO.h"
class TAITLE 
{
	SAIKORO saikoro;
	MULTI1 multi1;
	MULTI2 multi2;
	MULTI3 multi3;
	SAIKORO* sai[4] = {
		&saikoro,
		&multi1,
		&multi2,
		&multi3,
	};
	//SORO soro;

	enum { TAITLE1,EXPLAIN, SORO, MULTI, SENSEKI };
	int State = 0;
	int num[7] = {2,1,1,0,0,0,1};//0:人数	1:親回数　2:説明ページ数  3:ゲーム数  4:現在のゲーム数  6:手番管理  
	int Flag[3] = {};//0,1:設定  2:勝敗
public:
	void state();
	int create();
	void round(int n,int num);
	void setumei();
	void settei();
	void gamesetumei();
	void hantei();
	void kekka();
	void init();
};

