#include"HIRAGANA_GAME.h"
namespace GAME14 {
	void HIRAGANA::TITLE_INIT() {
		WIDTH = 750;
		HEIGHT = 200;
		Position_X = (Yoko/2)-425;
		Position_Y = Tate/2;
		Position_X_2 = (Yoko / 2) - 425;
		Position_Y_2 = (Tate/2)+200;
		stage_Progress = 1;
		text_Potition_X = 650;
		text_Potition_Y = 200;
		text_Size = 200;
	}
	bool HIRAGANA::MOUSE_JUDGE(int WIDTH,int HEIGHT, float Pos_X, float Pos_Y) {
		if (Pos_X - 50 < mouseX && mouseX < Pos_X + (WIDTH - 50) && Pos_Y  < mouseY && mouseY < Pos_Y + HEIGHT) {
			return true;
		}
		else {
			return false;
		}
	}
	int HIRAGANA::TITLE_DRAW() {
		rectMode(CORNER);
		if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X-50, Position_Y-(HEIGHT-25)) == true) {
			fill(255, 255, 50);
		}
		else {
			fill(255);
		}
		rect(Position_X-50, Position_Y-(HEIGHT-50), WIDTH, HEIGHT);
		if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X_2-50, Position_Y_2-(HEIGHT-25)) == true) {
			fill(255, 255, 50);
		}
		else {
			fill(255);
		}
		rect(Position_X_2-50, Position_Y_2-(HEIGHT-25), WIDTH, HEIGHT);
		textSize(150);
		fill(0);
		text("‚Ð‚ç‚ª‚ÈŽZ", (Yoko / 2) - 375, 300);
		text("‚Í‚¶‚ß‚é", Position_X, Position_Y);
		text("‚à‚Ç‚é", Position_X_2, Position_Y_2);
		if (isTrigger(MOUSE_LBUTTON)) {
			if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X, Position_Y-HEIGHT) == true) {
				return 2;
			}
			else if (MOUSE_JUDGE(WIDTH, HEIGHT, Position_X_2, Position_Y_2-HEIGHT) == true) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	void HIRAGANA::STAGE1_DRAW() {
			fill(255);
			textSize(text_Size);
			Goto_Select_Stage = false;
			Correct_answer();
		if (stage_Progress == 1) {
			text("‚ +‚¢=?", text_Potition_X, text_Potition_Y);
			text("‚¢+‚¢=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 2) {
			text("‚ +‚¨=?", text_Potition_X, text_Potition_Y);
			text("‚¢+‚¤=?", text_Potition_X, text_Potition_Y+text_Size);

		}
		else if (stage_Progress == 3) {
			text("‚¢+‚¨=?", text_Potition_X, text_Potition_Y);
			text("‚ +‚¤=?", text_Potition_X, text_Potition_Y+text_Size);

		}
		else if (stage_Progress == 4) {
			text("‚¤+‚¤=?", text_Potition_X, text_Potition_Y);
			text("‚¤+‚¦=?", text_Potition_X, text_Potition_Y+text_Size);

		}
		else if (stage_Progress == 5) {
			text("‚¢+‚¨=?", text_Potition_X, text_Potition_Y);
			text("‚¢+‚¦=?", text_Potition_X, text_Potition_Y+text_Size);
			text("‚¤+‚¦=?", text_Potition_X, text_Potition_Y + (text_Size*2));

		}
	}
	void HIRAGANA::STAGE1_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "‚¤‚¦") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "‚ ‚¨") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "‚¢‚¦") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "‚ ‚¢") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "‚¢‚ ‚¢") == 0) {
				correct_Answer = true;
			}
		}
	}
	void HIRAGANA::STAGE2_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (stage_Progress == 1) {
			text("‚¢-‚ =?", text_Potition_X, text_Potition_Y);
			text("‚¦-‚¢=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 2) {
			text("‚¤-‚¤=?", text_Potition_X, text_Potition_Y);
			text("‚¨-‚¢=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 3) {
			text("‚ -‚¦=?", text_Potition_X, text_Potition_Y);
			text("‚¢-‚¦=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 4) {
			text("‚¨-‚¤=?", text_Potition_X, text_Potition_Y);
			text("‚¢-‚¢+‚¦=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚ +‚¦-‚¤=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 5) {
			text("‚¦-‚¦=?", text_Potition_X, text_Potition_Y);
			text("‚¢+‚¨-‚¢=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚¦-‚ -‚¨=?", text_Potition_X, text_Potition_Y + (text_Size * 2));

		}
	}
	void HIRAGANA::STAGE2_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "‚ ‚¢") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "‚¨‚¤") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "‚¢‚¤") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "‚¢‚¦‚¢") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "‚¨‚¨‚¤") == 0) {
				correct_Answer = true;
			}
		}
	}
	void HIRAGANA::STAGE3_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		Correct_answer();
		if (stage_Progress == 1) {
			text("‚ +‚È=?", text_Potition_X, text_Potition_Y);
			text("‚©+‚©=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 2) {
			text("‚­+‚¢=?", text_Potition_X, text_Potition_Y);
			text("‚Ê+‚·=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 3) {
			text("‚µ+‚Ä=?", text_Potition_X, text_Potition_Y);
			text("‚­+‚¹=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 4) {
			text("‚«+‚Ä=?", text_Potition_X, text_Potition_Y);
			text("‚ +‚³=?", text_Potition_X, text_Potition_Y + text_Size);

		}
		else if (stage_Progress == 5) {
			text("‚·+‚Â=?", text_Potition_X, text_Potition_Y);
			text("‚­+‚·=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚«+‚»=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		Correct_answer();
	}
	void HIRAGANA::STAGE3_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "‚É‚µ") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "‚±‚Ü") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "‚Í‚¿") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "‚È‚µ") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "‚Í‚½‚¿") == 0) {
				correct_Answer = true;
			}
		}
	}
	void HIRAGANA::STAGE4_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		if (stage_Progress == 1) {
			text("‚ë+‚ñ=?", text_Potition_X, text_Potition_Y);
			text("‚Ó+‚ä=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚í+‚±=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 2) {
			text("‚í+‚ê=?", text_Potition_X, text_Potition_Y);
			text("‚µ+‚Ö=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚ä+‚ß=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 3) {
			text("‚¤-‚ñ=?", text_Potition_X, text_Potition_Y);
			text("‚é-‚ç=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚È-‚â=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 4) {
			text("‚¯-‚ñ=?", text_Potition_X, text_Potition_Y);
			text("‚ä-‚â=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚¢-‚ñ=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 5) {
			text("‚Ó+‚ê=?", text_Potition_X, text_Potition_Y);
			text("‚ë+‚È=?", text_Potition_X, text_Potition_Y + text_Size);
			text("‚â+‚Ð=?", text_Potition_X, text_Potition_Y + (text_Size * 2));
		}
		Correct_answer();
	}
	void HIRAGANA::STAGE4_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "‚â‚©‚ñ") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "‚à‚â‚µ") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "‚«‚¢‚ë") == 0) {
				correct_Answer= true;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "‚·‚¢‚©") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "‚µ‚©‚­") == 0) {
				correct_Answer = true;
			}
		}
	}
	void HIRAGANA::STAGE5_DRAW() {
		fill(255);
		textSize(text_Size);
		Goto_Select_Stage = false;
		if (stage_Progress == 1) {
			text("‚³+‚Í+‚ =?", text_Potition_X - 100, text_Potition_Y);
			text("‚í+‚í+‚Ö=?", text_Potition_X - 100, text_Potition_Y + text_Size);
			text("‚Í+‚Í+‚Ë=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 2) {
			text("‚Ý+‚«+‚Ö=?", text_Potition_X - 100, text_Potition_Y);
			text("‚Í+‚Ó+‚ï=?", text_Potition_X - 100, text_Potition_Y + text_Size);
			text("‚È+‚Ð+‚é=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 3) {
			text("‚ä-‚ +‚Ý=?", text_Potition_X - 100, text_Potition_Y);
			text("‚ð-‚³+‚¿=?", text_Potition_X - 100, text_Potition_Y + text_Size);
			text("‚µ-‚¿+‚ð=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 4) {
			text("‚±-‚³+‚ä=?", text_Potition_X - 100, text_Potition_Y);
			text("‚Ð-‚ß+‚·=?", text_Potition_X - 100, text_Potition_Y + text_Size);
			text("‚Â-‚â+‚Ä=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));
		}
		else if (stage_Progress == 5) {
			text("‚ß+‚Ì+‚·=?", text_Potition_X - 100, text_Potition_Y);
			text("‚½-‚È+‚³=?", text_Potition_X - 100, text_Potition_Y + text_Size);
			text("‚î+‚«+‚­=?", text_Potition_X - 100, text_Potition_Y + (text_Size * 2));

		}
		Correct_answer();
	}
	void HIRAGANA::STAGE5_INPUT(const char* str) {
		if (stage_Progress == 1) {
			if (strcmp(str, "‚ä‚©‚½") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 2) {
			if (strcmp(str, "‚­‚é‚Ü") == 0) {
				correct_Answer= true;
			}
		}
		else if (stage_Progress == 3) {
			if (strcmp(str, "‚¹‚ñ‚ë") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 4) {
			if (strcmp(str, "‚Ý‚©‚ñ") == 0) {
				correct_Answer = true;
			}
		}
		else if (stage_Progress == 5) {
			if (strcmp(str, "‚«‚©‚¢") == 0) {
				correct_Answer = true;
			}
		}
	}
	void HIRAGANA::START_STAGE(int num, int mouseX, int mouseY) {
		fill(255);
		textSize(text_Size / 2);
		rectMode(CENTER);
		/*
		if (0 == num) {
			text("‚ ’i‚Ì‰ÁŽZ‚É‚Â‚¢‚Äl‚¦‚Ü‚·B", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("‚Í‚¶‚ß‚é", Yoko/2-350, 650);
		}
		else if (1 == num) {
			text("‚ ’i‚ÌŒ¸ŽZ‚É‚Â‚¢‚Äl‚¦‚Ü‚·B", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("‚Í‚¶‚ß‚é", Yoko/2-350 ,650);
		}
		else if (2 == num) {
			text("æ’ö‚Ü‚Å‚Ìƒ‹[ƒ‹‚ðŠg’£‚µ‚Ü‚·B", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("‚Í‚¶‚ß‚é", Yoko/2-350, 650);
		}
		else if (3 == num) {
			text("ŒJ‚èã‚ª‚è‚Ì‚ ‚éŒvŽZ‚É‚Â‚¢‚Äl‚¦‚Ü‚·B", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("‚Í‚¶‚ß‚é", Yoko/2-350, 650);
		}
		else if (4 == num) {
			text("‘¶Ý‚µ‚È‚¢•¶Žš‚É‚Â‚¢‚Äl‚¦‚Ü‚·B", 200, text_Potition_Y);
			if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
				fill(255, 255, 0);
				if (isTrigger(MOUSE_LBUTTON)) {
					Start_Stage = true;
				}
			}
			rect(Yoko / 2, 800, 900, 300);
			fill(0);
			text("‚Í‚¶‚ß‚é", Yoko/2-350, 650);
		}
		*/
		if (0 == num) {
			text("1.ƒAs‚Ì‘«‚µŽZ", 200, text_Potition_Y);
			text("ƒAs“¯Žm‚Ì‰ÁŽZ‚ðl‚¦‚Ü‚·B", 200, text_Potition_Y+(text_Size/2));
		}
		else if (1 == num) {
			text("2.ƒAs‚Ìˆø‚«ŽZ", 200, text_Potition_Y);
			text("ƒAs“¯Žm‚ÌŒ¸ŽZ‚ðl‚¦‚Ü‚·B", 200, text_Potition_Y + (text_Size / 2));
		}
		else if (2 == num) {
			text("3.ƒA`ƒ“s‚ÌŒvŽZ1", 200, text_Potition_Y);
			text("ƒA`ƒ“s“¯Žm‚Ì‰ÁŽZ‚ðl‚¦‚Ü‚·B", 200, text_Potition_Y + (text_Size / 2));
			text("ƒAs‚ÌŒvŽZ‚à¬‚è—§‚Â‚æ‚¤‚É", 200, text_Potition_Y + (text_Size + (text_Size / 2)));
			text("ŒvŽZ‹K‘¥‚ðŠg’£‚µ‚Ü‚·B", 200, text_Potition_Y +( text_Size*2));
		}
		else if (3 == num) {
			text("4.ƒA`ƒ“s‚ÌŒvŽZ2", 200, text_Potition_Y);
			text("ŒJ‚èã‚ª‚è‚Ì‚ ‚é", 200, text_Potition_Y + (text_Size / 2));
			text("‰ÁŽZ‚ÆŒ¸ŽZ‚ðl‚¦‚Ü‚·B", 200, text_Potition_Y + text_Size);
		}
		else if (4 == num) {
			text("5.ƒA`ƒ“s‚ÌŒvŽZ3", 200, text_Potition_Y);
			text("‘¶Ý‚µ‚È‚¢•¶Žš‚Ìˆµ‚¢‚ðl‚¦‚Ü‚·B", 200, text_Potition_Y + (text_Size / 2));
		}
		if ((Yoko / 2) - 450 < mouseX && mouseX < (Yoko / 2) + 450 && 650 < mouseY && mouseY < 950) {
			fill(255, 255, 0);
			if (isTrigger(MOUSE_LBUTTON)) {
				Start_Stage = true;
			}
		}
		rect(Yoko / 2, 800, 900, 300);
		fill(0);
		text("‚Í‚¶‚ß‚é", Yoko / 2 - 150, 850);

		//BOTTOM, TOP, BCENTER, MBCENTER.
		rectMode(CORNER);
	}
	bool HIRAGANA::SENT_START_STAGE_FLAG() {
		return Start_Stage;
	}
	void HIRAGANA::FLAG_INIT() {
		Goto_Select_Stage = false;
		Start_Stage = false;
		stage_Progress = 1;
	}
	bool HIRAGANA::GOTO_SELECT_STAGE() {
		return Goto_Select_Stage;
	}
	void HIRAGANA::Correct_answer() {
		if (correct_Answer == true) {
			textSize(150);
			fill(0);
			text("³‰ð!", 1500, 930);
			text("ŽŸ‚Ö:N", 1425, 1080);
			fill(255, 0, 0);
			circle(Yoko / 2, Tate / 2, 700);
			fill(190);
			circle(Yoko / 2, Tate / 2, 600);
			fill(255);
			if (isTrigger(KEY_N)) {
				if (stage_Progress == 5) {
					stage_Progress = 1;
					Goto_Select_Stage = true;
					correct_Answer = false;
				}
				else {
					stage_Progress++;
					correct_Answer = false;
				}
			}
		}
	}
}