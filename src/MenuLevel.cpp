
#include "MenuLevel.h"
#include "Constants.h"

namespace Where1::InkBall {
	static constexpr auto PADDING = Constants::LEVEL_PADDING;

	SDL_Rect MenuLevel::get_bounding_rect(MenuItem &item, int index) 
	{

		std::pair<int, int> text_size = SDL_Utilities::GetStringSize(item.text, Constants::MENU_LEVEL_FONT_SIZE);
		int x = Constants::GAME_WIDTH / 2 - text_size.first / 2;
		int y = (Constants::GAME_HEIGHT - Constants::GAME_TOP_BAR_HEIGHT) / 2 + (index - 1) * (text_size.second + 2 * PADDING);

		return SDL_Rect{
				.x = x - PADDING,
				.y = y - PADDING,
				.w = text_size.first + 2 * PADDING,
				.h = text_size.second + 2 * PADDING,
		};
	}

	void MenuLevel::draw(SDL_Renderer *renderer) {
		SDL_SetRenderDrawColor(renderer, 230, 230, 230, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		int i = 0;
		for (auto &item : get_menu_items()) {
			SDL_Rect rect = get_bounding_rect(item, i);

			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

			SDL_RenderFillRect(renderer, &rect);

			SDL_Utilities::WriteText(renderer, {(double) rect.x + PADDING, (double) rect.y + PADDING}, item.text, Constants::MENU_LEVEL_FONT_SIZE, 0, 0, 0);

			i++;
		}
	}

	void MenuLevel::update(double timestep) {
		// nop
	}

	void MenuLevel::handle_mouse_button(SDL_MouseButtonEvent &e) {
		if (e.type == SDL_MOUSEBUTTONUP && e.button & SDL_BUTTON_LEFT) {
			for (int i = 0; auto &item : get_menu_items()) {
				SDL_Rect rect = get_bounding_rect(item, i);

				if (e.x > rect.x && e.x < rect.x + rect.w && e.y > rect.y && e.y < rect.y + rect.h) {
					item.on_click(get_game());
					break;
				}

				i++;
			}
		}
	}

	bool MenuLevel::is_menu() {
		return true;
	}
}
