#include "../../libOne/inc/libOne.h"
#include "TAITLE.h"
int TAITLE::create() {
	saikoro.create();
	multi1.create();
	multi2.create();
	multi3.create();
	//soro.create();
	return 0;
}

void TAITLE::state() {
	if (State == TAITLE1) {
		clear(0, 0, 64);//0,0,64
		textSize(50);
		fill(255, 255, 0);
		//text("GAME07タイトル", 0, 100);
		text("ENTERキーでメニューに戻る", 0, 1080);
		fill(255);
		textSize(200);
		text("チンチロ", 500, 400);
		textSize(50);
		text("SPACEでゲーム説明へ", 700, 500);
		text("Zで人数設定へ", 700, 600);


		if (isTrigger(KEY_SPACE)) {
			State = EXPLAIN;
		}

		if (isTrigger(KEY_Z)) {
			num[2] = 3;
			State = EXPLAIN;
		}
	}

	else if (State == EXPLAIN) {
		gamesetumei();
		/*textSize(50);
		text("ENTERキーでメニューに戻る", 0, 1080);*/
		if (isTrigger(KEY_M)) {
			saikoro.init();
			multi1.init();
			multi2.init();
			multi3.init();
			init();
			State = TAITLE1;
		}
	}


	else if (State == MULTI) {
		clear(0, 0, 64);//0,0,64
		fill(255);
		round(num[3], num[4]);
		textSize(50);
		//text(num[6], 900, 500);

		if (num[3] == num[4]) {
			State = SENSEKI;
		}

		saikoro.set(300, 300, num[4] % num[0]);
		saikoro.judge(475, 500);

		if (num[6] == 1) {
			saikoro.kakekin();
			text("1P", 900, 500);
			if (isTrigger(KEY_SPACE) && Flag[2] == 0 || num[4] % num[0] == 0) {
				num[6] += 1;
				Flag[2] = 1;
			}
		}

		else if (Flag[2] == 1 && num[6] == 2) { Flag[2] = 0; }
		multi1.set(1200, 300, num[4] % num[0]);
		multi1.judge(1375, 500);
		if (num[6] == 2) {
			multi1.kakekin();
			text("2P", 900, 500);
			if (isTrigger(KEY_SPACE) && Flag[2] == 0 || num[4] % num[0] == 1) {
				num[6] += 1;
				Flag[2] = 1;
			}
		}

		else if (Flag[2] == 1 && num[6] == 3) { Flag[2] = 0; }
		if (num[0] >= 3) {
			multi2.set(300, 650, num[4] % num[0]);
			multi2.judge(475, 850);
			if (num[6] == 3) {
				multi2.kakekin();
				text("3P", 900, 500);
				if (isTrigger(KEY_SPACE) && Flag[2] == 0 || num[4] % num[0] == 2) {
					num[6] += 1;
					Flag[2] = 1;
				}
			}
			else if (Flag[2] == 1 && num[6] == 4) { Flag[2] = 0; }
		}

		if (num[0] >= 4) {
			multi3.set(1200, 650, num[4] % num[0]);
			multi3.judge(1375, 850);
			if (num[6] == 4 || num[4] % num[0] == 3) {
				multi3.kakekin();
				text("4P", 900, 500);
				if (isTrigger(KEY_SPACE) && Flag[2] == 0) {
					num[6] += 1;
					Flag[2] = 1;
				}
			}
		}
		if (Flag[2] == 1 && num[0] == num[6] - 1) {
			saikoro.kakekinf();
			multi1.kakekinf();
			multi2.kakekinf();
			multi3.kakekinf();
		}

		if (isPress(KEY_Q)) {
			gamesetumei();
		}
		if (isTrigger(KEY_M)) {
			saikoro.init();
			multi1.init();
			multi2.init();
			multi3.init();
			init();
			State = TAITLE1;
		}
		hantei();
		//kari();
	}

	//封印
	/*
	else if (State == SORO) {
		clear(0, 0, 64);
		fill(255);
		saikoro.set(300, 300, num[4] % num[0]);
		soro.set(1200, 300, saikoro.flagr());

		saikoro.judge(450, 500);
		soro.judge(1350, 500);

		//saikoro.kakekin();
		//soro.kakekin();

		if (isTrigger(KEY_R)) {
			saikoro.init();
			soro.init();
		}

		if (saikoro.yakur() > soro.yakur() && 1 == saikoro.flagr() && 1 == soro.flagr()) { text("1Pの勝ち", 870, 300); }
		else if (saikoro.yakur() < soro.yakur() && 1 == saikoro.flagr() && 1 == soro.flagr()) { text("BOTの勝ち", 850, 300); }
		else if (saikoro.yakur() == soro.yakur() && 1 == saikoro.flagr() && 1 == soro.flagr()) { text("引き分け", 870, 300); }
	}
	*/

	else if (State == SENSEKI) {
		clear(0, 0, 64);
		kekka();
		if (isTrigger(KEY_M)) {
			saikoro.init();
			multi1.init();
			multi2.init();
			multi3.init();
			init();
			State = TAITLE1;
		}
		text(" Mでタイトルへも戻る", 20, 1080);
	}
}

