#include "Game.h"
#include<iostream>
#include "HttpServer.h"

using namespace std;

int main() {

//	          cat is great.
//  	      ／＞-----フ
//           |  。   。 l
//   　　　／     ꒳   ノ
//  　 　 /　　　 　 |
//  　　 /　 、　　 ﾉ 
//   　 │　　|　|　| 
//  ／￣|　　 |　|　| 
//  | (￣ヽ＿、)_)
//  ＼二つ​

	/*Game game;
	game.ChooseMode();

	return 0;*/
    HttpServer server(U("http://localhost:8080"));
    server.start();

    std::string line;
    std::getline(std::cin, line); // Wait for user input to stop server

    server.stop();
    return 0;
}