#include "../../libOne/inc/libOne.h"
//#include "../MAIN/MAIN.h"
//#include "GAME05.h"
#include<fstream>
#include"PLAYER.h"
#include"TITLE.h"
namespace GAME05 {
    void TITLE::TITLE_text() {
        fill(255);
        textSize(50);
        text("SPACE‚ÅSELECT‰æ–Ê‚Ö", 0, 500);

    }
    void TITLE::setImage(int Img) {
        StageImage = Img;
    }
    void TITLE::for_TITLE_LOAD() {
        fileName = "..\\MAIN\\assets\\game05\\stage_title.txt";
    }
    void TITLE::for_TITLE_INIT() {
        blockSize = 100;
        display_Cols = (width / blockSize) + 1.0f;
        endWorldX = blockSize * (cols - 2) - width;
    }
    void TITLE::FILE_OPEN_etc_MEMORY_ALLOCATION(FILE** fp_pointer) {
        fopen_s(fp_pointer, fileName, "rb");
        fseek(*fp_pointer, 0, SEEK_END);
        fileSize = ftell(*fp_pointer);
        fseek(*fp_pointer, 0, SEEK_SET);
        map = (char*)malloc(fileSize);
        if (map == NULL) {
            fclose(*fp_pointer);
            return;
        }
        fread(map, sizeof(char), fileSize, *fp_pointer);
        fclose(*fp_pointer);
        for (int i = 0; i < fileSize; i++) {
            count++;
            if (map[i] == '\n') {
                if (rows == 0) {
                    cols = count;
                }
                else if (cols != count) {
                    WARNING(1, "—ñ”‚ª‘µ‚Á‚Ä‚¢‚È‚¢.", "");
                }
                rows++;
                count = 0;
            }
        }
        if (fileSize % cols != 0) {
            WARNING(1, "‰üs‚µ‚Ä‚È‚¢.", "");
        }
    }

    void TITLE::WORLD_SCROLL() {
        worldX += 2;
        if (worldX >= endWorldX) {
            worldX = endWorldX;
        }
    }
    void TITLE::MAP_DRAW() {
        noStroke();
        fill(50, 0, 0);
        rect(0, 0, width, height);
        start_Cols = worldX / blockSize;
        end_Cols = start_Cols + display_Cols;
        for (int c = start_Cols; c < end_Cols; c++) {
            Block_X = -worldX + blockSize * c;
            for (int r = 0; r < rows; r++) {
                Block_Y = blockSize * r;
                index = r * cols + c;
                if (map[index] == 'b') {
                    image(StageImage, Block_X, Block_Y - 20);
                }
            }
        }
    }
    void TITLE::TITLE_Free() {
        free(map);
    }
}