void TAITLE::round(int n,int num) {
	stroke(255);
	strokeWeight(3);
	fill(255);
	textSize(100);
	text(num+1, 700, 150);
	text(n, 850, 150);
	text(" /  回目", 750, 150);
 
}

void TAITLE::setumei() {
	fill(255);
	textSize(60);
	text("操作説明", 20, 60*1);
	text(" D：掛け金プラス", 20, 60*2);
	text(" A：掛け金マイナス", 20, 60*3);
	text(" W,S:上下", 20, 60 * 4);
	text(" Q：ゲーム説明", 20, 60 * 5);
	text(" M：タイトルへも戻る", 20, 60 * 6);
	text("SPACE：決定、次へ", 20, 60*7);
	text("サイコロを振る", 20, 60 *8);
	text("1P:U, 2P:I, 3P:O, 4P:P", 20,60*9);

	text("ルール説明", 1020, 60);
	text("子が掛け金を決める", 1020, 60*2);
	text("全員がサイコロを振る", 1020, 60*3);
	text("親対子の対決で勝敗を決める", 1020, 60*4);
	text("親を交代して繰り返す", 1020, 60*5);
}

void TAITLE::settei() {
	fill(255);
	textSize(60);
	text("プレイ人数決定", 20, 60);
	if (isTrigger(KEY_S) && num[0] < 4 && Flag[0] == 0) num[0]++;
	if (isTrigger(KEY_W) && num[0] > 2 && Flag[0] == 0)num[0]--;
	/*
	if (num[0] == 1) {
		fill(255, 0, 0);
	}
	text("1人", 100, 150);
	fill(255);
	*/
	if (num[0] == 2) {
		fill(255, 0, 0);
	}
	text("2人", 100, 250);
	fill(255);
	if (num[0] == 3) {
		fill(255, 0, 0);
	}
	text("3人", 100, 350);
	fill(255);
	if (num[0] == 4) {
		fill(255, 0, 0);
	}
	text("4人", 100, 450);
	fill(255);

	text("ゲーム数(親の回数)", 600, 60);
	if (isTrigger(KEY_S) && num[1] < 3 && Flag[0] == 1 && Flag[1] == 0) num[1]++;
	if (isTrigger(KEY_W) && num[1] > 1 && Flag[0] == 1 && Flag[1] == 0)num[1]--;
	if (num[1] == 1) {
		fill(255, 0, 0);
	}
	text("1回", 700, 150);
	fill(255);
	if (num[1] == 2) {
		fill(255, 0, 0);
	}
	text("2回", 700, 250);
	fill(255);
	if (num[1] == 3) {
		fill(255, 0, 0);
	}
	text("3回", 700, 350);
	fill(255);

	if(Flag[1]==1)num[3] = num[0] * num[1];

	if (isTrigger(KEY_SPACE) && Flag[0] == 0)Flag[0] = 1;
	else if (isTrigger(KEY_SPACE) && Flag[1] == 0)Flag[1] = 1;
	else if (isTrigger(KEY_SPACE)) {
		if (num[0] == SORO - 1) State = SORO;
		if (num[0] != SORO - 1) State = MULTI;
	}
}

