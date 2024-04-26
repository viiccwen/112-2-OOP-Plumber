#pragma once
#include "Board.h"

#include<vector>
#include<iostream>
#include<Windows.h>
using namespace std;

int Board::ROW = 0;
int Board::COL = 0;

void Board::SetBoardSize(int& row, int& col) {
	ROW = row;
	COL = col;
}

void Board::SetPipe(int x, int y, Type type, int rotation) {
	board[x][y].SetType(type);
	board[x][y].SetRotation(rotation);
}

void Board::RotatePipe(int x, int y) {
	board[x][y].RotatePipe();
}

void Board::SetupBoard(vector<vector<char>> board_vec) {
	board.assign(ROW, std::vector<Pipe>(COL));
	isSolution.assign(ROW, std::vector<bool>(COL, false));

	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			pair<Type, int> pipe_pair;
			pipe_pair = Pipe::DetectPipe(board_vec, {row, col});
			SetPipe(row, col, pipe_pair.first, pipe_pair.second);
		}
	}

	GenerateSolution();
}

void Board::GenerateBoard() {
	board.assign(ROW, std::vector<Pipe>(COL));
	isSolution.assign(ROW, std::vector<bool>(COL, false));

	/* TODO: need to more flexible */

	int start, end;
	startCorner = Corner::LeftUp;
	endCorner = Corner::RightDown;

	srand(time(NULL));
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			if (row == 0 && col == 0) {
				Type type = Type::Cross;
				int rotation = 0;
				SetPipe(row, col, type, rotation);
				continue;
			}

			Type type = static_cast<Type>(rand() % 4);
			int rotation = (rand() % 4) * 90;
			SetPipe(row, col, type, rotation);
		}
	}

	/* TODO: need to make every position */
	GenerateSolution();
}

bool Board::FindSolutionPath(Board& dup_board, pair<int, int> cur_pos, pair<int, int>& end_pos, vector<pair<int, int>>& solution, vector<vector<bool>>& visited) {
	int curX = cur_pos.first;
	int curY = cur_pos.second;
	
	solution.push_back({ curX, curY });
	visited[curX][curY] = true;

	if (curX == end_pos.first && curY == end_pos.second) {
		return true;
	}
	
	Pipe curPipe = dup_board.board[curX][curY];

	for (int i = 0; i < 4; i++) {
		if (!curPipe.GetConnected()[i]) continue;

		int nextX = curX + directions[i].first;
		int nextY = curY + directions[i].second;

		if (nextX < 0 || nextX >= ROW) continue;
		if (nextY < 0 || nextY >= COL) continue;
		if (visited[nextX][nextY]) continue;

		Pipe& nextPipe = dup_board.board[nextX][nextY];
		int rotation_limit = 1;

		switch (nextPipe.GetType())
		{
		case Type::Straight:
			rotation_limit = 2;
			break;
		case Type::TShape:
			rotation_limit = 4;
			break;
		case Type::Corner:
			rotation_limit = 4;
			break;
		case Type::Cross:
			rotation_limit = 1;
			break;
		}

		for (int j = 0; j < rotation_limit; ++j) {
			int rotation = j * 90;
			nextPipe.SetRotation(rotation);

			if (!nextPipe.GetConnected()[(i + 2) % 4] ) continue;
			if ( FindSolutionPath(dup_board, { nextX, nextY }, end_pos, solution, visited) ) return true;
			
			solution.pop_back();
		}
	}
}

/* HOTFIX: BUG with generateSolution */
void Board::GenerateSolution() {
	srand(time(NULL));

	/* TODO: need to make every position */
	vector<pair<int, int>> solution;
	pair<int, int> end_pos = { ROW - 1, COL - 1 };
	vector<vector<bool>> visited(ROW, vector<bool>(COL, false));

	/* TODO: need more flexible writing */
	Board dup_board;
	dup_board.board = board;
	FindSolutionPath(dup_board, { 0, 0 }, end_pos, solution, visited);
	
	for (auto pir : solution) {
		isSolution[pir.first][pir.second] = true;
	}
}

// for color (from google)
void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


void Board::PrintBoard(const int& x, const int& y) const {
	system("cls");

	for (int row = 0; row < ROW; ++row) {
		for (int times = 0; times < 3; ++times) {
			for (int col = 0; col < COL; ++col) {
				for (int chr = 0; chr < 3; ++chr) {
					Type type = board[row][col].GetType();
					int rotation = board[row][col].GetRotation();

					char curChar = '#';

					switch (type)
					{
					case Type::Straight:
						curChar = Pipe::StraightShape[(rotation / 90) % 2][times][chr];
						break;
					case Type::Corner:
						curChar = Pipe::CornerShape[rotation / 90][times][chr];
						break;
					case Type::TShape:
						curChar = Pipe::TShape[rotation / 90][times][chr];
						break;
					case Type::Cross:
						curChar = Pipe::CrossShape[times][chr];
						break;
					default:
						break;
					}

					if (row == x && col == y) {
						if (isSolution[row][col]) SetColor(CurPosition_SolutionPath_Color);
						else SetColor(CurPosition_Color);
					}
					else if (isSolution[row][col]) SetColor(SolutionPath_Color);
					else SetColor(Else_Color);

					if (board[row][col].GetWatered() && curChar == 'P') SetColor(WaterPath_Color);
					cout << curChar;

					SetColor(7);
				}
				cout << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}

void Board::InjectWater(){
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			board[row][col].SetWatered(false);
		}
	}

	/* TODO: need every start point and end point*/

	int startX = 0;
	int startY = 0;

	if (!board[0][0].GetConnected()[3]) return;

	queue<pair<int, int>> q;

	q.push({ startX,startY });
	board[0][0].SetWatered(true);

	while (!q.empty()) {
		pair<int, int> current = q.front();
		q.pop();
		
		int curX = current.first;
		int curY = current.second;
		Pipe curPipe = board[curX][curY];


		for (int i = 0; i < 4; i++) {
			if (!curPipe.GetConnected()[i]) continue;
			
			int nextX = curX + directions[i].first;
			int nextY = curY + directions[i].second;

			if (nextX < 0 || nextX >= ROW) continue;
			if (nextY < 0 || nextY >= COL) continue;

			Pipe nextPipe = board[nextX][nextY];
			
			if (nextPipe.GetWatered()) continue;
			if (!nextPipe.GetConnected()[(i + 2) % 4]) continue;
			
			q.push({ nextX, nextY });
			board[nextX][nextY].SetWatered(true);
		}

	}
}

bool Board::IsGameOver() {
	return board[ROW - 1][COL - 1].GetWatered();
}