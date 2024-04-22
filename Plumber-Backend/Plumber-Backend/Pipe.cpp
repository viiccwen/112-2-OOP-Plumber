#pragma once
#include "Pipe.h"

Pipe::Pipe() {
	isWatered = false;
	rotation = 0;
	type = Type::Cross;
	connected = { false,false,false,false };
}

void Pipe::SetWatered(bool isWatered) {
	this->isWatered = isWatered;
}

void Pipe::SetType(Type type) {
	this->type = type;
	SetConnected();
}

void Pipe::SetRotation(int rotation) {
	this->rotation = rotation;
	SetConnected();
}

Type Pipe::GetType() const {
	return type;
}

int Pipe::GetRotation() const {
	return rotation;
}

bool Pipe::GetWatered() const {
	return isWatered;
}

void Pipe::SetConnected(){
	switch (type)
	{
	case Type::Straight:
		connected[rotation / 90] = false;
		connected[(rotation / 90 + 1) % 4] = true;
		connected[(rotation / 90 + 2) % 4] = false;
		connected[(rotation / 90 + 3) % 4] = true;
		break;
	case Type::Corner:
		connected[rotation / 90] = true;
		connected[(rotation / 90 + 1) % 4] = true;
		connected[(rotation / 90 + 2) % 4] = false;
		connected[(rotation / 90 + 3) % 4] = false;
		break;
	case Type::TShape:
		connected = { true,true,true,true };
		connected[rotation / 90] = false;
		break;
	case Type::Cross:
		connected = { true,true,true,true };
		break;
	}
}

vector<bool> Pipe::GetConnected() const {
	return connected;
}

void Pipe::RotatePipe() {
	rotation = (rotation + 90) % 360;
	SetConnected();
}