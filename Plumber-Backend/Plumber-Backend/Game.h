#ifndef _GAME_H_
#define _GAME_H_

class Game {
private:

public:
	Game();
	void StartGame();
	void CheckWin();
	void UpdateWater();
	bool GenerateSolutionPath();
};

#endif _GAME_H_