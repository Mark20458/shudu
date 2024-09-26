#ifndef _SUDOKU_BLOCK_H_
#define _SUDOKU_BLOCK_H_

#include "common.h"
// 数独行政区域类
class CBlock {
    static const int MAX_COUNT = 9;

public:
    CBlock();
    // 检查是否有重复值
    bool isValid() const;
    bool isFull() const;
    void push_back(point_value_t *point);
    void print() const;

private:
    int _count;
    point_value_t *_numbers[MAX_COUNT];  // 地址
};
#endif