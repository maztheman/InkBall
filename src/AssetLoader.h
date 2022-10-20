#pragma once

#include <cstdint>
#include <unordered_map>

typedef struct _TTF_Font TTF_Font;

namespace Where1::SDL_Utilities
{

class AssetLoader
{
public:
    AssetLoader() = default;
    ~AssetLoader();

    void load();
    void unload();

    TTF_Font* getFontForSize(int size);

private:
    std::unordered_map<int, TTF_Font*> m_Fonts;
};


//return singleton assert manager
inline AssetLoader& Assets()
{
    static AssetLoader instance;
    return instance;
}


}