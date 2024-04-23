#ifndef _PIPE_H_
#define _PIPE_H_

#include<iostream>
#include<vector>
using namespace std;

// in 0 degree:
// -
// L
// T

enum class Type {
	Straight,
	Corner,
	TShape,
	Cross,
};

class Pipe {
private:
	// straight, L-shaped, T-shaped, Cross
	Type type;
	int rotation; // 0, 90, 180, 270
	bool isWatered;
	vector<bool> connected; // top right bottom left
public:
	Pipe();
	Type GetType() const;
	static pair<Type, int> DetectPipe(vector<vector<char>> board_vec, pair<int, int> start_pos);
	int GetRotation() const;
	bool GetWatered() const;
	void SetType(Type type);
	void SetRotation(int rotation);
	void SetWatered(bool isWatered);
	void RotatePipe();
	void SetConnected();
	vector<bool> GetConnected() const;
public:
	static vector<vector<string>> StraightShape;
	static vector<vector<string>> CornerShape;
	static vector<vector<string>> TShape;
	static vector<string> CrossShape;
};

#endif _PIPE_H_