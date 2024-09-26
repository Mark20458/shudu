#ifndef _SUDOKU_SCENCE_H
#define _SUDOKU_SCENCE_H

#include "block.h"

class CScene {
private:
    const static int max_column = 9;
    point_t _cur_point;      // 箭头位置
    point_value_t _map[81];  // 存储的九宫格值
    CBlock _column_block[9];
    CBlock _row_block[9];
    CBlock _xy_block[3][3];

private:
    void setValue(const point_t &, const int);
    bool isComplete();
    void move();  // 移动箭头位置
    void move(point_t p);
    void moveToEnd();

public:
    CScene();
    ~CScene();
    void init();  // 将_map数据的地址映射到_column_block,_row_block,_xy_block
    void generate();                         // 生成数据
    void draw();                             // 画整个方框
    void drawUnderLine(int no_line);         // 画下划线
    void eraseRandomGrids(const int count);  // 选择count个格子清空
    void play();
};
#endif