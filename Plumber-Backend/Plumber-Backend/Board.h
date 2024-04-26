#ifndef _BOARD_H_
#define _BOARD_H_

#include "Pipe.h"
#include "Player.h"
#include<vector>
#include<queue>

using namespace std;

enum class Corner {
	LeftUp,
	LeftDown,
	RightUp,
	RightDown,
};

class Board {
private:
	// for random board generation
	Corner startCorner;
	Corner endCorner;

	pair<int, int> startPosition;
	pair<int, int> endPosition;

	int WaterPath_Color = 159;
	int CurPosition_SolutionPath_Color = 236;
	int CurPosition_Color = 224;
	int SolutionPath_Color = 12;
	int Else_Color = 7;
public:
	static int ROW;
	static int COL;

	void SetBoardSize(int& row, int& col);
	void SetPipe(int x, int y, Type type, int rotation);
	void RotatePipe(int x, int y);
	void GenerateBoard();
	void SetupBoard(vector<vector<char>> board_vec);
	void GenerateSolution();
	void PrintBoard(const int& x, const int& y) const;
	void InjectWater();
	bool FindSolutionPath(pair<int, int> cur_pos, pair<int, int>& end_pos, vector<pair<int, int>> temp_solution, vector<pair<int, int>>& solution, vector<vector<bool>>& visited);
	bool IsGameOver();
private:
	vector<vector<Pipe>> board;
	vector<vector<bool>> isSolution;

	int directions[4][2] = { {0,-1}, {1,0}, {0,1}, {-1,0} };
};

#endif _BOARD_H_