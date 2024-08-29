//
// Created by elejandc on 8/29/24.
//

#include <algorithm>
#include <iostream>
#include <vector>

#include "SudokuBoard.h"

#define MAX_GENERATIONS 100
#define GENERATION_SIZE 100

int test1board[9][9] = {
    {0, 0, 0, 9, 6, 0, 5, 0, 4},
    {0, 2, 0, 1, 0, 0, 0, 6, 0},
    {5, 0, 0, 0, 0, 0, 8, 0, 9},
    {0, 3, 2, 0, 0, 0, 0, 5, 1},
    {1, 9, 6, 7, 5, 3, 0, 0, 2},
    {7, 0, 5, 0, 0, 0, 0, 9, 0},
    {9, 8, 4, 5, 0, 1, 0, 0, 6},
    {2, 0, 0, 0, 0, 9, 1, 0, 8},
    {0, 0, 0, 8, 2, 7, 9, 0, 0}
};

int main() {

    SudokuBoard default_board(*test1board);

    int current_generation = 1;

    //Init 1 generation
    std::vector<SudokuBoard> OldGeneration;
    for(int i = 0; i < GENERATION_SIZE; i++) {
        SudokuBoard child(default_board);
        child.fillBoard();
        OldGeneration.push_back(child);
    }

    //Sort children for _empty_spaces
    std::sort(OldGeneration.begin(), OldGeneration.end(), [](const SudokuBoard &a, const SudokuBoard &b) {
        return a.get_empty_spaces() < b.get_empty_spaces();
    });

    //Show best from 1 generation
    std::cout << "Best: " << OldGeneration[0].get_empty_spaces() << std::endl;
    OldGeneration[0].printBoard();


    return 0;
}