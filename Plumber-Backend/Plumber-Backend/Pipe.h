#ifndef _PIPE_H_
#define _PIPE_H_

#include<iostream>

class Pipe {
private:
	// straight, L-shaped, T-shaped, ¤Q-shaped
	enum Type {
		I = 1,
		L,
		T,
		X,
	};
public:
	Pipe();
	void RotatePipe(std::pair<int, int>& pos);
};

#endif _PIPE_H_