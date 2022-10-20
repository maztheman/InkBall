#pragma once

#include <cstdint>

namespace Where1::InkBall::Constants
{

    inline constexpr auto GAME_TOP_BAR_HEIGHT = 30;
    inline constexpr auto GAME_HEIGHT = 608 + GAME_TOP_BAR_HEIGHT;
	inline constexpr auto GAME_WIDTH = 480;

    inline constexpr auto LEVEL_PADDING = 10;

    //Font Sizes

    inline constexpr auto LEVEL_FONT_SIZE = 30;
    inline constexpr auto PLAYABLE_LEVEL_FONT_SIZE = GAME_TOP_BAR_HEIGHT - 4;
    inline constexpr auto SURTEXT_FONT_SIZE = 40;
	inline constexpr auto SUBTEXT_FONT_SIZE = 20;
    inline constexpr auto MENU_LEVEL_FONT_SIZE = 30;


}