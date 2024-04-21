#pragma once
#include "Player.h"

bool Player::PressButton() const {
	return _kbhit();
}

int Player::GetInput() const {
	return static_cast<int>(_getch());
}

bool Player::isEsc(const int& press) const {
	return press == 27;
}

bool Player::isSpace(const int& press) const {
	return press == 32;
}

bool Player::isUp(const int& press) const {
	return press == 72;
}

bool Player::isDown(const int& press) const {
	return press == 80;
}

bool Player::isLeft(const int& press) const {
	return press == 75;
}

bool Player::isRight(const int& press) const {
	return press == 77;
}

void Player::moveUp() {
	if (pos.x > 0) pos.x--;
}

void Player::moveDown() {
	if (pos.x < Board::ROW - 1) pos.x++;
}

void Player::moveLeft() {
	if (pos.y > 0) pos.y--;
}

void Player::moveRight() {
	if (pos.y < Board::COL - 1) pos.y++;
}