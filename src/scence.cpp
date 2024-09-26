// #include "scence.h"

#include "scence.h"

#include <conio.h>
#include <memory.h>

#include <cassert>
#include <ctime>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "block.h"
#include "color.h"
#include "symbol.h"

// not real random,return number between [begin,end]
inline unsigned int random(int begin, int end) {
    assert(end >= begin && begin >= 0);
    srand(time(NULL));
    return (unsigned int)rand() % (end - begin + 1) + begin;
}

CScene::CScene() : _cur_point({0, 0}) {
    init();
}

CScene::~CScene() {
}

void CScene::init() {
    memset(_map, UNSELECTED, sizeof _map);
    // column_block 所有列
    for (int col = 0; col < max_column; ++col) {
        CBlock column_block;

        for (int row = 0; row < max_column; ++row) {
            column_block.push_back(_map + row * 9 + col);
        }
        _column_block[col] = column_block;
    }

    // row_block 所有行
    for (int row = 0; row < max_column; ++row) {
        CBlock row_block;

        for (int col = 0; col < max_column; ++col) {
            row_block.push_back(_map + row * 9 + col);
        }
        _row_block[row] = row_block;
    }

    // xy_block 所有九宫格, [行][列]
    for (int block_index = 0; block_index < max_column; ++block_index) {
        CBlock xy_block;

        int xy_begin = block_index / 3 * 27 + block_index % 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                xy_block.push_back(_map + xy_begin + i * 9 + j);
            }
        }
        _xy_block[block_index / 3][block_index % 3] = xy_block;
    }

    return;
}

void CScene::draw() {
    drawUnderLine(0);
    for (int i = 0; i < 9; ++i) {
        _row_block[i].print();
        drawUnderLine(i + 1);
    }
}

void CScene::setValue(const point_t &p, const int value) {
    _map[p.x + p.y * 9].value = value;
}
/**
 * no_line行号
 */
void CScene::drawUnderLine(int no_line) {
    // 当前行号是否相同
    bool is_curline = ((_cur_point.y + 1) == no_line);
    for (int colunm = 0; colunm < 9; ++colunm) {
        if (no_line == 0 || no_line % 3 == 0 || colunm % 3 == 0) {
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_RED)
                      << CORNER << Color::Modifier();
        } else {
            std::cout << CORNER;
        }
        auto third_symbol =
            (is_curline && _cur_point.x == colunm) ? ARROW : LINE;
        if (no_line == 0 || no_line % 3 == 0) {
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_RED)
                      << LINE << third_symbol << LINE << Color::Modifier();
        } else {
            std::cout << LINE << third_symbol << LINE;
        }
    }
    std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED)
              << CORNER << Color::Modifier() << std::endl;
}

void CScene::generate() {
    // 符合九宫格的图案
    static const char map_pattern[9][10] = {
        "ighcabfde", "cabfdeigh", "fdeighcab", "ghiabcdef", "abcdefghi",
        "defghiabc", "higbcaefd", "bcaefdhig", "efdhigbca"};
    //  将a~i在1~9中进行随机映射，以此在每次产生不同的结果
    std::vector<char> v = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    std::unordered_map<char, int> hash_map;
    for (int i = 1; i <= 9; ++i) {
        int idx = random(0, v.size() - 1);
        hash_map[v[idx]] = i;
        v.erase(v.begin() + idx);
    }
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            point_t point = {row, col};
            setValue(point, hash_map[map_pattern[row][col]]);
        }
    }
    assert(isComplete());
}
// 生成是否完成生成数据
bool CScene::isComplete() {
    for (int i = 0; i < 81; i++) {
        if (_map[i].value == UNSELECTED) {
            return false;
        }
    }
    for (int row = 0; row < 9; ++row) {
        if (!_row_block[row].isValid()) return false;
    }
    for (int col = 0; col < 9; ++col) {
        if (!_column_block[col].isValid()) return false;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!_xy_block[i][j].isValid()) return false;
        }
    }
    return true;
}

void CScene::eraseRandomGrids(const int count) {
    point_value_t p = {UNSELECTED, State::ERASED};
    std::vector<int> v(81);
    for (int i = 0; i < 81; ++i) {
        v[i] = i;
    }
    for (int i = 0; i < count; ++i) {
        int r = random(0, v.size() - 1);
        _map[v[r]] = p;
        v.erase(v.begin() + r);
    }
}

void CScene::move(point_t p) {
    std::cout << "\033[" << p.y << ";" << p.x << "H";
}

void CScene::move() {
    std::cout << "\033[" << 2 * (_cur_point.y + 1) + 1 << ";"
              << 4 * _cur_point.x + 3 << "H";
}
void CScene::moveToEnd() {
    std::cout << "\033[" << 20 << ";" << 1 << "H";
}

void CScene::play() {
    draw();
    char key = '\0';
    while (true) {
        key = _getch();
        move();
        if ((_cur_point.y + 1) % 3 == 0) {
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_RED)
                      << LINE << Color::Modifier();
        } else {
            std::cout << LINE;
        }
        moveToEnd();
        if (key == 'w' || key == 'W') {
            _cur_point.y = (_cur_point.y - 1) < 0 ? 0 : _cur_point.y - 1;
        } else if (key == 's' || key == 'S') {
            _cur_point.y = (_cur_point.y + 1) > 8 ? 8 : _cur_point.y + 1;
        } else if (key == 'a' || key == 'A') {
            _cur_point.x = (_cur_point.x - 1) < 0 ? 0 : _cur_point.x - 1;
        } else if (key == 'd' || key == 'D') {
            _cur_point.x = (_cur_point.x + 1) > 8 ? 8 : _cur_point.x + 1;
        } else if (key >= '1' && key <= '9' &&
                   _map[_cur_point.x + _cur_point.y * 9].state ==
                       State::ERASED) {
            _map[_cur_point.x + _cur_point.y * 9].value = int(key - '0');
            move({4 * _cur_point.x + 3, 2 * (_cur_point.y + 1)});
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_GREEN)
                      << key << Color::Modifier();
            if (isComplete()) {
                moveToEnd();
                std::cout << "恭喜你完成了本次游戏！！!";
                key = _getch();
                return;
            }
        }
        move();
        if ((_cur_point.y + 1) % 3 == 0) {
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_RED)
                      << ARROW << Color::Modifier();
        } else {
            std::cout << ARROW;
        }
        moveToEnd();
    }
}