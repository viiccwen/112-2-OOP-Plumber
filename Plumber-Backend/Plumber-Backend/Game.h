#ifndef _GAME_H_
#define _GAME_H_
#include <fstream>
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
	void StartGame();

	bool ServerChooseMode(int type, int n, int m);
	bool ServerRotatePipe(int x, int y);
	
	Board GetBoard();
};

#endif _GAME_H_