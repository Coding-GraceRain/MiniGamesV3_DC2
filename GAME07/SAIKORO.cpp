#include "SAIKORO.h"
#include "../../libOne/inc/libOne.h"
int SAIKORO::create()
{
	Img[0] = loadImage("..\\MAIN\\assets\\game07\\kara.png");
	Img[1] = loadImage("..\\MAIN\\assets\\game07\\saikoro1.png");
	Img[2] = loadImage("..\\MAIN\\assets\\game07\\saikoro2.png");
	Img[3] = loadImage("..\\MAIN\\assets\\game07\\saikoro3.png");
	Img[4] = loadImage("..\\MAIN\\assets\\game07\\saikoro4.png");
	Img[5] = loadImage("..\\MAIN\\assets\\game07\\saikoro5.png");
	Img[6] = loadImage("..\\MAIN\\assets\\game07\\saikoro6.png");
	return 0;
}
void SAIKORO::init() {
	 A = 0, B = 0, C = 0;
	 num[0] = 3;
	 num[1] = 5;
	 for (int i = 0;i < 11;i++) {
		 cnt[i] = 0;
	 }
	 Coin = 1000;
	 Coinkake = 50;
	 Yaku = 0;
	 for (int i = 0;i < 3;i++) {
		 Flag[i] = 0;
	 }
	 i = 0;
}

void SAIKORO::reset() {
	A = 0;
	B = 0;
	C = 0;
	Flag[0] = 0;
	Flag[1] = 0;
	Flag[2] = 0;
	Yaku = 0;
	Coinkake =50;
	for (int i = 0;i < 11;i++) {
		cnt[i] = 0;
	}
}

void SAIKORO::set(int x, int y,int n) {

	//íäëI
	if (isTrigger(KEY_U) && cnt[0] < num[0] && cnt[1] < num[1] && Flag[0] == 0 && Flag[1] == 1) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		cnt[0]++;

		i = 1;
	}

	rectMode(CORNER);
	fill(0);
	rect(0, 0, 400, 200);


	rect(400, 0, 100, 100);
	textSize(80);
	if (n == 0) {
		fill(255, 0, 0);
		text("êe", 410, 90);
	}
	else {
		fill(255);
		text("éq", 410, 90);
	}

	fill(255);
	stroke(255);
	strokeWeight(3);
	line(0, 50, 400, 50);
	line(0, 100, 400, 100);
	line(0, 150, 400, 150);
	line(275, 50, 275,200);

	textSize(50);
	text("PLAYER1", 110, 50);
	text("éËéùÇøã‡", 10, 100);
	text("ä|ÇØã‡", 10, 150);
	text("êUÇÍÇÈâÒêî", 10, 200);
	text(Coin, 280, 100);
	text(Coinkake, 280, 150);
	text(num[0] - cnt[0], 280, 200);


	//ÉTÉCÉRÉçï\é¶
	rectMode(CENTER);
	image(Img[A], x, y);
	image(Img[B], x + 200, y);
	image(Img[C], x + 400, y);

	//ÉVÉÉÉbÉtÉãââèo
	if(i>0&&i<11)i++;
	if (i>1&&i<10)kari(x,y);

}


void SAIKORO::judge(int x,int y) {

	if (i == 11) {
	    //ÉsÉìÉ]Éç
		if (A == 1 && B == 1 && C == 1) {
			text("ARASI", x, y);
			Yaku = 14;
			Flag[0] = 1;
		}

		//ÉAÉâÉV,2,3,4,5,6
		else if (A == 6 && B == 6 && C == 6) {
			text("roku", x, y);
			Yaku = 13;
			Flag[0] = 1;
		}
		else if (A == 5 && B == 5 && C == 5) {
			text("go", x, y);
			Yaku = 12;
			Flag[0] = 1;
		}
		else if (A == 4 && B == 4 && C == 4) {
			text("yon", x, y);
			Yaku = 11;
			Flag[0] = 1;
		}
		else if (A == 3 && B == 3 && C == 3) {
			text("san", x, y);
			Yaku = 10;
			Flag[0] = 1;
		}
		else if (A == 2 && B == 2 && C == 2) {
			text("ni", x, y);
			Yaku = 9;
			Flag[0] = 1;
		}

		//ÇµÇ≤ÇÎ
		else if (
			A == 4 && B == 5 && C == 6 || A == 4 && B == 6 && C == 5 ||
			A == 5 && B == 4 && C == 6 || A == 5 && B == 6 && C == 4 ||
			A == 6 && B == 4 && C == 5 || A == 6 && B == 5 && C == 4) {
			text("sigoro", x, y);
			Yaku = 8;
			Flag[0] = 1;
		}

		//Ç–Ç”Ç›
		else if (A == 1 && B == 2 && C == 3 || A == 1 && B == 3 && C == 2 ||
			A == 2 && B == 1 && C == 3 || A == 2 && B == 3 && C == 1 ||
			A == 3 && B == 1 && C == 2 || A == 3 && B == 2 && C == 1) {
			text("hifumi", x, y);
			Yaku = 0;
			Flag[0] = 1;
		}

		//í èÌ
		else if (A == B) {
			if(C!=0)text(C, x, y);
			Yaku = C + 1;
			if (A != 0)Flag[0] = 1;
		}

		else if (A == C) {
			text(B, x, y);
			Yaku = B + 1;
			if (A != 0)Flag[0] = 1;
		}

		else if (B == C) {
			text(A, x, y);
			Yaku = A + 1;
			if (A != 0)Flag[0] = 1;
		}


		//Ç‚Ç≠Ç»Çµ
		else {
			text("Yakunasi", x, y);
			Yaku = 1;
			if (cnt[0] == num[0])Flag[0] = 1;
		}
	}
}

