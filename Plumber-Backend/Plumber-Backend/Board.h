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
	// for random board generation
	Position start_pos;
	Position end_pos;

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
	void GenerateSolution(int start, int end);
	void PrintBoard(const int& x, const int& y) const;

private:
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
		{	"###",
			"PPP",
			"#P#"},
		{
			"#P#",
			"PP#",
			"#P#"},
		{
			"#P#",
			"PPP",
			"###"},
		{
			"#P#",
			"#PP",
			"#P#"},
	};

	vector<string> CrossShape = {
		"#P#",
		"PPP",
		"#P#"
	};
};

#endif _BOARD_H_