#ifndef _SUDOKU_COMMON_H_
#define _SUDOKU_COMMON_H_
static const unsigned int UNSELECTED = 0;

enum class State : int {
    INITED = 0,
    ERASED,
};

struct point_t {
    int x;
    int y;
};

struct point_value_t {
    int value;
    State state;
};

#endif