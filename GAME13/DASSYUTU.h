#pragma once
#include"GAME13.h"
namespace GAME13 {
	class DASSYUTU {

#define STAGE_WIDTH 10
#define STAGE_HEIGHT 10
		struct PLAYER {
			int player_x = 2;
			int player_y = 2;
			int last_player_x = 0;
			int last_player_y = 0;
			int use_x = 0;
			int use_y = 0;
			char direction = 0;
			int use_point[10][10] = { 0 };
			bool Not_move = 0;
		};
		struct STAGE {
			int map[10][10] = { 0 };
			const enum { WALL, FLOOR, GIMMICK, DOOR, WINDOW };
			float size = 100;
		};
		struct OTHER {
			bool point = 0;
		};
		struct GIMMICK {
			bool search_flower = 0;
			bool broke_window = 0;
			char gimmick_No = 0;
			bool gimmick_No1 = 0;
			bool gimmick_No2 = 0;
			bool gimmick_No3 = 0;
			bool gimmick_No4 = 0;
			bool gimmick_No5 = 0;
			bool gimmick_No6 = 0;
			bool gimmick_No7 = 0;
			bool gimmick_No8 = 0;
			bool gimmick_No9 = 0;
			bool gimmick_No10 = 0;
			char have_knife_move = 0;
			bool go_end2 = 0;
			bool go_end2_1 = 0;
			bool go_end2_2 = 0;
			bool go_end2_3 = 0;
			bool go_end2_4 = 0;
			bool light_on_fire = 0;
		};
		struct ITEM {
			bool candle = 0;
			bool knife = 0;
			bool key = 0;
		};
		struct GAME {
			const enum {
				TITLE, STAGE, END1, END2, END3,BACK
			};
			char game_state = TITLE;
		};
		struct PLAYER p;
		struct STAGE s;
		struct OTHER o;
		struct GIMMICK gi;
		struct ITEM i;
		struct GAME g;
		bool Back_Scene = false;
	public:
		void initmap(struct STAGE* s_pointer);
		void INIT(struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void TITLE(struct GAME* g_pointer, struct OTHER* o_pointer, struct STAGE* s_pointer);
		void draw_player(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void draw_map(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void draw_map_player(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void use_item(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void move_player(struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void judge_collision(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void gimmick(struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void draw_gimmick(struct STAGE* s_pointer, struct PLAYER* p_pointer);
		void Go_END2(struct GAME* g_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer, struct OTHER* o_pointer);
		void Text(struct GAME* g_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer, struct OTHER* o_pointer);
		void Debug(struct STAGE* s_pointer);
		void STAGE(struct GAME* g_pointer, struct OTHER* o_pointer, struct GIMMICK* gi_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct ITEM* i_pointer);
		void END1(struct GAME* g_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void END2(struct GAME* g_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void END3(struct GAME* g_pointer, struct STAGE* s_pointer, struct PLAYER* p_pointer, struct GIMMICK* gi_pointer, struct ITEM* i_pointer);
		void Back_SCENE(struct GAME* g_pointer);
		bool Sent_Back_Scene();
		void Game_console();

	};
}