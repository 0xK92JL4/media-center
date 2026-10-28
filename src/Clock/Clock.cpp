/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Clock.cpp                                              ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/28 11:55:54 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 12:17:12 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "Clock.h"
#include "Svg/Svg.h"

#include <algorithm>
#include <cmath>

Clock::Clock(SDL_Renderer* r, const std::string& file,
             float x, float y, float w, float h)
    : _x(static_cast<int>(std::lround(x))),
      _y(static_cast<int>(std::lround(y)))
{
    Svg svg(file);

    const float cell  = svg.width() / GLYPHS;
    const float scale = std::min(w / (5 * cell), h / svg.height());

    _cell = std::max(1, static_cast<int>(std::lround(cell * scale)));
    _h    = std::max(1, static_cast<int>(std::lround(svg.height() * scale)));

    _tex = svg.toTexture(r, _cell * GLYPHS, _h);
    refresh();
}

void Clock::refresh()
{
    const std::time_t t = std::time(nullptr);
    if (t == _last)
    {
        return;
    }
    _last = t;

    std::tm tm{};
    localtime_r(&t, &tm);
    char buf[6];
    std::strftime(buf, sizeof buf, "%H:%M", &tm);
    _text = buf;
}

void Clock::update()
{
    refresh();
}

void Clock::draw(SDL_Renderer* r) const
{
    int i = 0;
    for (char c : _text)
    {
        const int g = (c == ':') ? 10 : c - '0';
        const SDL_Rect src = { g * _cell, 0, _cell, _h };
        const SDL_Rect dst = { _x + i * _cell, _y, _cell, _h };
        SDL_RenderCopy(r, _tex.get(), &src, &dst);
        ++i;
    }
}
