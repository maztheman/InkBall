
#include <iostream>
#include "Game.h"
#include "LevelDeserialization.h"
#include "SerializedLevel.h"
#include "MenuLevel.h"
#include "EscapeMenu.h"
#include "TextScreenLevel.h"
#include "LevelSelectMenu.h"
#include "Constants.h"

#include "AssetLoader.h"

#include <SDL2/SDL_ttf.h>

namespace Where1::InkBall 
{
	void Game::play() 
	{
		unsigned long long now = SDL_GetPerformanceCounter();
		unsigned long long last = now;

		SDL_Utilities::Assets().load();

		while (!should_quit) 
		{
			SDL_Event event;
			while (!should_quit && SDL_PollEvent(&event)) 
			{
				handle_event(event);
			}

			last = now;
			now = SDL_GetPerformanceCounter();
			double delta_t = (now - last) / (double) SDL_GetPerformanceFrequency();

			const double max_timestep = 1 / 60.0;

			while (delta_t > 1 / 60.0) 
			{
				delta_t -= max_timestep;
				level_stack.top()->update(max_timestep);
			}

			if (delta_t > 0) 
			{
				level_stack.top()->update(delta_t);
			}

			level_stack.top()->draw(renderer.get());

			SDL_RenderPresent(renderer.get());
		}

		SDL_Utilities::Assets().unload();
	}

	void Game::quit() 
	{
		should_quit = true;
	}

	void Game::handle_event(SDL_Event &event) 
	{
		switch (event.type) {
			case SDL_QUIT:
				quit();
				break;
			case SDL_MOUSEMOTION:
				level_stack.top()->handle_mouse_move(event.motion);
				break;
			case SDL_KEYUP:
				if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
					if(level_stack.top()->is_menu()){
						pop_level();
					}else {
						open_escape_menu();
					}
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				level_stack.top()->handle_mouse_button(event.button);
				break;
			default:
				//printf("%d\n", event.type);
				break;
		}
	}

	Game::Game() {
		window = std::unique_ptr<SDL_Window, SDL_Utilities::SDLWindowDeleter>(
				SDL_CreateWindow("InkBall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::GAME_WIDTH, Constants::GAME_HEIGHT,
								 SDL_WINDOW_OPENGL));


		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		if (!window) {
			throw SDL_Utilities::SDLError("Could not create Game window:");
		}

		renderer = std::unique_ptr<SDL_Renderer, SDL_Utilities::SDLRendererDeleter>(
				SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

		if (!renderer) {
			throw SDL_Utilities::SDLError("Could not create Game renderer:");
		}

		initialize_textures();

		load_level_from_path(LEVEL_PATH_PREFIX + std::string("Level 1.ikl"));
	}

	Game::~Game() {
		TTF_Quit();
		SDL_Quit();
	}

	void Game::initialize_textures() {
		for (auto &texture_info : texture_names) {
			std::string &common_name = texture_info.first;
			std::string &filename = texture_info.second;

			std::string path = ASSET_PATH_PREFIX + filename;
			SDL_Surface *surface = IMG_Load(path.c_str());

			if (surface == nullptr) {
				std::string message = "Could not load surface from ";
				message += path + ":";
				throw SDL_Utilities::SDLError(message.c_str());
			}

			textures[common_name] = std::unique_ptr<SDL_Texture, SDL_Utilities::SDLTextureDeleter>(
					SDL_CreateTextureFromSurface(renderer.get(), surface));

			if (surface != nullptr)
				SDL_FreeSurface(surface);

			if (!textures[common_name].get()) {
				throw SDL_Utilities::SDLError("Could not load texture:");
			}
		}
	}

	void Game::lose() {
		level_stack.push(std::make_unique<TextScreenLevel>("GAME OVER"));
	}

	SDL_Texture &Game::get_texture(std::string name) {
		return *textures[name];
	}

	void Game::win() {
		level_stack.push(std::make_unique<TextScreenLevel>("YOU WIN!"));
	}

	void Game::open_level_select() {
		level_stack.push(std::make_unique<LevelSelectMenu>(*this));
	}

	std::string Game::get_asset_path_prefix() {
		return ASSET_PATH_PREFIX;
	}

	std::string Game::get_level_path_prefix() {
		return LEVEL_PATH_PREFIX;
	}

	void Game::load_level_from_path(std::string path) {
		DeserializedLevelInformation deserialized = LevelDeserialization::read(path, *this);

		clear_level_stack();
		level_stack.push(std::make_unique<PlayableLevel>(deserialized, *this));
	}

	void Game::open_escape_menu() {
		level_stack.push(std::make_unique<EscapeMenu>(*this));
	}

	void Game::clear_level_stack() {
		while(!level_stack.empty())
			level_stack.pop();
	}

	void Game::pop_level() {
		level_stack.pop();
	}
}