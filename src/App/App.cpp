/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  App.cpp                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:25 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 23:14:48 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "App.h"
#include "Theme.h"

#include "Scene/HomeMenuScene.h"
#include "Scene/ExtraMenuScene.h"

namespace
{
    constexpr int WINDOW_W = 1920;
    constexpr int WINDOW_H = 1080;
    constexpr int TEX_W    = 1920;
    constexpr int TEX_H    = 1080;
}

App::SdlContext::SdlContext()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw SdlError("SDL_Init");
    }
}

App::SdlContext::~SdlContext()
{
    SDL_Quit();
}

App::App(int menu)
{
    initWindow();
    initRenderer();
    loadScene(menu);
}

void App::initWindow()
{
    _window.reset(SDL_CreateWindow("menu", SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H,
                                   SDL_WINDOW_RESIZABLE));
    if (!_window)
    {
        throw SdlError("SDL_CreateWindow");
    }
}

void App::initRenderer()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    _renderer.reset(SDL_CreateRenderer(_window.get(), -1,
                                       SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_PRESENTVSYNC));
    if (!_renderer)
    {
        throw SdlError("SDL_CreateRenderer");
    }
    SDL_RenderSetLogicalSize(_renderer.get(), TEX_W, TEX_H);
}

void App::loadScene(int menu)
{
    std::unique_ptr<Scene> next;

    if (menu == 1)
        next = std::make_unique<HomeMenuScene>(_renderer.get());
    else
        next = std::make_unique<ExtraMenuScene>(_renderer.get());

    _scene = std::move(next);
    _menu  = menu;
}

void App::setColor(unsigned rgb) const
{
    SDL_SetRenderDrawColor(_renderer.get(),
                           (rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff, 255);
}

void App::run()
{
    while (_running)
    {
        events();
        update();
        draw();
    }
}

void App::events()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            _running = false;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            _running = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if (_scene->hitToggle(e.button.x, e.button.y))
            {
                loadScene(_menu == 1 ? 2 : 1);
                break;
            }
        }
    }
}

void App::update()
{
    _scene->update();
}

void App::draw()
{
    setColor(BG_COLOR);
    SDL_RenderClear(_renderer.get());
    _scene->draw(_renderer.get());
    SDL_RenderPresent(_renderer.get());
}
