#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>  // For file streams
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
	void handle_options(http_request request);
	void set_cors_headers(http_response& response);
	void serve_static_file(const utility::string_t& file_path, http_request& request);
	utility::string_t get_content_type(const utility::string_t& path);
public:
	HttpServer(utility::string_t url);
	void start();
	void stop();
};

#endif _HTTPSERVER_H_