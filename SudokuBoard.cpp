//
// Created by elejandc on 8/29/24.
//

#include "SudokuBoard.h"

#include <algorithm>
#include <iostream>

SudokuBoard::SudokuBoard(int *init_board) {
    std::copy(init_board, init_board + 81, &_board[0][0]);

    this->_empty_spaces = static_cast<int>(std::count(init_board, init_board + 81, 0));
}

SudokuBoard::SudokuBoard(const SudokuBoard &other) {
    std::copy(&other._board[0][0], &other._board[0][0] + 81, &_board[0][0]);
    _row_contains = other._row_contains;
    _column_contains = other._column_contains;
    _block_contains = other._block_contains;
    _empty_spaces = other._empty_spaces;
}

SudokuBoard::SudokuBoard(const SudokuBoard &initial, const SudokuBoard &parent1, const SudokuBoard &parent2,
                         int mutate_percent) {
    std::copy(&initial._board[0][0], &initial._board[0][0] + 81, &_board[0][0]);
    _row_contains = initial._row_contains;
    _column_contains = initial._column_contains;
    _block_contains = initial._block_contains;
    _empty_spaces = initial._empty_spaces;

    int connection_cycles = 0;
    int attempts = 0;
    bool parent_turn = 0;
    const SudokuBoard *current_parrent = nullptr;

    // Try fill new board 'child' until we find a solution or we reach max number of attempts
    while (attempts < 100 && _empty_spaces > 0) {
        // Change parent turn
        parent_turn = !parent_turn;
        current_parrent = parent_turn ? &parent1 : &parent2;

        //Choose random row and column
        int row = rand() % 9;
        int col = rand() % 9;

        int num = 0;
        if (rand() % 100 < mutate_percent) num = rand() % 9 + 1;
        else num = current_parrent->_board[row][col];

        if (current_parrent->_board[row][col] == 0) {
            attempts++;
            continue;
        }

        if (canBeFilled(row, col, num)) {
            _board[row][col] = num;
            _column_contains[col].set(num - 1);
            _row_contains[row].set(num - 1);
            _block_contains[row / 3 * 3 + col / 3].set(num - 1);
            _empty_spaces--;
            attempts = 0;
            break;
        } else attempts++;
    }
}

bool SudokuBoard::canBeFilled(int row, int col, int num) {
    if (_board[row][col] != 0) return false;

    if (_row_contains[row].test(num - 1) || _column_contains[col].test(num - 1) || _block_contains[
            row / 3 * 3 + col / 3].test(num - 1)) return false;

    return true;
}

void SudokuBoard::fillBoard() {
    int attempts = 0;

    while(attempts < 100 && _empty_spaces > 0) {
        int row = rand() % 9;
        int col = rand() % 9;
        int num = rand() % 9 + 1;

        if(canBeFilled(row, col, num)) {
            _board[row][col] = num;
            _column_contains[col].set(num - 1);
            _row_contains[row].set(num - 1);
            _block_contains[row / 3 * 3 + col / 3].set(num - 1);
            _empty_spaces--;
            attempts = 0;
        } else attempts++;
    }
}

int SudokuBoard::printBoard() {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << _board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

bool SudokuBoard::operator==(const SudokuBoard &other) const {
    return std::equal(&_board[0][0], &_board[0][0] + 81, &other._board[0][0]);
}
