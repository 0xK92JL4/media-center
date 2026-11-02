/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Sdl.h                                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:55 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/02 13:00:06 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <stdexcept>
#include <string>

struct WindowDel
{
    void operator()(SDL_Window* p) const { SDL_DestroyWindow(p); }
};

struct RendererDel
{
    void operator()(SDL_Renderer* p) const { SDL_DestroyRenderer(p); }
};

struct TextureDel
{
    void operator()(SDL_Texture* p) const { SDL_DestroyTexture(p); }
};

using WindowPtr   = std::unique_ptr<SDL_Window, WindowDel>;
using RendererPtr = std::unique_ptr<SDL_Renderer, RendererDel>;
using TexturePtr  = std::unique_ptr<SDL_Texture, TextureDel>;

inline std::runtime_error SdlError(const std::string& what)
{
    return std::runtime_error(what + ": " + SDL_GetError());
}

inline float OutputScale(SDL_Renderer* r)
{
    int w = 0, h = 0;
    SDL_GetRendererOutputSize(r, &w, &h);
    const float k = std::min(w / 1920.0f, h / 1080.0f);
    return k < 1.0f ? 1.0f : k;
}
