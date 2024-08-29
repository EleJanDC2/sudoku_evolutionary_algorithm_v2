//
// Created by elejandc on 8/29/24.
//

#include "SudokuBoard.h"

#include <algorithm>

SudokuBoard::SudokuBoard(int *init_board) {
    std::copy(init_board, init_board + 81, &_board[0][0]);

    this->_empty_spaces = static_cast<int> (std::count(init_board, init_board + 81, 0));
}
