#pragma once
#include "HttpServer.h"


void HttpServer::handle_get(http_request request) {
	ucout << "GET request received" << std::endl;

	if (request.relative_uri().path() == U("/board")) {
		json::value response_data;
		response_data[U("board")] = json::value::string(U("Board state here"));
		request.reply(status_codes::OK, response_data);
	}
	else {
		request.reply(status_codes::NotFound, U("Route not found"));
	}
}

void HttpServer::handle_post(http_request request) {
	ucout << "POST request received" << std::endl;

	auto path = request.relative_uri().path();
	if (path == U("/newGame")) {
		request.extract_json().then([=](json::value val) {
			ucout << "Starting new game with mode: " << val[U("mode")].as_integer() << std::endl;

			game = Game();

			int type = val[U("mode")].as_integer();
			int n = val[U("n")].as_integer();
			int m = val[U("m")].as_integer();

			bool status = game.ServerChooseMode(type,n,m);

			json::value response_data;
			response_data[U("status")] = json::value::boolean(status);
			request.reply(status_codes::OK, response_data);
			});
	}
	else if (path == U("/rotate")) {
		request.extract_json().then([=](json::value val) {
			ucout << "Rotating pipe at: (" << val[U("x")].as_integer() << ", " << val[U("y")].as_integer() << ")" << std::endl;
			
			int x = val[U("x")].as_integer();
			int y = val[U("y")].as_integer();

			bool status = game.ServerRotatePipe(x, y);

			json::value response_data;
			response_data[U("status")] = json::value::boolean(status);
			request.reply(status_codes::OK, response_data);
			});
	}
	else {
		request.reply(status_codes::NotFound, U("Route not found"));
	}
}

HttpServer::HttpServer(utility::string_t url) : listener(url) {
	listener.support(methods::GET, std::bind(&HttpServer::handle_get, this, std::placeholders::_1));
	listener.support(methods::POST, std::bind(&HttpServer::handle_post, this, std::placeholders::_1));

	game = Game();
}

void HttpServer::start() {
	try {
		listener.open().wait();
		ucout << "HTTP server started at: " << listener.uri().to_string() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
}

void HttpServer::stop() {
	listener.close().wait();
	ucout << "HTTP server stopped." << std::endl;
}