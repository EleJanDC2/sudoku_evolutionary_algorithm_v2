//
// Created by elejandc on 8/29/24.
//

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H
#include <array>
#include <bitset>


class SudokuBoard {
public:
    SudokuBoard(int * init_board);

    SudokuBoard(const SudokuBoard &other);

    SudokuBoard(const SudokuBoard &initial, const SudokuBoard &parent1, const SudokuBoard &parent2,int mutate_percent = 0);

private:
    int _board[9][9];
    std::array<std::bitset<9>, 9> _row_contains;
    std::array<std::bitset<9>, 9> _column_contains;
    std::array<std::bitset<9>, 9> _block_contains;

    int _empty_spaces = 81;



    bool canBeFilled(int row, int col, int num);
};



#endif //SUDOKUBOARD_H
