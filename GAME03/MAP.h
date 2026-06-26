#pragma once
#include "GAME_OBJECT.h"
namespace GAME03
{
	class MAP :
		public GAME_OBJECT
	{
	public:
		struct DATA {
			char* map = 0;
			//const char* fileName = 0;
			int chipSize = 0;
			int cols = 0;
			int rows = 0;
			int mapNumber = 0;

			int blockImg = 0;
			int barrierImg = 0;
			float px = 0, py = 0;
			int gimmickButton = 0;
		};
		enum CHARA_ID {
			BLOCK_ID = '1',
			BARRIER_ID = '2',
			BUTTON_ID = 'b',
			TURRET_BULLET_ID = 'e',
			PLAYER_ID = 'p',
			TURRET_ID = 't'
		};
	private:
		DATA Map;
	public:
		MAP(class GAME* game);
		~MAP();
		void init(const char* fileName);
		void draw();
		void create();

		bool collisionCheck(float wx, float wy);
		bool collisionCharaLeft(float wx, float wy);
		bool collisionCharaRight(float wx, float wy);
		bool collisionCharaTop(float wx, float wy);
		bool collisionCharaBottom(float wx, float wy);
		bool collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom);

		int chipSize() { return Map.chipSize; }
		int gimmickButton() { return Map.gimmickButton; }
		void gimmick();

	};
}