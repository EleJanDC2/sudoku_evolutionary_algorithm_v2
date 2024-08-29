//
// Created by elejandc on 8/29/24.
//

#include "SudokuBoard.h"

#include <algorithm>

SudokuBoard::SudokuBoard(int *init_board) {
    std::copy(init_board, init_board + 81, &_board[0][0]);

    this->_empty_spaces = static_cast<int> (std::count(init_board, init_board + 81, 0));
}

SudokuBoard::SudokuBoard(const SudokuBoard &other) {
    std::copy(&other._board[0][0], &other._board[0][0] + 81, &_board[0][0]);
    _row_contains = other._row_contains;
    _col_contains = other._col_contains;
    _block_contains = other._block_contains;
    _empty_spaces = other._empty_spaces;
}