void TAITLE::gamesetumei() {
	clear(0, 0, 64);
	if (isTrigger(KEY_D) && num[2] < 3) num[2]++;
	if (isTrigger(KEY_A) && num[2] > 1)num[2]--;
	if (num[2] == 1) {
		setumei();
		text("1ページ目", 0, 1080);
	}
	else if (num[2] == 2) {
		saikoro.saihyouzi();
		text("2ページ目", 0, 1080);
	}
	else if (num[2] == 3) {
		settei();
		fill(255);
		text("3ページ目", 0, 1080);

	}
}

void TAITLE::hantei() {

	if (sai[0]->flagr() + sai[1]->flagr() + sai[2]->flagr() + sai[3]->flagr() == num[0]) {
		if (num[4] % num[0] != 0 && num[0] >= 1) {
			fill(255, 0, 0);
			sai[0]->syouhai(sai[num[4] % num[0]]->yakur(), sai[0]->yakur(), sai[num[4] % num[0]],sai[0]);
		}
		if (num[4] % num[0] != 1 && num[0] >= 2) {
			fill(255, 0, 0);
			sai[0]->syouhai(sai[num[4] % num[0]]->yakur(), sai[1]->yakur(), sai[num[4] % num[0]],sai[1]);
		}
		if (num[4] % num[0] != 2 && num[0] >= 3) {
			fill(255, 0, 0);
			sai[0]->syouhai(sai[num[4] % num[0]]->yakur(), sai[2]->yakur(), sai[num[4] % num[0]],sai[2]);
		}
		if (num[4] % num[0] != 3 && num[0] >= 4) {
			fill(255, 0, 0);
			sai[0]->syouhai(sai[num[4] % num[0]]->yakur(), sai[3]->yakur(), sai[num[4] % num[0]],sai[3]);
		}
		for (int i = 0;i < num[0];i++) {
			sai[i]->kakef();
		}
		if (isTrigger(KEY_SPACE)) {
			num[4] += 1;
			num[6] = 1;
			Flag[2] = 0;
			for (int i = 0;i < num[0];i++) {
				sai[i]->reset();
			}
		}
	}
}

void TAITLE::kekka() {
	int n[4] = {
	sai[0]->Coinr(),
	sai[1]->Coinr(),
	sai[2]->Coinr(),
	sai[3]->Coinr(),
	};
	int a[4] = { 1,2,3,4 };
	for (int i = 0;i < num[0] - 1;i++) {
		for (int j = i + 1;j < num[0];j++) {
			if (n[i] < n[j]) {
				int w = n[j];
				n[j] = n[i];
				n[i] = w;

				int w1 = a[j];
				a[j] = a[i];
				a[i] = w1;
			}
		}
	}
	for (int i = 0;i < num[0];i++) {
		textSize(100);
		text(i+1, 100, 200 + 150 * i);
		text("位", 150, 200 + 150 * i);
		text(n[i], 400, 200 + 150 * i);
		text("点", 600, 200 + 150 * i);
		text(a[i], 750, 200 + 150 * i);
		text("PLAYER", 800, 200 + 150 * i);
	}
}

void TAITLE::init() {
	 State = 0;
	 num[0] = 2;
	 num[1] = 1;
	 num[2] = 1;
	 num[3] = 0;
	 num[4] = 0;
	 num[5] = 0;
	 num[6] = 1;
	 for (int i = 0;i < 3;i++) {
		 Flag[i] = 0;
	 }
}