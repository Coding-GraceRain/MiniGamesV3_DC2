#pragma once
#include "../../libOne/inc/libOne.h"
#include "GAME14.h"
#include <string>
namespace GAME14 {
#define KEY_NUM 57
#define SELECT_KEY_NUM 5
	class INPUT {
		const int KEY_START_X = 600;
		const int KEY_START_Y = 800;
		const int SELECT_KEY_START_X = 460;
		const int SELECT_KEY_START_Y = 340;
	public:
		class KEY {
		public:
			int x = 0;
			int y = 0;
			static const int Key_Size = 60;
			//std::string Hira;
			const char* Hira;
			bool press = false;
			//bool overlap = false;
		};
		class SELECT_KEY {
		public:
			int x = 0;
			int y = 0;
			static const int Key_Size_X = 200;
			static const int Key_Size_Y = 400;
			bool press = false;
		};
	private:
			KEY* key[KEY_NUM] = {};
			std::string inputText;
			SELECT_KEY* select_key[SELECT_KEY_NUM] = {};
			std::string sent_text;
	public:
		INPUT() {
			for (int i = 0; i < KEY_NUM; i++) {
				key[i] = new KEY();
				key[i]->Hira = "";
			}
			for (int i = 0; i < SELECT_KEY_NUM; i++) {
				select_key[i] = new SELECT_KEY();
			}
		}
		~INPUT(){
			for (int i = 0; i < KEY_NUM; i++) {
				delete key[i];
			}
			for (int i = 0; i < SELECT_KEY_NUM; i++) {
				delete select_key[i];
			}
		}
		void INIT();
		void DRAWRECT(int mouseX, int mouseY);
		void DRAWTEXT();
		void KEYBOARD(int mouseX, int mouseY);
		void DRAW_SELECT(int mouseX, int mouseY);
		const char* Sent_text();

		void MOUSE_INPUT(int mouseX, int mouseY); // © V‹K’Ç‰Á
		int SELECT_MOUSE_INPUT(int mouseX, int mouseY);
		void SHOW_INPUT(); // © “ü—ÍŒ‹‰Ê‚ð‰æ–Ê‚É•\Ž¦
		bool BACK_SCENE(int mouseX,int mouseY);
	};
}
