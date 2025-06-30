#pragma once
namespace GAME04 {
	class ENEMYBULLET {
	public:




        int hp = 0;
        float px = 0;
        float py = 0;
        float vx = 0;
        float vy = 20.0f;
        float pr = 20.0f;
        float h = 20.0f;
        void move();
        void draw();
        void shoot(float ex, float ey, float vx_, float vy_);

	};

}