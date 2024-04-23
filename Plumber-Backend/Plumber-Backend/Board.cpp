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
}

void Board::GenerateBoard() {
	board.assign(ROW, std::vector<Pipe>(COL));
	isSolution.assign(ROW, std::vector<bool>(COL, false));

	/* TODO: need to more flexible */
	isSolution[0][0] = true;

	int start, end;
	start_pos = Position::LeftUp;
	end_pos = Position::RightDown;

	/* TODO: need to make every position */
	GenerateSolution(static_cast<int>(start_pos), static_cast<int>(end_pos));

	srand(time(NULL));
	for (int row = 0; row < ROW; ++row) {
		for (int col = 0; col < COL; ++col) {
			if (isSolution[row][col] == false) {
				Type type = static_cast<Type>(rand() % 4);
				int rotation = (rand() % 4) * 90;
				SetPipe(row, col, type, rotation);
			}
		}
	}
}

/* HOTFIX: BUG with generateSolution */
void Board::GenerateSolution(int start, int end) {
	srand(time(NULL));

	/* TODO: need to make every position */
	if (start == 0 && end == 3) {
		int x = 0, y = 0;
		board[x][y].SetType(static_cast<Type>(3));
		board[x][y].SetRotation(0);

		int dir = 0; // 0 -> right, 1-> down
		while (x != ROW - 1 || y != COL - 1) {
			if (x >= ROW - 1 || y >= COL - 1) {
				if (x == ROW - 1) isSolution[x][++y] = true;
				else if (y == COL - 1) isSolution[++x][y] = true;

				Type shape;
				do {
					shape = static_cast<Type>(rand() % 4);
				} while (shape == Type::Corner || shape == Type::Straight);

				SetPipe(x, y, shape, (rand() % 4) * 90);
			}
			else {
				if (dir == 0) isSolution[x][++y] = true;
				else isSolution[++x][y] = true;

				Type shape = static_cast<Type>(rand() % 4);
				SetPipe(x, y, shape, (rand() % 4) * 90);

				switch (shape)
				{
				case Type::Straight:
					break;
				case Type::Corner:
					dir = (dir + 1) % 2;
					break;
				case Type::TShape:
					dir = rand() % 2;
					break;
				case Type::Cross:
					dir = rand() % 2;
					break;
				default:
					break;
				}
			}
		}

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
		Pipe curPipe = board[curY][curX];


		for (int i = 0; i < 4; i++) {
			if (!curPipe.GetConnected()[i]) continue;
			
			int nextX = curX + directions[i][0];
			int nextY = curY + directions[i][1];

			if (nextX < 0 || nextX >= COL) continue;
			if (nextY < 0 || nextY >= ROW) continue;

			Pipe nextPipe = board[nextY][nextX];
			
			if (nextPipe.GetWatered()) continue;
			if (!nextPipe.GetConnected()[(i + 2) % 4]) continue;
			
			q.push({ nextX, nextY });
			board[nextY][nextX].SetWatered(true);
		}

	}
}

bool Board::IsGameOver() {
	return board[ROW - 1][COL - 1].GetWatered() && board[ROW - 1][COL - 1].GetConnected()[1];
}