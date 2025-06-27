#pragma once
namespace GAME05 {
    class TITLE {
    private:
        int StageImage = 0;
        int BackImage = 0;
        const char* fileName = 0;
        int fileSize = 0;
        char* map = 0;
        int count = 0;
        int cols = 0;
        int rows = 0;
        int index = 0;
        float blockSize = 0;
        float Block_X = 0;
        float Block_Y = 0;
        float worldX = 0;
        float endWorldX = 0;
        int start_Cols = 0;
        int display_Cols = 0;
        int end_Cols = 0;
    public:
        void TITLE_text();
        void setImage(int Img);
        void for_TITLE_INIT();
        void for_TITLE_LOAD();
        void FILE_OPEN_etc_MEMORY_ALLOCATION(FILE** fp_pointer);
        void WORLD_SCROLL();
        void MAP_DRAW();
        void TITLE_Free();

    };
}