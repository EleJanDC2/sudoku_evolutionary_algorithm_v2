//
// Created by elejandc on 8/29/24.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

#include "SudokuBoard.h"

#define MAX_GENERATIONS 100
#define GENERATION_SIZE 1000

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

int test3board[9][9] = {
    {9, 0, 2, 3, 0, 0, 8, 0, 1},
    {0, 1, 5, 0, 0, 0, 3, 0, 0},
    {4, 0, 7, 0, 0, 0, 0, 5, 6},
    {0, 0, 8, 0, 0, 7, 1, 0, 2},
    {0, 0, 0, 0, 2, 6, 5, 9, 0},
    {0, 0, 0, 5, 8, 0, 0, 0, 4},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 6, 0, 0, 0, 0, 5},
    {0, 7, 9, 2, 0, 5, 0, 0, 0}
};

int test6board[9][9] = {
    {9, 0, 0, 1, 0, 0, 0, 4, 0},
    {0, 7, 0, 6, 0, 0, 3, 0, 9},
    {0, 0, 0, 0, 3, 0, 0, 5, 0},
    {0, 5, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 4},
    {1, 0, 0, 0, 2, 0, 9, 0, 6},
    {5, 0, 0, 0, 6, 0, 2, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 3, 0},
    {0, 0, 8, 7, 0, 0, 0, 0, 0}
};

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());


    SudokuBoard default_board(*test6board);

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


    while(current_generation < MAX_GENERATIONS) {
        std::vector<SudokuBoard> NewGeneration;
        for(int i = 0; i < GENERATION_SIZE; i++) {
            int parent1 = std::uniform_int_distribution<>(0, GENERATION_SIZE-1 / 10)(gen);
            int parent2 = std::uniform_int_distribution<>(0, GENERATION_SIZE-1 / 10)(gen);
            while(OldGeneration[parent1] == OldGeneration[parent2]) parent2 = std::uniform_int_distribution<>(0, GENERATION_SIZE-1)(gen);
            SudokuBoard child(OldGeneration[parent1], OldGeneration[parent2], default_board, 0);
            NewGeneration.push_back(child);
        }

        //Sort children for _empty_spaces
        std::sort(NewGeneration.begin(), NewGeneration.end(), [](const SudokuBoard &a, const SudokuBoard &b) {
            return a.get_empty_spaces() < b.get_empty_spaces();
        });

        //Show best from generation
        std::cout << "GENERATION : " << current_generation <<  "    Best: " << NewGeneration[0].get_empty_spaces() << std::endl;
        NewGeneration[0].printBoard();

        if(NewGeneration[0].get_empty_spaces() == 0) break;

        OldGeneration = NewGeneration;
        current_generation++;
    }


    return 0;
}