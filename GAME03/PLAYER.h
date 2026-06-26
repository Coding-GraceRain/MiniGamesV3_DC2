#pragma once
#include "CHARACTER.h"
#include "../../libOne/inc/libOne.h"
namespace GAME03
{
	class PLAYER :
		public CHARACTER
	{
	public:
		struct DATA {
			float curWx = 0;
			float gravity = 0;
			float initVy = 0;
			int jumpFlag = 0;
		};
	private:
		DATA Player;
		enum class STATE { STRUGGLING, DIED, FALL, SURVIVED };
		STATE State = STATE::STRUGGLING;
	public:
		PLAYER(class GAME* game);
		void create();
		void appear(float x, float y, float vx, float vy);
		void update();
		void Move();
		void CollisionWithMap();
		void CheckState();
		void damage();
		bool died();
		bool survived();
	};
}