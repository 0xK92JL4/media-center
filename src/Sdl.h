/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Sdl.h                                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:55 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/26 11:45:56 by 0xK92JL4                 ▒▒    ▒▒        │*/
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
