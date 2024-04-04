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
	enum start_pos {
		left_top = 1,
		left_down,
		right_top,
		right_down,
	};

	enum end_pos {
		left_top = 1,
		left_down,
		right_top,
		right_down,
	};
public:
	Board();
	void GenerateRandomBoard();
	void PrintBoard();
};

#endif _BOARD_H_