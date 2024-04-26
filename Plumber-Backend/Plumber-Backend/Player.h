#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Board.h"
#include<iostream>
#include <conio.h>
#include <Windows.h>

typedef struct {
	int x;
	int y;
} POS;

class Player {
private:

public:
	POS pos; // player's current position

	bool PressButton() const;
	int GetInput() const;

	bool isEsc(const int& press) const;
	bool isSpace(const int& press) const;
	bool isUp(const int& press) const;
	bool isDown(const int& press) const;
	bool isLeft(const int& press) const;
	bool isRight(const int& press) const;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif _PLAYER_H_