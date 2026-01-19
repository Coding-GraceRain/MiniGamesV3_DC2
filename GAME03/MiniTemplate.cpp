#include "MiniTemplate.h"
static const std::vector<MiniTemplate> g_miniTemplates = {
    {
        {
            {0,0,0},
            {0,0,0},
            {0,0,0}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,true}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {1,0,0},
            {0,0,0},
            {0,0,0}
        },
        {
            {false,true,true},
            {true,false,true},
            {true,true,true}
        },
        {
            {false,true,true},
            {true,false,true},
            {true,true,true}
        }
    },
    {
        {
            {0,0,1},
            {0,0,0},
            {0,0,0}
        },
        {
            {true,true,false},
            {true,false,true},
            {true,true,true}
        },
        {
            {true,true,false},
            {true,false,true},
            {true,true,true}
        }
    },
    {
        {
            {0,0,0},
            {0,0,0},
            {1,0,0}
        },
        {
            {true,true,true},
            {true,false,true},
            {false,true,true}
        },
        {
            {true,true,true},
            {true,false,true},
            {false,true,true}
        }
    },
    {
        {
            {0,0,0},
            {0,0,0},
            {0,0,1}
        },
        {
            {true,true,true},
            {true,false,true},
            {true,true,false}
        },
        {
            {true,true,true},
            {true,false,true},
            {true,true,false}
        }
    },
    {
        {
            {1,1,0},
            {0,0,0},
            {0,0,0}
        },
        {
            {false,false,true},
            {false,false,false},
            {true,false,true}
        },
        {
            {false,false,true},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {1,0,1},
            {0,0,0},
            {0,0,0}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,false,false}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,false,false}
        }
    },
    {
        {
            {1,0,0},
            {1,0,0},
            {0,0,0}
        },
        {
            {false,false,true},
            {false,false,false},
            {true,false,true}
        },
        {
            {false,false,true},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {1,0,0},
            {0,1,0},
            {0,0,0}
        },
        {
            {false,true,false},
            {true,false,false},
            {false,false,false}
        },
        {
            {false,true,false},
            {true,false,false},
            {false,false,false}
        }
    },
    {
        {
            {1,0,0},
            {0,0,1},
            {0,0,0}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        }
    },
    {
        {
            {1,0,0},
            {0,0,0},
            {1,0,0}
        },
        {
            {false,true,false},
            {true,false,false},
            {false,true,false}
        },
        {
            {false,true,false},
            {true,false,false},
            {false,true,false}
        }
    },
    {
        {
            {1,0,0},
            {0,0,0},
            {0,1,0}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {1,0,0},
            {0,0,0},
            {0,0,1}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,true,false}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,true,false}
        }
    },
    {
        {
            {0,1,1},
            {0,0,0},
            {0,0,0}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,true}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {0,1,0},
            {0,1,0},
            {0,0,0}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        }
    },
    {
        {
            {0,1,0},
            {0,0,0},
            {1,0,0}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        }
    },
    {
        {
            {0,1,0},
            {0,0,0},
            {0,0,1}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,false}
        }
    },
    {
        {
            {0,0,1},
            {1,0,0},
            {0,0,0}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        }
    },
    {
        {
            {0,0,1},
            {0,1,0},
            {0,0,0}
        },
        {
            {false,true,false},
            {false,false,true},
            {false,false,false}
        },
        {
            {false,true,false},
            {false,false,true},
            {false,false,false}
        }
    },
    {
        {
            {0,0,1},
            {0,0,1},
            {0,0,0}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,true}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {0,0,1},
            {0,0,0},
            {1,0,0}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,true,false}
        },
        {
            {false,true,false},
            {true,false,true},
            {false,true,false}
        }
    },
    {
        {
            {0,0,1},
            {0,0,0},
            {0,1,0}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {0,0,1},
            {0,0,0},
            {0,0,1}
        },
        {
            {false,true,false},
            {false,false,true},
            {false,true,false}
        },
        {
            {false,true,false},
            {false,false,true},
            {false,true,false}
        }
    },
    {
        {
            {0,0,0},
            {1,1,0},
            {0,0,0}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        }
    },
    {
        {
            {0,0,0},
            {1,0,0},
            {1,0,0}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,true}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,true}
        }
    },
    {
        {
            {0,0,0},
            {1,0,0},
            {0,0,1}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        },
        {
            {true,false,false},
            {false,false,false},
            {true,false,false}
        }
    },
    {
        {
            {0,0,0},
            {0,1,1},
            {0,0,0}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        }
    },
    {
        {
            {0,0,0},
            {0,1,0},
            {1,0,0}
        },
        {
            {false,false,false},
            {true,false,false},
            {false,true,false}
        },
        {
            {false,false,false},
            {true,false,false},
            {false,true,false}
        }
    },
    {
        {
            {0,0,0},
            {0,1,0},
            {0,1,0}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        },
        {
            {false,false,false},
            {false,false,false},
            {true,false,true}
        }
    },
    {
        {
            {0,0,0},
            {0,1,0},
            {0,0,1}
        },
        {
            {false,false,false},
            {false,false,true},
            {false,true,false}
        },
        {
            {false,false,false},
            {false,false,true},
            {false,true,false}
        }
    },
    {
        {
            {0,0,0},
            {0,0,1},
            {1,0,0}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        },
        {
            {false,false,true},
            {false,false,false},
            {false,false,true}
        }
    },
    {
        {
            {0,0,0},
            {0,0,1},
            {0,0,1}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,false}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,false}
        }
    },
    {
        {
            {0,0,0},
            {0,0,0},
            {1,1,0}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,true}
        },
        {
            {true,false,true},
            {false,false,false},
            {false,false,true}
        }
    },
    {
        {
            {0,0,0},
            {0,0,0},
            {1,0,1}
        },
        {
            {false,false,false},
            {true,false,true},
            {false,true,false}
        },
        {
            {false,false,false},
            {true,false,true},
            {false,true,false}
        }
    },
    {
        {
            {0,0,0},
            {0,0,0},
            {0,1,1}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,false}
        },
        {
            {true,false,true},
            {false,false,false},
            {true,false,false}
        }
    }
};

