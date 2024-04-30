#pragma once
#include "HttpServer.h"

void HttpServer::handle_get(http_request request) {
	request.headers().add(U("Access-Control-Allow-Origin"), U("*"));

	auto path = request.relative_uri().path();
	utility::string_t file_path;

	ucout << "GET " << path << std::endl;

	if (path == U("/board")) {
		json::value response_data;

		Board board = game.GetBoard();
		json::value json_board = json::value::array(board.ROW);

		pair<int, int> startPosition = board.GetStartPosition();
		pair<int, int> endPosition = board.GetEndPosition();

		for (int i = 0; i < board.ROW; i++) {
			json::value json_row = json::value::array(board.COL);
			for (int j = 0; j < board.COL; j++) {
				Pipe pipe = board.GetPipe(i, j);

				json::value json_pipe = json::value::object();
				json_pipe[U("isWatered")] = json::value::boolean(pipe.GetWatered());
				json_pipe[U("rotation")] = json::value::number(pipe.GetRotation());
				json_pipe[U("isSolution")] = json::value::boolean(board.GetIsSolution(i, j));

				json_pipe[U("isStartPosition")] = startPosition.first == i && startPosition.second == j;
				json_pipe[U("isEndPosition")] = endPosition.first == i && endPosition.second == j;

				if (pipe.GetType() == Type::Cross)
					json_pipe[U("type")] = json::value::string(U("cross"));
				else if (pipe.GetType() == Type::Straight)
					json_pipe[U("type")] = json::value::string(U("straight"));
				else if (pipe.GetType() == Type::Corner)
					json_pipe[U("type")] = json::value::string(U("elbow"));
				else if (pipe.GetType() == Type::TShape)
					json_pipe[U("type")] = json::value::string(U("t"));

				json_row[j] = json_pipe;
			}
			json_board[i] = json_row;
 		}

		response_data[U("board")] = json_board;
		response_data[U("isGameOver")] = board.IsGameOver();
		response_data[U("status")] = json::value::boolean(true);

		auto response = http_response(status_codes::OK);
		response.set_body(response_data);
		set_cors_headers(response);
		request.reply(response);
	}
	else if (path.empty() || path == U("/") || path == U("")) {
		file_path = U("./public/index.html");  // Default to serving index.html
	}
	else {
		file_path = U("./public") + path;
	}

	serve_static_file(file_path, request);
}

void HttpServer::handle_post(http_request request) {
	request.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	auto path = request.relative_uri().path();

	ucout << "POST " << path << std::endl;
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
			
			auto response = http_response(status_codes::OK);
			response.set_body(response_data);
			set_cors_headers(response);
			request.reply(response);
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

			auto response = http_response(status_codes::OK);
			response.set_body(response_data);
			set_cors_headers(response);
			request.reply(response);
			});
	}
	else {
		json::value response_data;
		response_data[U("status")] = json::value::boolean(false);
		request.reply(status_codes::NotFound, response_data);
	}
}

void HttpServer::serve_static_file(const utility::string_t& file_path, http_request& request) {
	concurrency::streams::istream fileStream;
	try {
		fileStream = concurrency::streams::fstream::open_istream(file_path, std::ios::in).get();
		auto content_type = get_content_type(file_path);
		request.reply(status_codes::OK, fileStream, content_type).then([fileStream](pplx::task<void> t) {
			try {
				t.get();
				fileStream.close().get(); // Close the stream
			}
			catch (...) {
				
			}
			});
	}
	catch (const std::exception& e) {
		ucout << "Failed to open file: " << file_path << ':' << e.what() << std::endl;
		request.reply(status_codes::NotFound, U("File not found"));
	}
}

utility::string_t HttpServer::get_content_type(const utility::string_t& path) {
	auto ext = path.substr(path.find_last_of(U('.')) + 1);
	if (ext == U("html")) return U("text/html");
	if (ext == U("css")) return U("text/css");
	if (ext == U("js")) return U("application/javascript");
	if (ext == U("png")) return U("image/png");
	if (ext == U("jpg") || ext == U("jpeg")) return U("image/jpeg");
	if (ext == U("gif")) return U("image/gif");
	return U("application/octet-stream"); // Default MIME type
}

void HttpServer::handle_options(http_request request) {
	ucout << "OPTIONS request received\n";

	http_response response(status_codes::OK);
	response.headers().add(U("Allow"), U("GET, POST, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
	request.reply(response);
}

void HttpServer::set_cors_headers(http_response& response) {
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
}

HttpServer::HttpServer(utility::string_t url) : listener(url) {
	listener.support(methods::GET, std::bind(&HttpServer::handle_get, this, std::placeholders::_1));
	listener.support(methods::POST, std::bind(&HttpServer::handle_post, this, std::placeholders::_1));
	listener.support(methods::OPTIONS, std::bind(&HttpServer::handle_options, this, std::placeholders::_1));

	game = Game();
}

void HttpServer::start() {
	try {
		listener.open().wait();
		ucout << "Game URL: " << listener.uri().to_string() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
}

void HttpServer::stop() {
	listener.close().wait();
	ucout << "HTTP server stopped." << std::endl;
}