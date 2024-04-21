#pragma once
#include "Pipe.h"

void Pipe::SetType(Type CurType) {
	type = CurType;
}

void Pipe::SetRotation(int CurRotation) {
	rotation = CurRotation;
}

Type Pipe::GetType() const {
	return type;
}

int Pipe::GetRotation() const {
	return rotation;
}

void Pipe::RotatePipe() {
	if (type == Type::Cross) {
		return;
	}
	rotation = (rotation + 90) % 360;
	return;
}