#ifndef _BOARD_H_
#define _BOARD_H_

#include "Pipe.h"
#include<vector>

class Board {
private:
	int ROW;
	int COL;
	std::vector<Pipe> board;
	
	// for random board generation
	int start_pos;
	int end_pos;
public:
	Board() {};
	void SetBoardSize(int& row, int& col);
	void GenerateRandomBoard();
	void PrintBoard();
};

#endif _BOARD_H_