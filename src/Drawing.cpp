
#include "Drawing.h"

#include "AssetLoader.h"

#include <SDL2/SDL_ttf.h>

namespace Where1::SDL_Utilities {
	int CircleError(int x, int y, int r) {
		return r * r - x * x - y * y;
	}

	void DrawCircle(SDL_Renderer *renderer, const int centre_x, const int centre_y, const int r) {
		const int r_squared = r * r;
		int y = r;
		int x = -1;

		do {
			x++;
			while (y * y + x * x >= r_squared) {
				y--;
			}


			// Above we calculate one point in one octant of the circle, now we exploit its symmetry
			SDL_Rect rects[]{
					{
							.x = centre_x - x,
							.y = centre_y - y,
							.w = 2 * x,
							.h = 2 * y
					},
					{
							.x = centre_x - y,
							.y = centre_y - x,
							.w = 2 * y,
							.h = 2 * x
					}
			};

			SDL_RenderFillRects(renderer, rects, 2);
		} while (y >= x);
	}

	void DrawLine(SDL_Renderer *renderer, Geometry::Line<double> line, int thickness) {
		DrawLine(renderer, line.p1, line.p2, thickness);
	}

	void DrawLine(SDL_Renderer *renderer, vec2d p1, vec2d p2, int thickness) {
		int medium = thickness / 2;

		vec2d displacement = (p2 - p1);
		vec2d normal_vector = displacement.get_normal_vector().get_normalized();

		for(int i = -medium; i <= medium; i++){
			vec2d pt1 = p1 + (double)i * normal_vector;
			vec2d pt2 = p2 + (double)i * normal_vector;

			SDL_RenderDrawLine(renderer, pt1.x, pt1.y, pt2.x, pt2.y);
		}
	}

	void DrawLines(SDL_Renderer *renderer, const std::vector<vec2d>& points) 
	{
		//could use some sort of allocator that remembers every frame
		std::vector<SDL_Point> pointArray(points.size());

		for(int i = 0; i < points.size(); i++)
		{
			pointArray[i].x = (int)points[i].x;
			pointArray[i].y = (int)points[i].y;
		}

		SDL_RenderDrawLines(renderer, pointArray.data(), points.size());
	}

	void WriteText(SDL_Renderer *renderer, vec2d position, std::string_view text, int size, uint8_t red, uint8_t blue, uint8_t green) 
	{
		TTF_Font *sans = Assets().getFontForSize(size);

		SDL_Color color = {red, green, blue};

		SDL_Surface *surface = TTF_RenderText_Solid(sans, text.data(), color);

		sans = nullptr;

		if(surface == nullptr){
			throw SDLError("Could not write text to surface:");
		}

		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_Rect rect {
				.x = (int)position.x,
				.y = (int)position.y,
				.w = surface->w,
				.h = surface->h
		};

		SDL_FreeSurface(surface);
		surface = nullptr;

		if(texture == nullptr){
			throw SDLError("Could not create texture");
		}

		SDL_RenderCopy(renderer, texture, nullptr, &rect);

		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	std::pair<int, int> GetStringSize(std::string_view text, int size) 
	{
		TTF_Font *sans = Assets().getFontForSize(size);

		int w, h;

		TTF_SizeText(sans, text.data(), &w, &h);

		return std::make_pair(w, h);
	}
}
