#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<iostream>

class Player {
private:
	std::pair<int, int> pos; // player's current position
public:
	Player() {};
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif _PLAYER_H_