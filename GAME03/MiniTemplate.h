#pragma once

#include <vector>
#include <utility>

enum DIR {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct MiniTemplate {
    int  cell[3][3];
    bool canStart[3][3];
    bool canGoal[3][3];

    std::vector<std::pair<int, int>> mainPath;
    DIR arrow[3][3];
};

extern const std::vector<MiniTemplate> g_miniTemplates;
MiniTemplate rotate90(const MiniTemplate& src);
MiniTemplate rotate180(const MiniTemplate& src);
MiniTemplate rotate270(const MiniTemplate& src);
MiniTemplate flipHorizontal(const MiniTemplate& src);
std::vector<MiniTemplate> generateVariants(const MiniTemplate& base);

