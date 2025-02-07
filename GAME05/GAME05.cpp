#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include"GAME05.h"
#include"TRAMP.h"
#include "../../libOne/inc/graphic.h"
#include"time.h"
namespace GAME05
{
	int GAME::create()
	{
		deck = new Card;

		char str[100];
		for (int i = 0; i <= 12; ++i) {
			sprintf_s(str, "..\\main\\assets\\game05\\TRAMP\\D%d.png", i + 1);
			DaiyaImg[i] = loadImage(str);
			sprintf_s(str, "..\\main\\assets\\game05\\TRAMP\\H%d.png", i + 1);
			HeartImg[i] = loadImage(str);
			sprintf_s(str, "..\\main\\assets\\game05\\TRAMP\\C%d.png", i + 1);
			CloverImg[i] = loadImage(str);
			sprintf_s(str, "..\\main\\assets\\game05\\TRAMP\\S%d.png", i + 1);
			SpadeImg[i] = loadImage(str);
		}

		HaimenImg = loadImage("..\\main\\assets\\game05\\haimen.png");
		TrampImg = loadImage("..\\main\\assets\\game05\\tramp.png");
		ChipImg = loadImage("..\\main\\assets\\game05\\chip.png");
		Chip_2Img = loadImage("..\\main\\assets\\game05\\chip_2.png");
		TamagoImg = loadImage("..\\main\\assets\\game05\\tamago.png");
		Egg1Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg2Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg3Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg4Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg5Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg6Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg7Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg8Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg9Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg10Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		Egg11Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
		WhiteImg = loadImage("..\\main\\assets\\game05\\white.png");
		GachaImg = loadImage("..\\main\\assets\\game05\\gacha.png");
		WinImg = loadImage("..\\main\\assets\\game05\\win.png");
		RuleImg = loadImage("..\\main\\assets\\game05\\RULE.png");
		Rule2Img = loadImage("..\\main\\assets\\game05\\RULE2.png");
		Rule3Img = loadImage("..\\main\\assets\\game05\\RULE3.png");
		ChikettoImg = loadImage("..\\main\\assets\\game05\\chiketto.png");
		Chiketto2Img = loadImage("..\\main\\assets\\game05\\chiketto2.png");
		SeggImg = loadImage("..\\main\\assets\\game05\\Segg.png");
		SresultImg = loadImage("..\\main\\assets\\game05\\Sresult.png");
		Sresult2Img = loadImage("..\\main\\assets\\game05\\Sresult2.png");
		ReggImg = loadImage("..\\main\\assets\\game05\\Regg.png");
		RresultImg = loadImage("..\\main\\assets\\game05\\Rresult.png");
		Rresult2Img = loadImage("..\\main\\assets\\game05\\Rresult2.png");

		DrawSnd = loadSound("..\\main\\assets\\game05\\draw.wav");
		WinSnd = loadSound("..\\main\\assets\\game05\\ジャジャーン.wav");
		straightWinSnd = loadSound("..\\main\\assets\\game05\\win.wav");
		LoseSnd = loadSound("..\\main\\assets\\game05\\lose.wav");
		BackSnd = loadSound("..\\main\\assets\\game05\\back.wav");
		PakaSnd = loadSound("..\\main\\assets\\game05\\パカ.wav");
		KakuteiSnd = loadSound("..\\main\\assets\\game05\\シャキーン.wav");
		GetSnd = loadSound("..\\main\\assets\\game05\\金額表示.wav");

		return 0;
	}

	void GAME::proc()
	{
		if (State == TITLE)Title();
		else if (State == CHANGEBETCOIN)ChangeBetCoin();
		else if (State == JOB)Job();
		else if (State == RULE)Rule();
		else if (State == RULEPAGE)RulePage();
		else if (State == RULEPAGE2)RulePage2();
		else if (State == PLAY)Play(deck);
		else if (State == SHOW)Show();
		else if (State == WIN)Win();
		else if (State == STRAIGHTWIN)StraightWin();
		else if (State == LOSE)Lose();
		else if (State == DRAW)Draw();
		else if (State == GACHA)Gacha();
		else if (State == RESULT)Result();
		else if (State == RESULT2)Result2();
		else if (State == BOX)Box();
		else if (State == PROB)Prob();
	}

	void GAME::destroy() {
		if (deck != nullptr) {
			delete deck;
			deck = nullptr;
		}
	}

	void GAME::initialCards(Card* deck)
	{
		int index = 0;
		for (int number = 1; number <= 13; ++number) {
			deck->CARD[index].num = number;
			deck->CARD[index].suit = 'H';
			deck->CARD[index].img = HeartImg[number - 1];
			++index;
		}
		for (int number = 1; number <= 13; ++number) {
			deck->CARD[index].num = number;
			deck->CARD[index].suit = 'D';
			deck->CARD[index].img = DaiyaImg[number - 1];
			++index;
		}
		for (int number = 1; number <= 13; ++number) {
			deck->CARD[index].num = number;
			deck->CARD[index].suit = 'S';
			deck->CARD[index].img = SpadeImg[number - 1];
			++index;
		}
		for (int number = 1; number <= 13; ++number) {
			deck->CARD[index].num = number;
			deck->CARD[index].suit = 'C';
			deck->CARD[index].img = CloverImg[number - 1];
			++index;
		}
	}

	void GAME::shuffleCards(Card* deck)
	{
		srand(time(NULL));
		for (int i = 0; i < 52; ++i) {
			int j = rand() % (i + 1);
			PlayingCard temp = deck->CARD[i];
			deck->CARD[i] = deck->CARD[j];
			deck->CARD[j] = temp;
		}
	}

	void GAME::Init()
	{
		straightWinCnt = 10;
		WinCnt = 0;
		Count = 0;
		CountDown = 100;
		SetImg[1] = HaimenImg;

		initialCards(deck);
		shuffleCards(deck);
		SetImg[0] = deck->CARD[0].img;
		SetNum[0] = deck->CARD[0].num;

		CardSetPx[0] = 955.0f;
		CardSetPy[0] = 225.0f;

		CardSetPx[1] = 955.0;
		CardSetPy[1] = 900.0f;

		HaimenPx = 1400.0f;
		HaimenPy = 240.0f;
	}

