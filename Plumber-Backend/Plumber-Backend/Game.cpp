#pragma once
#include "Game.h"
using namespace std;

void Game::ChooseMode() {
	int type = 1;
	int min = 3;
	int max = 10;	// can edit
	int N, M;

	cout << "Choose Mode: (1) type N*M (2) random N*M : ";
	cin >> type;

	if (type == 1) {
		cout << "Give the N (N>=3) : ";
		cin >> N;
		cout << "Give the M (M>=3) : ";
		cin >> M;

		if (N < 3 || M < 3) {
			cout << "There is wrong with your boundary!\n";
			return;
		}

		StartGame(N, M);
	}
	else if (type == 2) {
		srand(time(NULL));
		N = rand() % (max - min + 1) + min;
		M = rand() % (max - min + 1) + min;

		StartGame(N, M);
	}
	else {
		cout << "There is wrong with the mode you choosed!\n";
	}
}

void Game::Initialization(int& row, int& col) {
	// set size, pipe shape.
	board.SetBoardSize(row, col);
	board.GenerateBoard();

}

void Game::StartGame(int& row, int& col) {
	Initialization(row, col);

	bool FirstTime= false;
	while (1) {
		if (FirstTime == false) {
			FirstTime = true;
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