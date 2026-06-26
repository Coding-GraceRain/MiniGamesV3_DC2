#pragma once
class PLAYER {
private:
	float x, y;
	float vy;
	int jumpCount;
	bool isJump;
	int anime;
	int animeTimer;
	const float width = 40;
	const float height = 80;
public:


	void init();
	void update(int seJump);
	void draw(int imgSoldier[3]);

	void setY(float ny) { y = ny; }
	void setVy(float nvy) { vy = nvy; }
	void resetjump() { jumpCount = 0; }

	float getx() const { return x; }
	float gety() const { return y; }
	float getw() const { return width; }
	float geth() const { return height; }
	float getvy() const { return vy; }
	int getjumpCount() const { return jumpCount; }
};