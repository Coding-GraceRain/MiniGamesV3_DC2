#include"../../libOne/inc/libOne.h"
#include"../MAIN/MAIN.h"
#include"GAME12.h"

namespace GAME12
{
	int GAME::create()
	{
		return 0;
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{

		//シーン切り替え
		if (State == TITLE)title();
		else if (State == INIT)init();
		else if (State == PLAY)play();
		else if (State == WAIT)wait();
		else if (State == OVER)over();
		else if (State == END)ending();
	}

	void GAME::count() {
		for (int i = 0; i < Qnumber;i++) {
				str = strlen(ward[i][1]);
				sum += str;
			}

	}
	
	INPUT_CODE GAME::gettriggerkeycode() {
		for (int i = (int)KEY_A; i <= (int)KEY_ENTER; i++) {
			if (isTrigger((INPUT_CODE)i)) {
				return (INPUT_CODE)i;
			}
		}
		return (INPUT_CODE)0;
	}
	
		
	void GAME::title(){
		//描画--------------------------------------------------
		clear(60);
		//テキスト情報
		fill(0, 255, 0);
		textSize(100);
		text("タイピングゲーム", 600, 450);
		fill(0, 0, 0);
		textSize(40);
		text("クリックでゲームスタート", 750, 500);
		text("Enterでメニューに戻る", 750, 550);
		//シーン切り替え-----------------------------------------
		if (isTrigger(MOUSE_LBUTTON)) {
			//次のシーケンス
			State = INIT;
			return;
		}
		//メニューに戻る-----------------------------------------
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}

	void GAME::init() {
		clear(60, 60, 60);
		miss = 0;
		num = 0;
		wnum = 0;
		flag = 0;
		fflag = 0;
		gend = 0;
		lend = 0;
		fill(0, 0, 0);
		textSize(60);
		text("表示された文字をタイピングしよう", 525, 500);
		text("左クリックでゲームスタート", 575, 550);
		
		if (isTrigger(MOUSE_LBUTTON)) {
			count();
			State = WAIT;
			return;
		}
	}
	void GAME::wait() {
		clear(200);
		textSize(60);
		text("スペースキーで開始", 525, 500);
		
		if (isTrigger(KEY_SPACE)) {
			clear(200);
			State = PLAY;
			return;
		}
	}

	void GAME::draw(int snum) {
		fill(0);
		textSize(200);
		text((let) +ward[snum][0], 550, 300);
		text((let) +ward[snum][1], 550, 500);
		print(curtime);
		char str[128];
		strcpy_s(str, sizeof(str), ward[num][1]);
		str[wnum] = '\0';
		fill(255, 0, 0);
		textSize(200);
		text(str, 550, 500);
	}

	void GAME::dec(int num, int wnum) {
		
			if (ch[num][wnum] - 1 == ward[num][1][wnum] - 'a') {
				
				flag++;
			}
			else if (ch[num][wnum] - 1 != ward[num][1][wnum] - 'a') {
				fflag++;
			}
			
	}
	

	void GAME::play() {
		clear(200);
		
		curtime += delta;
		size_t len = strlen(ward[num][1]);
		draw(num);	
		ch[num][wnum] = gettriggerkeycode();
		if (ch[num][wnum] != 0) {
			dec(num, wnum);
		}
		if (fflag == 1) {
			fflag = 0;
			miss++;
			fill(0);
			textSize(300);
			text("×", 700, 550);
		}

		if (flag == 1) {
			wnum++;
			lend++;
			flag = 0;
		}

		if (lend == len) {
			num++;
			wnum = 0;
			lend = 0;
			gend++;
			clear(200);
		}

			
		if(gend == Qnumber){
			State = OVER;
		}
				

			
			
	}
	void GAME::over() {
		clear(200);
		fill(0);
		textSize(60);
		text("終了", 900, 550);
		text("左クリックで結果を見る", 600, 600);
		if(isTrigger(MOUSE_LBUTTON)) {
			State = END;
			return;
		}
	}
	
	void GAME::ending() {
		clear(0, 255, 0);
		//ゲームオーバーテキスト 
		fill(0, 0, 255);
		textSize(80);
		text((let)"一秒あたりのタイプ数:" +sum / curtime, 550, 100);
		text((let)"タイム:" +curtime, 550, 200);
		text((let)"ミスタイプ:"+miss, 550, 300);
		text("GAMEOVER", 650, 450);
		text("SPACEキーでタイトルに戻る", 500, 550);
		if (isTrigger(KEY_SPACE)) {
			State = TITLE;
		}
	}

	void GAME::gmain() {
		window( 1920,1080,full);
	}




}


