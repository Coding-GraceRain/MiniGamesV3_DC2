#include"GAME_SCENE_CHANGE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME14 {
	int GAME_SCENE::GAME_SELECT() {
		rectMode(CENTER);
		fill(255);
		textSize(50);
		text("‚Ð‚ç‚ª‚ÈŽZ", (Yoko / 4)-200, ((Tate / 2)));
		text("EXPLOIT", Yoko - (Yoko / 4), ((Tate / 2)));
		rect((Yoko / 5), ((Tate / 3)*2), TILE_SIZE, TILE_SIZE);
		rect(Yoko-(Yoko / 5), ((Tate / 3)*2), TILE_SIZE, TILE_SIZE);
		if (mouseX>((Yoko / 5) - (TILE_SIZE / 2)) && mouseX <((Yoko / 5) + (TILE_SIZE / 2)) && mouseY>(((Tate / 3)*2) - (TILE_SIZE / 2)) && mouseY <(((Tate / 3)*2) + (TILE_SIZE / 2))) {
			fill(0, 255, 255);;
			rect((Yoko / 5), ((Tate / 3) * 2), TILE_SIZE, TILE_SIZE);
			return 1;
		}
		else if (mouseX>((Yoko-(Yoko / 5)) - (TILE_SIZE / 2)) && mouseX <((Yoko-(Yoko / 5)) + (TILE_SIZE / 2)) && mouseY>(((Tate / 3) * 2) - (TILE_SIZE / 2)) && mouseY <(((Tate / 3) * 2) + (TILE_SIZE / 2))) {
			fill(0, 255, 255);;
			rect(Yoko - (Yoko / 5), ((Tate / 3) * 2), TILE_SIZE, TILE_SIZE);
			return 2;
		}
		else {
			return 0;
		}
		rectMode(CORNER);
	}
}