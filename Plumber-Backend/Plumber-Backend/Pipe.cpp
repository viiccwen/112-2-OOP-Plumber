#pragma once
#include "Pipe.h"

vector<vector<string>> Pipe::StraightShape = {
	{	"###",
		"PPP",
		"###" },
	{
		"#P#",
		"#P#",
		"#P#"}
};

vector<vector<string>> Pipe::CornerShape = {
		{	"#P#",
			"#PP",
			"###"},
		{
			"###",
			"#PP",
			"#P#"},
		{
			"###",
			"PP#",
			"#P#"},
		{
			"#P#",
			"PP#",
			"###"},
};

vector<vector<string>> Pipe::TShape = {
	{	"###",
		"PPP",
		"#P#"},
	{
		"#P#",
		"PP#",
		"#P#"},
	{
		"#P#",
		"PPP",
		"###"},
	{
		"#P#",
		"#PP",
		"#P#"},
};

vector<string> Pipe::CrossShape = {
	"#P#",
	"PPP",
	"#P#"
};


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

void Pipe::SetConnected() {
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

pair<Type, int> Pipe::DetectPipe(vector<vector<char>> board_vec, pair<int, int> start_pos) {
	vector<string> cur_shape(3);
	int cnt = 0;

	// get current shape.
	for (int r = start_pos.first * 3; r < start_pos.first * 3 + 3; ++r) {
		string cur_str = "";
		for (int c = start_pos.second * 3; c < start_pos.second * 3 + 3; ++c) {
			cur_str += board_vec[r][c];
		}
		cur_shape[r - start_pos.first * 3] = cur_str;
	}

	// detect for straight shape.
	for (int i = 0; i < Pipe::StraightShape.size(); ++i) {
		int cnt = 0;
		for (int j = 0; j < Pipe::StraightShape[i].size(); ++j) {
			if (cur_shape[j] == Pipe::StraightShape[i][j]) {
				cnt++;
			}
			else {
				break;
			}

			if(cnt == 3) return { Type::Straight, i * 90 };
		}
	}

	// detect for Corner shape.
	for (int i = 0; i < Pipe::CornerShape.size(); ++i) {
		cnt = 0;
		for (int j = 0; j < Pipe::CornerShape[i].size(); ++j) {

			if (cur_shape[j] == Pipe::CornerShape[i][j]) {
				cnt++;
			}
			else {
				break;
			}

			if (cnt == 3) return { Type::Corner, i * 90 };
		}
	}

	// detect for TShape shape.
	for (int i = 0; i < Pipe::TShape.size(); ++i) {
		cnt = 0;
		for (int j = 0; j < Pipe::TShape[i].size(); ++j) {

			if (cur_shape[j] == Pipe::TShape[i][j]) {
				cnt++;
			}
			else {
				break;
			}

			if(cnt == 3) return { Type::TShape, i * 90 };
		}
	}

	// detect for Cross shape.
	cnt = 0;
	for (int i = 0; i < Pipe::CrossShape.size(); ++i) {
		if (cur_shape[i] == Pipe::CrossShape[i]) {
			cnt++;
		}
		else {
			break;
		}

		if(cnt == 3) return { Type::Cross, 0 };
	}

	return { Type::Cross, 0 };
}