#pragma once
#include "Board.h"

#include<vector>
#include<iostream>
#include<Windows.h>
using namespace std;

void Board::SetBoardSize(int& row, int& col) {
	ROW = row;
	COL = col;
}

void Board::SetPipe(int x, int y, Type type, int rotation) {
	board[x][y].SetType(type);
	board[x][y].SetRotation(rotation);
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

void Board::GenerateSolution(int start, int end) {
	srand(time(NULL));

	/* TODO: need to make every position */
	if (start == 0 && end == 3) {
		int x = 0, y = 0;
		board[x][y].SetType(static_cast<Type>(3));
		board[x][y].SetRotation(0);

		int dir = 0; // 0 -> right, 1-> down
		while (x != ROW - 1 || y != COL - 1) {
			if (x == ROW - 1 || y == COL - 1) {
				if(x == ROW - 1) isSolution[x][++y] = true;
				else if(y == COL - 1) isSolution[++x][y] = true;

				Type shape;
				do {
					shape = static_cast<Type>(rand() % 4);
				} while (shape == Type::Corner);

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

void Board::PrintBoard() const {
	for (int row = 0; row < ROW; ++row) {
		for (int times = 0; times < 3; ++times) {
			for (int col = 0; col < COL; ++col) {
				SetColor((isSolution[row][col]) ? 12 : 7); // color table is on notion.

				Type type = board[row][col].GetType();
				int rotation = board[row][col].GetRotation();

				switch (type)
				{
				case Type::Straight:
					cout << StraightShape[(rotation / 90) % 2][times];
					break;
				case Type::Corner:
					cout << CornerShape[rotation / 90][times];
					break;
				case Type::TShape:
					cout << TShape[rotation / 90][times];
					break;
				case Type::Cross:
					cout << CrossShape[times];
					break;
				default:
					break;
				}
			
				cout << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
	}
}