	void GAME::Title()
	{
		clear(15, 140, 34);
		fill(255, 0 ,0);
		hideCursor();
		textSize(200);
		text("HIGH", 450, 580);
		fill(255);
		text("＆", 850, 580);
		fill(0, 0, 255);
		text("LOW", 1080, 580);
		fill(255);
		textSize(100);
		text("S:ゲームスタート", 550, 780);
		fill(255);
		textSize(50);
		text("ゲームプレイ数:" + (let)PlayCnt, 0, 200);
		text("bet:" + (let)BetCoins + "コイン", 0, 300);
		text("R:遊び方", 0, 400);
		if (ChikettoCnt >= 99) {
			ChikettoCnt = 99;
			text(":" + (let)ChikettoCnt + "枚", 100, 500);
		}
		else {
			text(":" + (let)ChikettoCnt + "枚", 100, 500);
		}
		text("(所持上限:99枚)", 0, 580);
		text("(コインの所持上限:100000000コイン)", 300, 95);
		text("G:ガチャ(10+1連ガチャが無料で引ける回数:" + (let)freeCnt + "回)", 0, 850);
		text("C:賭けコイン変更", 0, 940);
		text("J:所持コインが0になったときに押してください。", 0, 1020);
		text("ENTERキーでメニューに戻る", 0, 1080);
		if (freeCnt <= 0) {
			freeCnt = 0;
		}
		rectMode(CENTER);
		image(ChipImg, 50, 70);
		image(Chiketto2Img, 50, 480);
		if (playerCoins >= 100000000) {
			playerCoins = 100000000;
			text((let)playerCoins, 80, 95);
		}
		else {
			text((let)playerCoins, 80, 95);
		}

		if (isTrigger(KEY_C)) {
			State = CHANGEBETCOIN;
		}

		if (isTrigger(KEY_S) && playerCoins >= BetCoins) {
			Init();
			playSound(DrawSnd);
			showCursor();
			playerCoins -= BetCoins;
			State = PLAY;
		}

		if (loopSnd) {
			playLoopSound(BackSnd);
			loopSnd = false;
		}

		if (isTrigger(KEY_R)) {
			State = RULE;
		}

		if (isTrigger(KEY_J) && playerCoins == 0) {
			Init();
			State = JOB;
		}

		if (isTrigger(KEY_G)) {
			Init2();
			State = GACHA;
		}

		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}

	void GAME::ChangeBetCoin()
	{
		clear(15, 140, 34);
		hideCursor();
		textSize(100);
		text("賭けコインを決めてください。", 300, 300);
		textSize(120);
		text("賭けるコイン数:", 50, 570);
		text("コイン", 1340, 570);
		textSize(200);
		text((let)BetCoins, 950, 600);

		textSize(80);
		text("U,↑:+100", 300, 700);
		text("D,↓:-100", 1200, 700);
		text("S:ゲームスタート", 600, 1050);
		text("※最大5000コインまで賭けれます。", 300, 850);
		textSize(50);
		text("B:タイトルに戻る",0, 1080);

		if (isPress(KEY_UP)) {
			BetCoins += 100;
			if (playerCoins > 5000) {
				if (BetCoins > 5000) {
					BetCoins = 5000;
				}
			}
			else {
				if (BetCoins > playerCoins) {
					BetCoins = playerCoins;
				}
			}
		}

		if (isTrigger(KEY_U)) {
			BetCoins += 100;
			if (playerCoins > 5000) {
				if (BetCoins > 5000) {
					BetCoins = 5000;
				}
			}
			else {
				if (BetCoins > playerCoins) {
					BetCoins = playerCoins;
				}
			}
		}

		if (isPress(KEY_DOWN)) {
			BetCoins -= 100;
			if (BetCoins < 100) {
				BetCoins = 100;
			}
		}

		if (isTrigger(KEY_D)) {
			BetCoins -= 100;
			if (BetCoins < 100) {
				BetCoins = 100;
			}
		}

		if (isTrigger(KEY_S) && playerCoins >= BetCoins) {
			Init();
			playSound(DrawSnd);
			showCursor();
			playerCoins -= BetCoins;
			GetCoins = BetCoins * 2;
			State = PLAY;
		}

		if (isTrigger(KEY_B)) {
			BetCoins = 100;
			State = TITLE;
		}
	}

	void GAME::Job()
	{
		clear(255);
		hideCursor();
		fill(0);
		textSize(50);
		if (Count == 1000) {
			image(Chip_2Img, 600, 450);
			textSize(200);
			text("×" + (let)Count + "枚", 750, 550);
			textSize(150);
			text("獲得しました。", 500, 750);
			if (CountDown > 0) {
				CountDown--;
			}
			else{
				playLoopSound(BackSnd);
				playSound(GetSnd);
				playerCoins += 1000;
				BetCoins = 100;
				GetCoins = BetCoins * 2;
				PlayCnt++;
				State = TITLE;
			}
		}
		else{
			text("所持コインが無くなりました...", 600, 100);
			text("ENTERを押してコインを1000枚ゲット", 500, 200);
			image(Chip_2Img, 600, 450);
			textSize(200);
			text("×" + (let)Count, 750, 550);
			if (isPress(KEY_ENTER)) {
				Count += 1000;
			}
		}
	}

	void GAME::Rule()
	{
		rectMode(CENTER);
		clear(100);
		hideCursor();
		text("遊び方", 880, 50);
		fill(255);
		text("・Sキーを押してゲームスタート!", 500, 150);
		text("・ゲーム画面に来たらHキーまたはLキーを押します。", 300, 250);
		text("・相手の数字よりも大きかったら勝ち、", 500, 350);
		text("  相手の数字よりも小さかったら負けです。", 500, 420);
		text("D, →:次のページへ", 1420, 100);
		text((let)PageCnt + "/" + "3", 1820, 200);
		text("← 小さい", 400, 500);
		text("大きい →", 1200,500);
		image(TrampImg, 900, 800);
		textSize(50);
		text("ENTER:タイトル", 0, 100);

		if (isTrigger(KEY_D) || isTrigger(KEY_RIGHT)) {
			PageCnt++;
			if (PageCnt > 2) {
				PageCnt = 2;
			}
			State = RULEPAGE;
		}

		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}

