#include "block.h"

#include <cassert>
#include <iostream>

#include "color.h"
#include "common.h"
#include "symbol.h"

CBlock::CBlock() : _count(0) {
}

bool CBlock::isValid() const {
    assert(MAX_COUNT == _count);

    for (int i = 0; i < _count - 1; ++i) {
        for (int j = i + 1; j < _count; ++j) {
            if (UNSELECTED == _numbers[i]->value ||
                UNSELECTED == _numbers[j]->value)
                continue;

            if (_numbers[i]->value == _numbers[j]->value) return false;
        }
    }
    return true;
}

bool CBlock::isFull() const {
    for (int i = 0; i < _count; ++i) {
        point_value_t *p_point_value = _numbers[i];
        if (nullptr == p_point_value || UNSELECTED == p_point_value->value)
            return false;
    }
    return true;
}

void CBlock::print() const {
    std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT, Color::FG_RED)
              << PIPE << Color::Modifier();
    for (int i = 1; i <= _count; ++i) {
        point_value_t number = *(_numbers[i - 1]);
        if (number.value == UNSELECTED) {
            std::cout << "   ";
        } else {
            if (number.state == State::ERASED) {
                std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                             Color::FG_GREEN)
                          << " " << number.value << " " << Color::Modifier();
            } else {
                std::cout << " " << number.value << " ";
            }
        }
        if (i % 3 == 0) {
            std::cout << Color::Modifier(Color::BOLD, Color::BG_DEFAULT,
                                         Color::FG_RED)
                      << PIPE << Color::Modifier();
        } else {
            std::cout << PIPE;
        }
    }
    std::cout << std::endl;
}

void CBlock::push_back(point_value_t *point) {
    assert(nullptr != point);
    _numbers[_count++] = point;
}