void buildArrowFromPath(MiniTemplate& t)
{
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            t.arrow[y][x] = NONE;

    for (size_t i = 0; i + 1 < t.mainPath.size(); i++)
    {
        int x1 = t.mainPath[i].first;
        int y1 = t.mainPath[i].second;
        int x2 = t.mainPath[i + 1].first;
        int y2 = t.mainPath[i + 1].second;

        if (x2 == x1 + 1) t.arrow[y1][x1] = RIGHT;
        else if (x2 == x1 - 1) t.arrow[y1][x1] = LEFT;
        else if (y2 == y1 + 1) t.arrow[y1][x1] = DOWN;
        else if (y2 == y1 - 1) t.arrow[y1][x1] = UP;
    }
}


std::vector<std::pair<int, int>>
rotatePath90(const std::vector<std::pair<int, int>>& src)
{
    std::vector<std::pair<int, int>> dst;
    for (const auto& p : src)
    {
        int x = p.first;
        int y = p.second;
        dst.emplace_back(2 - y, x);
    }
    return dst;
}




MiniTemplate rotate270(const MiniTemplate& t)
{
    return rotate90(rotate180(t));
}


MiniTemplate rotate90(const MiniTemplate& src)
{
    MiniTemplate dst = {};

    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x) {
            dst.cell[x][2 - y] = src.cell[y][x];
            dst.canStart[x][2 - y] = src.canStart[y][x];
            dst.canGoal[x][2 - y] = src.canGoal[y][x];
        }

    return dst;
}
MiniTemplate rotate180(const MiniTemplate& t)
{
    return rotate90(rotate90(t));
}

MiniTemplate flipHorizontal(const MiniTemplate& src)
{
    MiniTemplate dst = {};

    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x) {
            dst.cell[y][2 - x] = src.cell[y][x];
            dst.canStart[y][2 - x] = src.canStart[y][x];
            dst.canGoal[y][2 - x] = src.canGoal[y][x];
        }

    return dst;
}

std::vector<MiniTemplate> generateVariants(const MiniTemplate& base)
{
    std::vector<MiniTemplate> v;
    MiniTemplate t = base;

    for (int i = 0; i < 4; ++i) {
        v.push_back(t);
        v.push_back(flipHorizontal(t));
        t = rotate90(t);
    }

    return v;
}