	void GAME::RulePage()
	{
		clear(100);
		hideCursor();
		rectMode(CENTER);
		fill(255);
		text("・1回勝つ毎に、もらえる枚数が2倍になります。", 400, 150);
		image(RuleImg, 350, 300);
		text("→", 650, 300);
		image(Rule2Img, 1000, 300);
		text("→", 1300, 300);
		image(Rule3Img, 1650, 300);
		text("・負けるともらえるコインは0枚です。", 500, 550);
		text("・勝って得たコインはゲームもしくはガチャに使えます。", 300, 650);
		text("・10回連続で勝てば、10+1連ガチャが無料で１回引けます。", 300, 750);
		text("  さらにガチャチケットも手に入ります。", 300, 800);
		text("・入手したガチャチケットは1枚消費でシングルガチャ1回、", 300, 900);
		text("　10枚消費で10+1連ガチャが1回回せます。", 300, 950);
		text("A, ←:前のページへ", 0, 100);
		text("D, →:次のページへ", 1400, 100);
		text((let)PageCnt + "/" + "3", 1820, 200);
		if (isTrigger(KEY_A) || isTrigger(KEY_LEFT)) {
			PageCnt--;
			if (PageCnt < 1) {
				PageCnt = 1;
			}
			State = RULE;
		}
		if (isTrigger(KEY_D) || isTrigger(KEY_RIGHT)) {
			PageCnt++;
			if (PageCnt < 3) {
				PageCnt = 3;
			}
			State = RULEPAGE2;
		}

		textSize(50);
		text("ENTER:タイトル", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}

	void GAME::RulePage2()
	{
		clear(100);
		hideCursor();
		rectMode(CENTER);
		text("ガチャについて", 800, 100);
		text("ガチャはシングルガチャと10+1連ガチャの2種類あります。", 300, 200);
		text("結果は以下の画像のように出ます。", 600, 300);
		text("シングルガチャ", 250, 400);
		image(SeggImg, 200, 530);
		text("→", 375, 550);
		image(SresultImg, 600, 530);
		text("10+1連ガチャ", 1250, 400);
		image(ReggImg, 1200, 530);
		text("→", 1375, 550);
		image(RresultImg, 1600, 530);
		text("シングルガチャ、10+1連ガチャ共に左上に★7確定の文字が出ると", 200, 680);
		text("★7の名前の部分が金色になって出てきます。", 450, 780);
		image(Sresult2Img, 600, 920);
		image(Rresult2Img, 1300, 920);
		text("A, ←:前のページへ", 0, 100);
		text((let)PageCnt + "/" + "3", 0, 200);
		if (isTrigger(KEY_A) || isTrigger(KEY_LEFT)) {
			PageCnt--;
			if (PageCnt <= 2) {
				PageCnt = 2;
			}
			State = RULEPAGE;
		}

		textSize(50);
		text("ENTER:タイトル", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}

	void GAME::Play(Card* deck)
	{
		clear(15, 140, 34);
		hideCursor();
		fill(255);
		textSize(150);
		text("H", 450, 590);
		textSize(100);
		text("か", 550, 580);
		textSize(150);
		text("L", 650, 590);
		textSize(100);
		text("を押してください", 750, 580);

		//画像切替
		if ((isTrigger(KEY_H)) || (isTrigger(KEY_L))) {
			playSound(DrawSnd);
			SetImg[1] = deck->CARD[1].img;
			SetNum[1] = deck->CARD[1].num;
			if (isTrigger(KEY_H)) {
				textSize(150);
				fill(255, 0, 0);
				text("H", 450, 590);
			}
			else {
				textSize(150);
				fill(0, 0, 255);
				text("L", 650, 590);
			}

			//相手の数字より自分の数字が大きいとき
			if (isTrigger(KEY_H) && SetNum[0] < SetNum[1] ||
				isTrigger(KEY_L) && SetNum[0] > SetNum[1]) {
				winFlag = true;
				State = SHOW;
			}

			//相手の数字より自分の数字が小さいとき
			if (playerCoins > 0 && isTrigger(KEY_H) && SetNum[0] > SetNum[1] ||
				isTrigger(KEY_L) && SetNum[0] < SetNum[1]) {
				loseFlag = true;
				State = SHOW;
			}

			//相手の数字と自分の数字が同じ大きさのとき
			if (isTrigger(KEY_H) && SetNum[0] == SetNum[1] ||
				isTrigger(KEY_L) && SetNum[0] == SetNum[1]){
				drawFlag = true;
				State = SHOW;
			}

			//所持コインが0で負けたとき
			if (playerCoins == 0 && (isTrigger(KEY_H) && SetNum[0] > SetNum[1] ||
				isTrigger(KEY_L) && SetNum[0] < SetNum[1])) {
				jobFlag = true;
				State = SHOW;
			}

			//9連勝していてかつ相手の数字より自分の数字が大きいとき
			if (WinCnt == 9 && (isTrigger(KEY_H) && SetNum[0] < SetNum[1] ||
				isTrigger(KEY_L) && SetNum[0] > SetNum[1])) {
				straightWinFlag = true;
				State = SHOW;
			}
		}
		draw();
	}

	void GAME::Show()
	{
		if (winFlag == true) {
			winFlag = false;
			Sleep(800);
			if (WinCnt < 9) {
				playSound(WinSnd);
			}
			State = WIN;
		}
		if (loseFlag == true) {
			loseFlag = false;
			Sleep(800);
			if (playerCoins > 0) {
				playSound(LoseSnd);
			}
			stopSound(BackSnd);
			State = LOSE;
		}
		if (drawFlag == true) {
			drawFlag = false;
			Sleep(800);
			State = DRAW;
		}
		if (jobFlag == true) {
			jobFlag = false;
			Sleep(400);
			stopSound(BackSnd);
			stopSound(LoseSnd);
			State = JOB;
		}
		if (straightWinFlag == true) {
			straightWinFlag = false;
			Sleep(500);
			playSound(straightWinSnd);
			stopSound(BackSnd);
			State = STRAIGHTWIN;
		}
	}

	void GAME::Win()
	{
		clear(15, 140, 34);
		fill(255);
		textSize(100);
		text("勝ちました！", 700, 200);
		text("ゲームを続けますか?", 500, 400);
		text("Y:ゲームを続ける", 600, 600);
		text("N:タイトル画面に戻る", 500, 800);
		text("配当:", 500, 900);
		fill(211, 202, 71);
		text((let)GetCoins, 750, 900);
		fill(255);
		text("コイン", 1300, 900);

		if (isTrigger(KEY_Y)) {
			WinCnt++;
			GetCoins *= 2;
			SetImg[0] = SetImg[1];
			SetNum[0] = SetNum[1];
			shuffleCards(deck);
			SetImg[1] = HaimenImg;
			playSound(DrawSnd);
			stopSound(WinSnd);
			State = PLAY;
		}

		if (isTrigger(KEY_C)) {
			WinCnt += 9;
			GetCoins += 51200;
			SetImg[0] = SetImg[1];
			SetNum[0] = SetNum[1];
			shuffleCards(deck);
			SetImg[1] = HaimenImg;
			playSound(DrawSnd);
			stopSound(WinSnd);
			State = PLAY;
		}
		
		if (isTrigger(KEY_N)) {
			playerCoins += GetCoins;
			WinCnt = 0;
			PlayCnt++;
			BetCoins = BetCoins;
			GetCoins = BetCoins * 2;
			playSound(GetSnd);
			State = TITLE;
		}
	}

	void GAME::StraightWin()
	{
		clear(255);
		fill(213, 202, 112);
		rectMode(CORNER);
		image(WinImg, 200, 0);
		textSize(50);
		text("10+1連ガチャが1回無料!", 0, 980);
		fill(0);
		textSize(50);
		text("ENTERキーでタイトルに戻る", 0, 1080);
		image(Chiketto2Img, 0, 820);
		text("1枚ゲット!", 100, 880);
		if (isTrigger(KEY_ENTER)) {
			playerCoins += GetCoins;
			WinCnt = 0;
			freeCnt++; 
			PlayCnt++;
			ChikettoCnt++;
			playLoopSound(BackSnd);
			stopSound(straightWinSnd);
			BetCoins = BetCoins;
			GetCoins = BetCoins * 2;
			playSound(GetSnd);
			State = TITLE;
		}
	}

	void GAME::Lose()
	{
		clear(15, 140, 34);
		fill(255);
		textSize(100);
		text("負けました…", 600, 540);
		textSize(50);
		text("ENTERでタイトルへ", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			WinCnt = 0;
			PlayCnt++;
			stopSound(LoseSnd);
			playLoopSound(BackSnd);
			BetCoins = BetCoins;
			if (BetCoins > playerCoins) {
				BetCoins = 100;
			}
			GetCoins = BetCoins * 2;
			State = TITLE;
		}
	}

	void GAME::Draw()
	{
		clear(15, 140, 34);
		fill(255);
		textSize(100);
		text("DRAW", 820, 540);
		text("ENTERでもう一回", 500, 640);
		if (isTrigger(KEY_ENTER)) {
			SetImg[0] = SetImg[1];
			SetNum[0] = SetNum[1];
			shuffleCards(deck);
			SetImg[1] = HaimenImg;
			State = PLAY;
		}
	}

	void GAME::Init2()
	{
		TotalProb5 = 58.8f;
		TotalProb6 = 87.5f;
		TotalProb7 = 99.7f;
		confirm = random() % 100;
		confirm1 = random() % 100; confirm2 = random() % 100; confirm3 = random() % 100; confirm4 = random() % 100; confirm5 = random() % 100;
		confirm6 = random() % 100; confirm7 = random() % 100; confirm8 = random() % 100; confirm9 = random() % 100; confirm10 = random() % 100;
		confirm11 = random() % 100;
		sFrameCnt = 100.0f;
		rFrameCnt = 500.0f;

		s0 = random() % 100 + 1;
		r1 = random() % 100 + 1, r2 = random() % 100 + 1, r3 = random() % 100 + 1, r4 = random() % 100 + 1, r5 = random() % 100 + 1,
		r6 = random() % 100 + 1, r7 = random() % 100 + 1, r8 = random() % 100 + 1, r9 = random() % 100 + 1, r10 = random() % 100 + 1;
		r11 = random() % 100 + 1;

		rare4Total = 10; rare5Total = 9; rare6Total = 8; rare7Total = 7;

		randrare4 = random() % rare4Total; randrare5 = random() % rare5Total;
		randrare6 = random() % rare6Total; randrare7 = random() % rare7Total;

		randrare4_1 = random() % rare4Total; randrare5_1 = random() % rare5Total;
		randrare6_1 = random() % rare6Total; randrare7_1 = random() % rare7Total;

		randrare4_2 = random() % rare4Total; randrare5_2 = random() % rare5Total;
		randrare6_2 = random() % rare6Total; randrare7_2 = random() % rare7Total;

		randrare4_3 = random() % rare4Total; randrare5_3 = random() % rare5Total;
		randrare6_3 = random() % rare6Total; randrare7_3 = random() % rare7Total;

		randrare4_4 = random() % rare4Total; randrare5_4 = random() % rare5Total;
		randrare6_4 = random() % rare6Total; randrare7_4 = random() % rare7Total;

		randrare4_5 = random() % rare4Total; randrare5_5 = random() % rare5Total;
		randrare6_5 = random() % rare6Total; randrare7_5 = random() % rare7Total;

		randrare4_6 = random() % rare4Total; randrare5_6 = random() % rare5Total;
		randrare6_6 = random() % rare6Total; randrare7_6 = random() % rare7Total;

		randrare4_7 = random() % rare4Total; randrare5_7 = random() % rare5Total;
		randrare6_7 = random() % rare6Total; randrare7_7 = random() % rare7Total;

		randrare4_8 = random() % rare4Total; randrare5_8 = random() % rare5Total;
		randrare6_8 = random() % rare6Total; randrare7_8 = random() % rare7Total;

		randrare4_9 = random() % rare4Total; randrare5_9 = random() % rare5Total;
		randrare6_9 = random() % rare6Total; randrare7_9 = random() % rare7Total;

		randrare4_10 = random() % rare4Total; randrare5_10 = random() % rare5Total;
		randrare6_10 = random() % rare6Total; randrare7_10 = random() % rare7Total;

		randrare4_11 = random() % rare4Total; randrare5_11 = random() % rare5Total;
		randrare6_11 = random() % rare6Total; randrare7_11 = random() % rare7Total;

		sPx = 200.0f, sPy = 560.0f;
		r1Px = 10.0f; r1Py = 260.0f;
		r2Px = 650.0f; r3Px = 1300.0f;
		r4Py = 460.0f; r7Py = 660.0f;
		r10Px = 300.0f; r10Py = 860.0f;
		r11Px = 1050.0f;
	}

	void GAME::Gacha()
	{
		clear(255);
		rectMode(CORNER);
		image(GachaImg, 0, 0);
		image(GachaImg, 0, 400);
		image(GachaImg, 0, 800);
		image(GachaImg, 960, 0);
		image(GachaImg, 960, 400);
		image(GachaImg, 960, 800); 
		rectMode(CENTER);
		image(ChipImg, 50, 70);
		image(Chiketto2Img, 400, 70);
		fill(0);
		textSize(50);
		if (playerCoins >= 100000000) {
			playerCoins = 100000000;
			text((let)playerCoins, 80, 95);
		}
		else {
			text((let)playerCoins, 80, 95);
		}
		if (ChikettoCnt >= 99) {
			ChikettoCnt = 99;
			text(":" + (let)ChikettoCnt + "枚所持", 450, 90);
		}
		else {
			text(":" + (let)ChikettoCnt + "枚所持", 450, 90);
		}
		text("B:獲得キャラ一覧", 600, 1080);
		text("P:排出確率", 1200, 1080);
		text("ENTERでタイトルへ", 0, 1080);
		if (freeCnt <= 0 && ChikettoCnt <= 0 && playerCoins < 5000){
			textSize(100);
			fill(255, 0, 0);
			text("コイン不足の為、ガチャが引けません。", 100, 320);
			textSize(120);
			fill(0);
			text("S:シングルガチャ:", 50, 500);
			text("R:10+1連ガチャ:", 50, 800);
			fill(255, 0, 0);
			text("5000コイン", 1100, 500);
			fill(255, 0, 0);
			text("50000コイン", 1000, 800);
		}
		else if(freeCnt <= 0 && ChikettoCnt <= 0 && playerCoins >= 5000 && playerCoins < 50000) {
			textSize(120);
			fill(0);
			text("S:シングルガチャ: 5000コイン", 50, 500);
			text("R:10+1連ガチャ:", 50, 800);
			fill(255, 0, 0);
			text("50000コイン", 950, 800);
		}
		else if (freeCnt <= 0 && ChikettoCnt <= 0 && playerCoins >= 50000) {
			textSize(120);
			fill(0);
			text("S:シングルガチャ: 5000コイン", 100, 500);
			text("R:10+1連ガチャ: 50000コイン", 100, 800);
		}
		else if (freeCnt >= 1 && ChikettoCnt >= 1 && ChikettoCnt <= 9) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ: あと" + (let)freeCnt + "回無料", 50, 800);
		}
		else if (freeCnt <= 0 && ChikettoCnt >= 1 && ChikettoCnt <= 9 && playerCoins >= 50000) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ: 50000コイン", 100, 800);
		}
		else if (freeCnt <= 0 && ChikettoCnt >= 1 && ChikettoCnt <= 9 && playerCoins >= 5000 && playerCoins < 50000) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ:", 50, 800);
			fill(255, 0, 0);
			text("50000コイン", 950, 800);
		}
		else if (freeCnt <= 0 && ChikettoCnt >= 1 && ChikettoCnt <= 9 && playerCoins < 5000) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ:", 50, 800);
			fill(255, 0, 0);
			text("50000コイン", 950, 800);
		}
		else if (freeCnt >= 1 && ChikettoCnt <= 0 && playerCoins < 5000) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			fill(255, 0, 0);
			text("5000コイン", 1100, 500);
			fill(0);
			textSize(110);
			text("R:10+1連ガチャ: あと" + (let)freeCnt + "回無料", 50, 800);
		}
		else if (freeCnt >= 1 && ChikettoCnt <= 0 && playerCoins >= 5000) {
			textSize(120);
			text("S:シングルガチャ: 5000コイン", 50, 500);
			textSize(110);
			text("R:10+1連ガチャ: あと" + (let)freeCnt + "回無料", 50, 800);
		}
		else if (freeCnt <= 0 && ChikettoCnt >= 1 && ChikettoCnt <= 9 && playerCoins >= 5000) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ:", 50, 800);
			fill(255, 0, 0);
			text("50000コイン", 950, 800);
		}
		else if (freeCnt >= 1 && ChikettoCnt >= 1 && ChikettoCnt <= 9) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ: あと" + (let)freeCnt + "回無料", 50, 800);
		}
		else if (freeCnt >= 0 && ChikettoCnt >= 10) {
			textSize(120);
			text("S:シングルガチャ:", 50, 500);
			image(ChikettoImg, 1180, 450);
			text("消費:1枚", 1280, 500);
			textSize(110);
			text("R:10+1連ガチャ:", 50, 800);
			image(ChikettoImg, 1130, 750);
			text("消費:10枚", 1280, 800);
		}

		textSize(100);
		fill(0);
		text("※チケットから優先的に消費されます。", 100, 1000);

		if (isTrigger(KEY_S) && playerCoins >= 5000 && ChikettoCnt <= 0) {
			Init2();
			playerCoins -= 5000;
			clear(255);
			image(TamagoImg, width / 2, height / 2);
			playSound(PakaSnd);
			if (confirm == 1) {
				playSound(KakuteiSnd);
			}
			State = RESULT;
		}

		if (isTrigger(KEY_S) && ChikettoCnt > 0) {
			Init2();
			ChikettoCnt--;
			clear(255);
			image(TamagoImg, width / 2, height / 2);
			playSound(PakaSnd);
			if (confirm == 1) {
				playSound(KakuteiSnd);
			}
			State = RESULT;
		}


		if (isTrigger(KEY_R) && playerCoins >= 50000 && freeCnt <= 0) {
			Init2();
			playerCoins -= 50000;
			clear(255);
			image(Egg1Img, 300, 220);
			image(Egg2Img, 950, 220);
			image(Egg3Img, 1600, 220);
			image(Egg4Img, 300, 420);
			image(Egg5Img, 950, 420);
			image(Egg6Img, 1600, 420);
			image(Egg7Img, 300, 620);
			image(Egg8Img, 950, 620);
			image(Egg9Img, 1600, 620);
			image(Egg10Img, 540, 820);
			image(Egg11Img, 1260, 820);
			playSound(PakaSnd);
			if (confirm1 == 1 || confirm2 == 2 || confirm3 == 3 || confirm4 == 4 || confirm5 == 5 ||
				confirm6 == 6 || confirm7 == 7 || confirm8 == 8 || confirm9 == 9 || confirm10 == 10 ||
				confirm11 == 11) {
				playSound(KakuteiSnd);
			}
			State = RESULT2;
		}

		if (isTrigger(KEY_R) && ChikettoCnt >= 10) {
			Init2();
			ChikettoCnt -= 10;
			clear(255);
			image(Egg1Img, 300, 220);
			image(Egg2Img, 950, 220);
			image(Egg3Img, 1600, 220);
			image(Egg4Img, 300, 420);
			image(Egg5Img, 950, 420);
			image(Egg6Img, 1600, 420);
			image(Egg7Img, 300, 620);
			image(Egg8Img, 950, 620);
			image(Egg9Img, 1600, 620);
			image(Egg10Img, 540, 820);
			image(Egg11Img, 1260, 820);
			playSound(PakaSnd);
			if (confirm1 == 1 || confirm2 == 2 || confirm3 == 3 || confirm4 == 4 || confirm5 == 5 ||
				confirm6 == 6 || confirm7 == 7 || confirm8 == 8 || confirm9 == 9 || confirm10 == 10 ||
				confirm11 == 11) {
				playSound(KakuteiSnd);
			}
			State = RESULT2;
		}
		else if (isTrigger(KEY_R) && freeCnt > 0) {
			Init2();
			freeCnt--;
			clear(255);
			image(Egg1Img, 300, 220);
			image(Egg2Img, 950, 220);
			image(Egg3Img, 1600, 220);
			image(Egg4Img, 300, 420);
			image(Egg5Img, 950, 420);
			image(Egg6Img, 1600, 420);
			image(Egg7Img, 300, 620);
			image(Egg8Img, 950, 620);
			image(Egg9Img, 1600, 620);
			image(Egg10Img, 540, 820);
			image(Egg11Img, 1260, 820);
			playSound(PakaSnd);
			if (confirm1 == 1 || confirm2 == 2 || confirm3 == 3 || confirm4 == 4 || confirm5 == 5 ||
				confirm6 == 6 || confirm7 == 7 || confirm8 == 8 || confirm9 == 9 || confirm10 == 10 ||
				confirm11 == 11) {
				playSound(KakuteiSnd);
			}
			State = RESULT2;
		}

		if (isTrigger(KEY_B)) {
			State = BOX;
		}

		if (isTrigger(KEY_P)) {
			Init2();
			State = PROB;
		}

		if (isTrigger(KEY_ENTER)) {
			if (BetCoins > playerCoins) {
				BetCoins = 100;
			}
			State = TITLE;
		}
	}

	void GAME::Result()
	{
		if (confirm == 1) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
			playSound(KakuteiSnd);
		}
		if (sFrameCnt < 60) {
			TamagoImg = WhiteImg;
			image(TamagoImg, width / 2, height / 2);
			if (confirm == 1) {
				fill(213, 202, 112);
				textSize(210);
				text("☆7:" + (let)rare7[randrare7].name, sPx, sPy);
				if (rare7[randrare7].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1100, 380);
				}
			}
			else {
				if (s0 > TotalProb7) {
					fill(213, 202, 112);
					textSize(210);
					text("☆7:", sPx, sPy);
					fill(0);
					text((let)rare7[randrare7].name, 600, sPy);
					if (rare7[randrare7].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1100, 380);
					}
				}
				else if (s0 > TotalProb6) {
					fill(0);
					textSize(210);
					text("☆6:" + (let)rare6[randrare6].name, sPx, sPy);
						if (rare6[randrare6].getCnt <= 0) {
							fill(255, 0, 0);
							text("NEW", 1100, 380);
						}
				}
				else if (s0 > TotalProb5) {
					fill(0);
					textSize(210);
					text("☆5:" + (let)rare5[randrare5].name, sPx, sPy);
					if (rare5[randrare5].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1100, 380);
					}
				}
				else {
					fill(0);
					textSize(210);
					text("☆4:" + (let)rare4[randrare4].name, sPx, sPy);
					if (rare4[randrare4].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1100, 380);
					}
				}
			}
		}
		if (sFrameCnt <= 0.5f) {
			if (confirm == 1) {
				rare7[randrare7].getCnt += 1;
			}
			else {
				if (s0 > TotalProb7) {
					rare7[randrare7].getCnt += 1;
					
				}
				else if (s0 > TotalProb6) {
					rare6[randrare6].getCnt += 1;
				}
				else if (s0 > TotalProb5) {
					rare5[randrare5].getCnt += 1;
				}
				else {
					rare4[randrare4].getCnt += 1;
				}
			}
		}
		if (sFrameCnt > 0) {
			sFrameCnt--;
		}
		else{
			TamagoImg = loadImage("..\\main\\assets\\game05\\tamago.png");
			State = GACHA;
		}
	}

	void GAME::Result2()
	{
		//1
		if (confirm1 == 1) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 460.0f) {
			Egg1Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg1Img, 300, 220);
			if (confirm1 == 1) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_1].name, r1Px, r1Py);
				if (rare7[randrare7_1].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 380, 190);
				}
			}
			else {
				if (r1 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r1Px, r1Py);
					fill(0);
					text((let)rare7[randrare7_1].name, 160, r1Py);
					if (rare7[randrare7_1].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 190);
					}
				}
				else if (r1 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_1].name, r1Px, r1Py);
					if (rare6[randrare6_1].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 190);
					}
				}
				else if (r1 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_1].name, r1Px, r1Py);
					if (rare5[randrare5_1].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 190);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_1].name, r1Px, r1Py);
					if (rare4[randrare4_1].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 190);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm1 == 1) {
					rare7[randrare7_1].getCnt += 1;
				}
				else {
					if (r1 > TotalProb7){
						rare7[randrare7_1].getCnt += 1;
					}
					else if (r1 > TotalProb6) {
						rare6[randrare6_1].getCnt += 1;
					}
					else if (r1 > TotalProb5) {
						rare5[randrare5_1].getCnt += 1;
					}
					else {
						rare4[randrare4_1].getCnt += 1;
					}
				}
			}
		}
		//2
		if (confirm2 == 2) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80); 
		if (rFrameCnt < 420.0f) {
			Egg2Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg2Img, 950, 220);
			if (confirm2 == 2) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_2].name, r2Px, r1Py);
				if (rare7[randrare7_2].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1000, 190);
				}
			}
			else {
				if (r2 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", 650.0f, r1Py);
					fill(0);
					text((let)rare7[randrare7_2].name, 820.0f, r1Py);
					if (rare7[randrare7_2].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 190);
					}
				}
				else if (r2 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_2].name, r2Px, r1Py);
					if (rare6[randrare6_2].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 190);
					}
				}
				else if (r2 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_2].name, r2Px, r1Py);
					if (rare5[randrare5_2].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 190);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_2].name, r2Px, r1Py);
					if (rare4[randrare4_2].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 190);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm2 == 2) {
					rare7[randrare7_2].getCnt += 1;
				}
				else {
					if (r2 > TotalProb7) {
						rare7[randrare7_2].getCnt += 1;
					}
					else if (r2 > TotalProb6) {
						rare6[randrare6_2].getCnt += 1;
					}
					else if (r2 > TotalProb5) {
						rare5[randrare5_2].getCnt += 1;
					}
					else {
						rare4[randrare4_2].getCnt += 1;
					}
				}
			}
		}
		//3
		if (confirm3 == 3) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 380.0f) {
			Egg3Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg3Img, 1600, 220);
			if (confirm3 == 3) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_3].name, r3Px, r1Py);
				if (rare7[randrare7_3].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1660, 190);
				}
			}
			else {
				if (r3 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r3Px, r1Py);
					fill(0);
					text((let)rare7[randrare7_3].name, 1470, r1Py);
					if (rare7[randrare7_3].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 190);
					}
				}
				else if (r3 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_3].name, r3Px, r1Py);
					if (rare6[randrare6_3].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 190);
					}
				}
				else if (r3 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_3].name, r3Px, r1Py);
					if (rare5[randrare5_3].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 190);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_3].name, r3Px, r1Py);
					if (rare4[randrare4_3].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 190);
					}
				}
			}if (rFrameCnt <= 0.5f) {
				if (confirm3 == 3) {
					rare7[randrare7_3].getCnt += 1;
				}
				else {
					if (r3 > TotalProb7) {
						rare7[randrare7_3].getCnt += 1;
					}
					else if (r3 > TotalProb6) {
						rare6[randrare6_3].getCnt += 1;
					}
					else if (r3 > TotalProb5) {
						rare5[randrare5_3].getCnt += 1;
					}
					else {
						rare4[randrare4_3].getCnt += 1;
					}
				}
			}
		}
		//4
		if (confirm4 == 4) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 340.0f) {
			Egg4Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg4Img, 300, 420);
			if (confirm4 == 4) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_4].name, r1Px, r4Py);
				if (rare7[randrare7_4].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 380, 380);
				}
			}
			else {
				if (r4 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r1Px, r4Py);
					fill(0);
					text((let)rare7[randrare7_4].name, 160, r4Py);
					if (rare7[randrare7_4].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 380);
					}
				}
				else if (r4 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_4].name, r1Px, r4Py);
					if (rare6[randrare6_4].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 380);
					}
				}
				else if (r4 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_4].name, r1Px, r4Py);
					if (rare5[randrare5_4].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 380);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_4].name, r1Px, r4Py);
					if (rare4[randrare4_4].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 380);
					}
				}
			}if (rFrameCnt <= 0.5f) {
				if (confirm4 == 4) {
					rare7[randrare7_4].getCnt += 1;
				}
				else {
					if (r4 > TotalProb7) {
						rare7[randrare7_4].getCnt += 1;
					}
					else if (r4 > TotalProb6) {
						rare6[randrare6_4].getCnt += 1;
					}
					else if (r4 > TotalProb5) {
						rare5[randrare5_4].getCnt += 1;
					}
					else {
						rare4[randrare4_4].getCnt += 1;
					}
				}
			}
		}
		//5
		if (confirm5 == 5) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 300.0f) {
			Egg5Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg5Img, 950, 420);
			if (confirm5 == 5) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_5].name, r2Px, r4Py);
				if (rare7[randrare7_5].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1000, 380);
				}
			}
			else {
				if (r5 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", 650, r4Py);
					fill(0);
					text((let)rare7[randrare7_5].name, 820, r4Py);
					if (rare7[randrare7_5].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 380);
					}
				}
				else if (r5 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_5].name, r2Px, r4Py);
					if (rare6[randrare6_5].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 380);
					}
				}
				else if (r5 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_5].name, r2Px, r4Py);
					if (rare5[randrare5_5].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 380);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_5].name, r2Px, r4Py);
					if (rare4[randrare4_5].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 380);
					}
				}
			}if (rFrameCnt <= 0.5f) {
				if (confirm5 == 5) {
					rare7[randrare7_5].getCnt += 1;
				}
				else {
					if (r5 > TotalProb7) {
						rare7[randrare7_5].getCnt += 1;
					}
					else if (r5 > TotalProb6) {
						rare6[randrare6_5].getCnt += 1;
					}
					else if (r5 > TotalProb5) {
						rare5[randrare5_5].getCnt += 1;
					}
					else {
						rare4[randrare4_5].getCnt += 1;
					}
				}
			}
		}
		//6
		if (confirm6 == 6) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 260.0f) {
			
			Egg6Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg6Img, 1600, 420);
			if (confirm6 == 6) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_6].name, r3Px, r4Py);
				if (rare7[randrare7_6].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1660, 380);
				}
			}
			else {
				if (r6 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r3Px, r4Py);
					fill(0);
					text((let)rare7[randrare7_6].name, 1470, r4Py);
					if (rare7[randrare7_6].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 380);
					}
				}
				else if (r6 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_6].name, r3Px, r4Py);
					if (rare6[randrare6_6].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 380);
					}
				}
				else if (r6 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_6].name, r3Px, r4Py);
					if (rare5[randrare5_6].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 380);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_6].name, r3Px, r4Py);
					if (rare4[randrare4_6].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 380);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm6 == 6) {
					rare7[randrare7_6].getCnt += 1;
				}
				else {
					if (r6 > TotalProb7) {
						rare7[randrare7_6].getCnt += 1;
					}
					else if (r6 > TotalProb6) {
						rare6[randrare6_6].getCnt += 1;
					}
					else if (r6 > TotalProb5) {
						rare5[randrare5_6].getCnt += 1;
					}
					else {
						rare4[randrare4_6].getCnt += 1;
					}
				}
			}
		}
		//7
		if (confirm7 == 7) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 220.0f) {
			
			Egg7Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg7Img, 300, 620);
			if (confirm7 == 7) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_7].name, r1Px, r7Py);
				if (rare7[randrare7_7].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 380, 570);
				}
			}
			else {
				if (r7 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r1Px, r7Py);
					fill(0);
					text((let)rare7[randrare7_7].name, 160, r7Py);
					if (rare7[randrare7_7].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 570);
					}
				}
				else if (r7 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_7].name, r1Px, r7Py);
					if (rare6[randrare6_7].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 570);
					}
				}
				else if (r7 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_7].name, r1Px, r7Py);
					if (rare5[randrare5_7].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 570);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_7].name, r1Px, r7Py);
					if (rare4[randrare4_7].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 380, 570);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm7 == 7) {
					rare7[randrare7_7].getCnt += 1;
				}
				else {
					if (r7 > TotalProb7) {
						rare7[randrare7_7].getCnt += 1;
					}
					else if (r7 > TotalProb6) {
						rare6[randrare6_7].getCnt += 1;
					}
					else if (r7 > TotalProb5) {
						rare5[randrare5_7].getCnt += 1;
					}
					else {
						rare4[randrare4_7].getCnt += 1;
					}
				}
			}
		}
		//8
		if (confirm8 == 8) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 180.0f) {
			Egg8Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg8Img, 950, 620);
			if (confirm8 == 8) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_8].name, r2Px, r7Py);
				if (rare7[randrare7_8].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1000, 570);
				}
			}
			else {
				if (r8 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", 650, r7Py);
					fill(0);
					text((let)rare7[randrare7_8].name, 820, r7Py);
					if (rare7[randrare7_8].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 570);
					}
				}
				else if (r8 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_8].name, r2Px, r7Py);
					if (rare6[randrare6_8].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 570);
					}
				}
				else if (r8 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_8].name, r2Px, r7Py);
					if (rare5[randrare5_8].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 570);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_8].name, r2Px, r7Py);
					if (rare4[randrare4_8].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1000, 570);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm8 == 8) {
					rare7[randrare7_8].getCnt += 1;
				}
				else {
					if (r8 > TotalProb7) {
						rare7[randrare7_8].getCnt += 1;
					}
					else if (r8 > TotalProb6) {
						rare6[randrare6_8].getCnt += 1;
					}
					else if (r8 > TotalProb5) {
						rare5[randrare5_8].getCnt += 1;
					}
					else {
						rare4[randrare4_8].getCnt += 1;
					}
				}
			}
		}
		//9
		if (confirm9 == 9) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 140.0f) {
			Egg9Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg9Img, 1600, 620);
			if (confirm9 == 9) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_9].name, r3Px, r7Py);
				if (rare7[randrare7_9].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1660, 570);
				}
			}
			else {
				if (r9 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r3Px, r7Py);
					fill(0);
					text((let)rare7[randrare7_9].name, 1470, r7Py);
					if (rare7[randrare7_9].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 570);
					}
				}
				else if (r9 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_9].name, r3Px, r7Py);
					if (rare6[randrare6_9].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 570);
					}
				}
				else if (r9 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_9].name, r3Px, r7Py);
					if (rare5[randrare5_9].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 570);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_9].name, r3Px, r7Py);
					if (rare4[randrare4_9].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1660, 570);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm9 == 9) {
					rare7[randrare7_9].getCnt += 1;
				}
				else {
					if (r9 > TotalProb7) {
						rare7[randrare7_9].getCnt += 1;
					}
					else if (r9 > TotalProb6) {
						rare6[randrare6_9].getCnt += 1;
					}
					else if (r9 > TotalProb5) {
						rare5[randrare5_9].getCnt += 1;
					}
					else {
						rare4[randrare4_9].getCnt += 1;
					}
				}
			}
		}
		//10
		if (confirm10 == 10) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 100.0f) {
			Egg10Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg10Img, 540, 820);
			if (confirm10 == 10) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_10].name, r10Px, r10Py);
				if (rare7[randrare7_10].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 650, 780);
				}
			}
			else {
				if (r10 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", r10Px, r10Py);
					fill(0);
					text((let)rare7[randrare7_10].name, 450, r10Py);
					if (rare7[randrare7_10].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 650, 780);
					}
				}
				else if (r10 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_10].name, r10Px, r10Py);
					if (rare6[randrare6_10].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 650, 780);
					}
				}
				else if (r10 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_10].name, r10Px, r10Py);
					if (rare5[randrare5_10].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 650, 780);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_10].name, r10Px, r10Py);
					if (rare4[randrare4_10].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 650, 780);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm10 == 10) {
					rare7[randrare7_10].getCnt += 1;
				}
				else {
					if (r10 > TotalProb7) {
						rare7[randrare7_10].getCnt += 1;
					}
					else if (r10 > TotalProb6) {
						rare6[randrare6_10].getCnt += 1;
					}
					else if (r10 > TotalProb5) {
						rare5[randrare5_10].getCnt += 1;
					}
					else {
						rare4[randrare4_10].getCnt += 1;
					}
				}
			}
		}
		//11
		if (confirm11 == 11) {
			fill(0);
			textSize(50);
			text("☆7確定!", 0, 100);
		}
		textSize(80);
		if (rFrameCnt < 60.0f) {
			Egg11Img = loadImage("..\\main\\assets\\game05\\white2.png");
			image(Egg11Img, 1150, 820);
			if (confirm11 == 11) {
				fill(213, 202, 112);
				text("☆7:" + (let)rare7[randrare7_11].name, r11Px, r10Py);
				if (rare7[randrare7_11].getCnt <= 0) {
					fill(255, 0, 0);
					text("NEW", 1400, 780);
				}
			}
			else {
				if (r11 > TotalProb7) {
					fill(213, 202, 112);
					text("☆7:", 1050, r10Py);
					fill(0);
					text((let)rare7[randrare7_11].name, 1200, r10Py);
					if (rare7[randrare7_11].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1400, 780);
					}
				}
				else if (r11 > TotalProb6) {
					fill(0);
					text("☆6:" + (let)rare6[randrare6_11].name, r11Px, r10Py);
					if (rare6[randrare6_11].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1400, 780);
					}
				}
				else if (r11 > TotalProb5) {
					fill(0);
					text("☆5:" + (let)rare5[randrare5_11].name, r11Px, r10Py);
					if (rare5[randrare5_11].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1400, 780);
					}
				}
				else {
					fill(0);
					text("☆4:" + (let)rare4[randrare4_11].name, r11Px, r10Py);
					if (rare4[randrare7_11].getCnt <= 0) {
						fill(255, 0, 0);
						text("NEW", 1400, 780);
					}
				}
			}
			if (rFrameCnt <= 0.5f) {
				if (confirm11 == 11) {
					rare7[randrare7_11].getCnt += 1;
				}
				else {
					if (r11 > TotalProb7) {
						rare7[randrare7_11].getCnt += 1;
					}
					else if (r11 > TotalProb6) {
						rare6[randrare6_11].getCnt += 1;
					}
					else if (r11 > TotalProb5) {
						rare5[randrare5_11].getCnt += 1;
					}
					else {
						rare4[randrare4_11].getCnt += 1;
					}
				}
			}
		}
		if (rFrameCnt > 0) {
			rFrameCnt--;
		}
		else{
			Egg1Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg2Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg3Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg4Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg5Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg6Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg7Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg8Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg9Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg10Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			Egg11Img = loadImage("..\\main\\assets\\game05\\tamago2.png");
			State = GACHA;
		}
	}

	void GAME::Box()
	{
		clear(255);
		textSize(60);
		for (int i = 0; i < rare4Total; i++) {
			text("☆4", 160.0f, 100.0f);
			if (rare4[i].getCnt >= 99.0f) {
				text(rare4[i].name, 50.0f, 200.0f + 90.0f * i);
				text("×99+", 350.0f, 200.0f + 90.0f * i);
			}
			else {
				text(rare4[i].name, 50.0f, 200.0f + 90.0f * i);
				text("×" + (let)rare4[i].getCnt, 350.0f, 200.0f + 90.0f * i);
			}
		}
		for (int i = 0; i < rare5Total; i++) {
			text("☆5", 640.0f, 100.0f);
			if (rare5[i].getCnt >= 99.0f) {
				text(rare5[i].name, 530.0f, 200.0f + 90.0f * i);
				text("×99+", 830.0f, 200.0f + 90.0f * i);
			}
			else {
				text(rare5[i].name, 530.0f, 200.0f + 90.0f * i);
				text("×" + (let)rare5[i].getCnt, 830.0f, 200.0f + 90.0f * i);
			}
		}
		for (int i = 0; i < rare6Total; i++) {
			text("☆6", 1120.0f, 100.0f);
			if (rare6[i].getCnt >= 99.0f) {
				text(rare6[i].name, 1010.0f, 200.0f + 90.0f * i);
				text("×99+", 1310.0f, 200.0f + 90.0f * i);
			}
			else {
				text(rare6[i].name, 1010.0f, 200.0f + 90.0f * i);
				text("×" + (let)rare6[i].getCnt, 1310.0f, 200.0f + 90.0f * i);
			}
		}
		for (int i = 0; i < rare7Total; i++) {
			fill(213, 202, 112);
			text("☆7", 1600, 100);
			fill(0);
			if (rare7[i].getCnt >= 99) {
				text(rare7[i].name, 1490.0f, 200.0f + 90.0f * i);
				text("×99+", 1740.0f, 200.0f + 90.0f * i);
			}
			else {
				text(rare7[i].name, 1490.0f, 200.0f + 90.0f * i);
				text("×" + (let)rare7[i].getCnt, 1740.0f, 200.0f + 90.0f * i);
			}
		}
		textSize(50);
		text("ENTER:ガチャ選択画面にもどる", 600.0f, 1080.0f);
		if (isTrigger(KEY_ENTER)) {
			State = GACHA;
		}
	}

	void GAME::Prob()
	{
		clear(37, 44, 107);
		fill(255);
		textSize(50);
		for (int i = 0; i < 10; i++) {
			text("☆4:10体:61.3%", 60, 100);
			text(rare4[i].name, 50.0f, 200.0f + 90.0f * i);
			text(":6.13%", 300.0f, 200.0f + 90.0f * i);

		}
		for (int i = 0; i < 9; i++) {
			text("☆5:9体:28.8%", 540, 100);
			text(rare5[i].name, 530.0f, 200.0f + 90.0f * i);
			text(":3.2%", 780.0f, 200.0f + 90.0f * i);
		}
		for (int i = 0; i < 8; i++) {
			text("☆6:8体:9.6%", 1020, 100);
			text(rare6[i].name, 1010.0f, 200.0f + 90.0f * i);
			text(":1.2%", 1260.0f, 200.0f + 90.0f * i);
		}
		for (int i = 0; i < 7; i++) {
			fill(213, 202, 112);
			text("☆7:7体:0.3%", 1500, 100);
			fill(255);
			text(rare7[i].name, 1440.0f, 200.0f + 90.0f * i);
			text(":0.04%", 1690.0f, 200.0f + 90.0f * i);
		}
		fill(255);
		textSize(50);
		text("ENTER:ガチャ選択画面にもどる", 600, 1080);
		if (isTrigger(KEY_ENTER)) {
			State = GACHA;
		}
	}

	void GAME::draw()
	{
		textSize(50);
		fill(255);
		text((let)WinCnt + "/" + (let)straightWinCnt + "連勝", 50, 100);
		text("勝ったときの配当:" + (let)GetCoins + "コイン", 50, 200);
		image(HaimenImg, HaimenPx, HaimenPy);
		image(HaimenImg, HaimenPx, HaimenPy - 3);
		image(HaimenImg, HaimenPx, HaimenPy - 6);
		image(HaimenImg, HaimenPx, HaimenPy - 9);
		image(HaimenImg, HaimenPx, HaimenPy - 12);
		image(HaimenImg, HaimenPx, HaimenPy - 15);
		image(HaimenImg, HaimenPx, HaimenPy - 18);
		image(HaimenImg, HaimenPx, HaimenPy - 21);
		image(HaimenImg, HaimenPx, HaimenPy - 24);
		image(HaimenImg, HaimenPx, HaimenPy - 27);
		image(HaimenImg, HaimenPx, HaimenPy - 30);
		image(SetImg[0], CardSetPx[0], CardSetPy[0]);
		image(SetImg[1], CardSetPx[1], CardSetPy[1]);
		text("ディーラー", 830, 50);
		strokeWeight(5);
		stroke(255);
		line(830, 70, 1080, 70);
		line(830, 70, 830, 380);
		line(830, 380, 1080, 380);
		line(1080, 70, 1080, 380);
	}
}