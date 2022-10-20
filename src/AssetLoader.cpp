#include "AssetLoader.h"

#include "Constants.h"
#include "SDLError.h"

#include <SDL2/SDL_ttf.h>
#include <fmt/format.h>
#include <string_view>

using namespace std::string_view_literals;

namespace Where1::SDL_Utilities
{

static constexpr auto FONT_SIZES = {
    InkBall::Constants::LEVEL_FONT_SIZE,
    InkBall::Constants::MENU_LEVEL_FONT_SIZE,
    InkBall::Constants::PLAYABLE_LEVEL_FONT_SIZE,
    InkBall::Constants::SUBTEXT_FONT_SIZE,
    InkBall::Constants::SURTEXT_FONT_SIZE
};

static constexpr auto FONT = "assets/LiberationSans-Regular.ttf"sv;

AssetLoader::~AssetLoader()
{
    
}


void AssetLoader::load()
{
    for(auto size : FONT_SIZES)
    {
        TTF_Font *sans = TTF_OpenFont(FONT.data(), size);
        if (sans == nullptr)
        {
            std::string err = fmt::format("Could not open font: {}", FONT);

            throw SDL_Utilities::SDLError(err);
        }
        m_Fonts.emplace(size, sans);
    }
}

void AssetLoader::unload()
{
    for(auto& font : m_Fonts)
    {
        TTF_CloseFont(font.second);
    }
    m_Fonts.clear();
}


TTF_Font* AssetLoader::getFontForSize(int size)
{
    if (auto it = m_Fonts.find(size); it != m_Fonts.end())
    {
        return it->second;
    }

    TTF_Font *sans = TTF_OpenFont(FONT.data(), size);
    m_Fonts.emplace(size, sans);
    return sans;
}

}