int SAIKORO::yakur() { return Yaku; }
int SAIKORO::flagr() { return Flag[0]; }
int SAIKORO::Coinr() { return Coin; }

void SAIKORO::kari(int x,int y) {
		//clear(0, 0, 64);
		image(Img[random() % 6 + 1], x, y);
		image(Img[random() % 6 + 1], x + 200, y);
		image(Img[random() % 6 + 1], x + 400, y);
		//Sleep(70);
}

void SAIKORO::kakekin() {
	if (isTrigger(KEY_D) && Coinkake < 100 && Coinkake < Coin && Flag[1] == 0)Coinkake += 5;
	else if (isTrigger(KEY_A) && Coinkake > 10 && Flag[1] == 0)Coinkake -= 5;
}

int SAIKORO::kaker() {
	return Coinkake;
}
void SAIKORO::kakef() {
	Flag[2] = 1;
}
void SAIKORO::kakekati(int n) {
	if (Flag[2] == 0) {
		Coin += n;
	}	
}
void SAIKORO::kakemake(int n){
	if (Flag[2] == 0) {
		Coin -= n;
	}
}

void SAIKORO::syouhai(int p1, int p2, SAIKORO* n1, SAIKORO* n2) {
	int num = 1;
	if (p1 == 14 || p2 == 14) {
		num *= 5;
	}
	if (p1 >= 9 && p1 <= 13 || p2 >= 9 && p2 <= 13) {
		num *= 3;
	}
	if (p1 == 8 || p2 == 8) {
		num *= 2;
	}
	if (p1 == 0 || p2 == 0) {
		num *= 2;
	}
	if (p1 > p2) {
		if (Flag[2] == 0) {
			n1->Coin += (n2->Coinkake * num);
			n2->Coin -= (n2->Coinkake * num);
		}
	}
	if (p1 < p2) {
		if (Flag[2] == 0) {
			n2->Coin += (n2->Coinkake * num);
			n1->Coin -= (n2->Coinkake * num);
		}
	}
	if (p1 == p2) {}
}

void SAIKORO::kakekinf() {
	Flag[1] = 1;
}

void SAIKORO::saihyouzi() {
	int a = 120, x = 300, y = 90;
	float s = 0.6f;
	int n = 0;

	clear(0, 0, 64);
	rectMode(CORNER);
	fill(0, 0, 64);
	stroke(255);
	strokeWeight(3);
	rect(20, 75, x + a * 3 + 200, a * 7);
	line(280, 75, 280, 75 + a * 7);
	line(x + a * 3, 75, x + a * 3, 75 + a * 7);
	line(20, 75 + a, 520 + a * 3, 75 + a);
	line(20, 75 + a * 6, 520 + a * 3, 75 + a * 6);

	fill(255);
	textSize(60);
	text("ñàÍóó(ç∂è„Ç©ÇÁã≠Ç¢ñ)", 20, 60);
	text("ÉsÉìÉ]Éç", 20, 165);
	text("+5î{", 50 + x + a * 3, 165);
	text("É]Éçñ⁄", 60, 525);
	text("+3î{", 50 + x + a * 3, 525);
	text("ÉVÉSÉç", 60, 885);
	text("+2î{", 50 + x + a * 3, 885);
	for (int i = 0; i < 6;i++) {
		if (i == 0)n += 6;
		else n = 0;
		image(Img[7 - i - n], x, y + (a * i), 0, s);
		image(Img[7 - i - n], x + a * 1, y + (a * i), 0, s);
		image(Img[7 - i - n], x + a * 2, y + (a * i), 0, s);
		line(280, 75 + a * (i + 1), 300 + a * 3, 75 + a * (i + 1));
	}
	image(Img[4], x, y + a * 6, 0, s);
	image(Img[5], x + a * 1, y + a * 6, 0, s);
	image(Img[6], x + a * 2, y + a * 6, 0, s);

	x = 900;
	fill(0, 0, 64);
	rect(20 + x, 75, 500 + a * 3, a * 8);

	stroke(255);
	strokeWeight(3);
	line(280 + x, 75, 280 + x, 75 + a * 8);
	line(300 + x + a * 3, 75, 300 + x + a * 3, 75 + a * 8);
	line(20 + x, 75 + a * 6, 520 + a * 3 + x, 75 + a * 6);
	line(20 + x, 75 + a * 7, 520 + a * 3 + x, 75 + a * 7);
	fill(255);
	text("í èÌñ", 60 + x, 465);
	text("+1î{", (50 + 300) + x + a * 3, 465);
	text("ñÇ»Çµ", 60 + x, 885);
	text("-1î{", (50 + 300) + x + a * 3, 885);
	text("ÉqÉtÉ~", 60 + x, 1005);
	text("-2î{", (50 + 300) + x + a * 3, 1005);
	for (int i = 0; i < 8;i++) {
		if (6 > i) {
			image(Img[1 + i % 6], x + 300, y + (a * i), 0, s);
			image(Img[1 + i % 6], x + 300 + a * 1, y + (a * i), 0, s);
			image(Img[6 - i], x + 300 + a * 2, y + (a * i), 0, s);
			line(280 + x, 75 + a * (i + 1), 300 + x + a * 3, 75 + a * (i + 1));
		}
	}

	image(Img[2], x + 300, y + a * 6, 0, s);
	image(Img[3], x + 300 + a * 1, y + a * 6, 0, s);
	image(Img[5], x + 300 + a * 2, y + a * 6, 0, s);


	image(Img[1], x + 300, y + a * 7, 0, s);
	image(Img[2], x + 300 + a * 1, y + a * 7, 0, s);
	image(Img[3], x + 300 + a * 2, y + a * 7, 0, s);
}