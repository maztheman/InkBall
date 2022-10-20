
#ifndef INKBALL_DRAWING_H
#define INKBALL_DRAWING_H

#include "SDLError.h"
#include "Vector2.h"
#include "Line.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <vector>
#include <string_view>

namespace Where1::SDL_Utilities{
	void DrawCircle(SDL_Renderer *renderer, int centre_x, int y, int r);
	void DrawLine(SDL_Renderer *renderer, vec2d p1, vec2d p2, int thickness);
	void DrawLine(SDL_Renderer *renderer, Geometry::Line<double> line, int thickness);
	void DrawLines(SDL_Renderer *renderer, const std::vector<vec2d>& points);
	void WriteText(SDL_Renderer *renderer, vec2d position, std::string_view text, int size, uint8_t red, uint8_t blue, uint8_t green);
	std::pair<int, int> GetStringSize(std::string_view text, int size);
}

#endif //INKBALL_DRAWING_H
