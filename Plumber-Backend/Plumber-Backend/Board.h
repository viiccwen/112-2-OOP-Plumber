#ifndef _BOARD_H_
#define _BOARD_H_

#include "Pipe.h"
#include<vector>
using namespace std;
enum class Position {
	LeftUp,
	LeftDown,
	RightUp,
	RightDown,
};

class Board {
private:
	int ROW;
	int COL;
	vector<vector<Pipe>> board;
	vector<vector<bool>> isSolution;
	vector<vector<string>> StraightShape = {
		{	"###",
			"PPP",
			"###" },
		{
			"#P#",
			"#P#",
			"#P#"}
	};

	vector<vector<string>> CornerShape = {
		{	"#P#",
			"#PP",
			"###"},
		{
			"###",
			"#PP",
			"#P#"},
		{
			"###",
			"PP#",
			"#P#"},
		{
			"#P#",
			"PP#",
			"###"},
	};

	vector<vector<string>> TShape = {
		{	"PPP",
			"#P#",
			"#P#"},
		{
			"P##",
			"PPP",
			"P##"},
		{
			"#P#",
			"#P#",
			"PPP"},
		{
			"#P#",
			"PP#",
			"#P#"},
	};

	vector<string> CrossShape = {
		"#P#",
		"PPP",
		"#P#"
	};
	
	// for random board generation
	Position start_pos;
	Position end_pos;
public:
	void SetBoardSize(int& row, int& col);
	void SetPipe(int x, int y, Type type, int rotation);
	void GenerateBoard();
	void GenerateSolution(int start, int end);
	void PrintBoard() const;
};

#endif _BOARD_H_