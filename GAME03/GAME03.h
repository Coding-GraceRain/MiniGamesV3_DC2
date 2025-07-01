#pragma once
#include <vector>
#include "../MAIN/GAME_BASE.h"

namespace GAME03 {

    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main);

        int  create()  override;
        void proc()    override;
        void destroy() override;

    private:
        enum STATE { TITLE, PLAY, CLEAR };

        static const int SIZE = 10;
        static const int EMPTY = 0;
        static const int BLOCK = 2;

        STATE State = TITLE;
        bool  playInitFlg = false;
        bool  prevEnterKey = false;

        int selectedDifficulty = 0;      // ��Փx�i0:�ȒP, 1:����, 2:����j
        int selectedMapIndex = 0;        // �}�b�v�ԍ��i0�`4�j
        int numBlocks = 0;               // �u���b�N���i�Q�l�p�j
        int titleBgm = -1;
        int playBgm = -1;
        int clearBgm = -1;
        int  board[SIZE][SIZE];          // �}�b�v�f�[�^
        bool visited[SIZE][SIZE];        // �K��t���O
        int  px = 0, py = 0;             // �v���C���[�ʒu

        int  visitCount = 0;             // �K��ς݃}�X��
        int  totalEmpty = SIZE * SIZE;   // �ʂ��}�X��
        bool gameClear = false;


        std::vector<std::pair<int, int>> path;           // �X�l�[�N��̏����o�H
        std::vector<std::pair<int, int>> moveHistory;    // �ړ������iZ�L�[�p�j
        std::vector<std::pair<int, int>> shortestPath;   // �ŒZ�o�H�i���g�p�j
        std::vector<std::pair<int, int>> highlightPath;  // �o�H�n�C���C�g�\���p

        // �e�����֐�
        void resetVisited();
        void generateMap();                              // �}�b�v�����i�Œ�}�b�v�ɐؑցj
        void drawBoard();                                // �}�b�v�`��
        void handleInput();                              // ���͏���
        void restartPlay();                              // ���X�^�[�g

        void loadPredefinedMap(int difficulty, int index);  // �Œ�}�b�v��ǂݍ���
        void drawCenteredText(const char* str, int centerX, int y, int size = 24); // �����`��⏕
    };

} // namespace GAME03
