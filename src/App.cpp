/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  App.cpp                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:25 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/26 11:49:44 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "App.h"

#include <cstdio>

namespace
{
    constexpr int WINDOW_W = 1280;
    constexpr int WINDOW_H = 720;
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

App::App(const std::string& svgPath)
{
    initWindow();
    initRenderer();
    loadSvg(svgPath);
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

void App::loadSvg(const std::string& path)
{
    Svg svg(path);
    std::printf("%s: %.1f x %.1f\n", path.c_str(), svg.width(), svg.height());
    _texture = svg.toTexture(_renderer.get(), TEX_W, TEX_H);
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
    }
}

void App::update()
{
}

void App::draw()
{
    SDL_Renderer* r = _renderer.get();
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    SDL_RenderCopy(r, _texture.get(), nullptr, nullptr);
    SDL_RenderPresent(r);
}
