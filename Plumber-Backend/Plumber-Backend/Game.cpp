#pragma once
#include "Game.h"
using namespace std;

void Game::ChooseMode() {
	int type = 1;
	int min = 3;
	int max = 20;	// can edit
	int N, M;

	while (true) {
		cout << "Choose Mode: (1) type N*M (2) random N*M (3) read file : ";
		cin >> type;

		if (type == 1) {
			cout << "Give the N (N>=3) : ";
			cin >> N;
			cout << "Give the M (M>=3) : ";
			cin >> M;

			if (N < 3 || M < 3) {
				cout << "There is wrong with your boundary!\n";
			}
			else {
				board.SetBoardSize(N, M);
				board.GenerateBoard();
				break;
			}
		}
		else if (type == 2) {
			srand(time(NULL));
			N = rand() % (max - min + 1) + min;
			M = rand() % (max - min + 1) + min;
			board.SetBoardSize(N, M);
			board.GenerateBoard();
			break;
		}
		else if (type == 3) {
			ifstream in("board.txt");

			in >> N >> M;
			if (N < 3 || M < 3) {
				cout << "There is wrong with your boundary!\n";
			}
			else {
				vector<vector<char>> board_vec(N * 3, vector<char>(M * 3));
				for (int row = 0; row < N * 3; ++row) {
					for (int col = 0; col < M * 3; ++col) {
						in >> board_vec[row][col];
					}
				}

				board.SetBoardSize(N, M);
				board.SetupBoard(board_vec);
				break;
			}

			in.close();
		}
		else {
			cout << "There is wrong with the mode you choosed!\n";
		}
	}
	StartGame();
}

void Game::StartGame() {
	bool FirstTime = false;
	while (1) {
		if (FirstTime == false) {
			FirstTime = true;
			board.InjectWater();
			pair<int, int> start_pos = board.GetStartPosition();
			player.pos.x = start_pos.first;
			player.pos.y = start_pos.second;
			board.PrintBoard(player.pos.x, player.pos.y);
		}

		if (player.PressButton()) {
			int press = player.GetInput();
			if (press != 224) {

				if (player.isEsc(press)) {
					break;
				}

				if (player.isSpace(press)) {
					board.RotatePipe(player.pos.x, player.pos.y);
				}

				if (player.isUp(press)) {
					player.moveUp();
				}

				if (player.isDown(press)) {
					player.moveDown();
				}

				if (player.isLeft(press)) {
					player.moveLeft();
				}

				if (player.isRight(press)) {
					player.moveRight();
				}

				board.InjectWater();
				board.PrintBoard(player.pos.x, player.pos.y);
			}
		}

		if (board.IsGameOver()) {
			cout << "Stage Clear!\n";
			break;
		}
	}
}

Board Game::GetBoard() {
	return board;
}


bool Game::ServerChooseMode(int type, int n = 3, int m = 3) {
	int min = 3;
	int max = 20;
	int N, M;

	if (type == 1) {
		N = n;
		M = m;

		if (N < 3 || M < 3) {
			return false;
		}
		else {
			board.SetBoardSize(N, M);
			board.GenerateBoard();
			board.InjectWater();
		}
	}
	else if (type == 2) {
		srand(time(NULL));
		N = rand() % (max - min + 1) + min;
		M = rand() % (max - min + 1) + min;
		board.SetBoardSize(N, M);
		board.GenerateBoard();
		board.InjectWater();
	}
	else if (type == 3) {
		ifstream in("board.txt");

		in >> N >> M;
		if (N < 3 || M < 3) {
			return false;
		}
		else {
			vector<vector<char>> board_vec(N * 3, vector<char>(M * 3));
			for (int row = 0; row < N * 3; ++row) {
				for (int col = 0; col < M * 3; ++col) {
					in >> board_vec[row][col];
				}
			}
			

			board.SetBoardSize(N, M);
			board.SetupBoard(board_vec);
			board.InjectWater();
		}

		in.close();
	}
	else {
		return false;
	}

	return true;
}

bool Game::ServerRotatePipe(int x, int y) {
	if (0 > x || x >= board.ROW) return false;
	if (0 > y || y >= board.COL) return false;

	board.RotatePipe(x, y);
	board.InjectWater();
	board.PrintBoard(x, y);
	return true;
}

