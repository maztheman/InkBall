
#include "TextScreenLevel.h"
#include "Drawing.h"
//#include "Game.h"
#include "Constants.h"

#include <string_view>

using namespace std::string_view_literals;

namespace Where1::InkBall {
	void TextScreenLevel::update(double timestep) {
		// nop
	}

	void TextScreenLevel::draw(SDL_Renderer *renderer) 
	{
		static constexpr auto PADDING = Constants::LEVEL_PADDING;

		SDL_SetRenderDrawColor(renderer, 230, 230, 230, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		

		static constexpr auto subtext = "Press ESC for menu"sv;

		std::pair<int, int> surtext_size = SDL_Utilities::GetStringSize(surtext, Constants::SURTEXT_FONT_SIZE);

		int x = Constants::GAME_WIDTH / 2 - surtext_size.first / 2;
		int y = (Constants::GAME_HEIGHT - Constants::GAME_TOP_BAR_HEIGHT) / 2 - surtext_size.second / 2;

		SDL_Rect rect{
				.x = x - PADDING,
				.y = y - PADDING,
				.w = surtext_size.first + 2 * PADDING,
				.h = surtext_size.second + 2 * PADDING,
		};

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

		SDL_RenderFillRect(renderer, &rect);

		SDL_Rect subtext_rect{
				.x = rect.x,
				.y = rect.y + rect.h,
				.w = rect.w,
				.h = SDL_Utilities::GetStringSize(subtext, Constants::SUBTEXT_FONT_SIZE).second + 2 * PADDING,
		};

		SDL_RenderFillRect(renderer, &subtext_rect);

		SDL_Utilities::WriteText(renderer, {(double) x, (double) y}, surtext, Constants::SURTEXT_FONT_SIZE, 0, 0, 0);
		SDL_Utilities::WriteText(renderer, {(double) x, (double) subtext_rect.y + PADDING}, subtext, Constants::SUBTEXT_FONT_SIZE, 0, 0, 0);
	}

	TextScreenLevel::TextScreenLevel(std::string surtext)
			: surtext(surtext) {

	}

	bool TextScreenLevel::is_menu() {
		return false;
	}
}