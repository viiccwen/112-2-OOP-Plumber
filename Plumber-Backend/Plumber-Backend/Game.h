#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"
#include "Player.h"

class Game {
private:
	enum Type {
		Specific = 1,
		Random,
	};

	Board board;
	Player player;
public:
	Game() {};
	void ChooseMode();

	// parameters: <int>board row, <int>board col
	void StartGame(int& row, int& col);
	void Initialization(int& row, int& col);
	void CheckWin();
	void UpdateWater();
};

#endif _GAME_H_