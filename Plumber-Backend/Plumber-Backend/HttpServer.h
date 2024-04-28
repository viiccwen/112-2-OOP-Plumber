#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "Game.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class HttpServer {
private:
	Game game;

	http_listener listener;
	void handle_get(http_request request);
	void handle_post(http_request request);
public:
	HttpServer(utility::string_t url);
	void start();
	void stop();
};

#endif _HTTPSERVER_H_