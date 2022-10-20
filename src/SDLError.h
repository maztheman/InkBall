
#ifndef INKBALL_SDLERROR_H
#define INKBALL_SDLERROR_H

#include <SDL2/SDL.h>

#include <exception>
#include <string>
#include <cstring>

namespace Where1::SDL_Utilities {
	class SDLError : public std::exception {
	public:
		explicit SDLError(const char *error_message) {
			std::string tmp = error_message;
			tmp += ' ';
			tmp += SDL_GetError(); // If this was all on one line it would do pointer addition because C++

			message = std::move(tmp);
		}

		explicit SDLError(std::string error_message)
		{
			error_message += " ";
			error_message += SDL_GetError();
			message = std::move(error_message);
		}

		SDLError()
				: SDLError("") {
		}

		std::string message;

		const char *what() const noexcept override {
			return message.c_str();
		}
	};
}

#endif //INKBALL_SDLERROR_H
