#ifndef _PIPE_H_
#define _PIPE_H_

#include<iostream>

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
public:
	Pipe() {};
	Type GetType() const;
	int GetRotation() const;
	void SetType(Type CurType);
	void SetRotation(int CurRotation);
	void RotatePipe();
};

#endif _PIPE_H_