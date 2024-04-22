#ifndef _PIPE_H_
#define _PIPE_H_

#include<iostream>
#include <vector>
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
	int GetRotation() const;
	bool GetWatered() const;
	void SetType(Type type);
	void SetRotation(int rotation);
	void SetWatered(bool isWatered);
	void RotatePipe();

	void SetConnected();
	vector<bool> GetConnected() const;
};

#endif _PIPE_H_