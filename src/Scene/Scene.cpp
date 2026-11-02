/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.cpp                                              ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:38 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/02 13:02:28 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "Scene/Scene.h"
#include "Svg/Svg.h"
#include "Theme.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace
{
    std::string asset(const std::string& rel)
    {
        return std::string("build/themes/")
             + THEME_NAME + "/" + rel;
    }
}

void Scene::add(SDL_Renderer* r, const std::string& file, const Box& b)
{
    Svg svg(asset(file));

    const float k     = OutputScale(r);
    const float scale = std::min(b.w / svg.width(), b.h / svg.height());

    const float lw = svg.width()  * scale;
    const float lh = svg.height() * scale;
    const int   pw = std::max(1, static_cast<int>(std::lround(lw * k)));
    const int   ph = std::max(1, static_cast<int>(std::lround(lh * k)));

    _sprites.push_back(Sprite{
        svg.toTexture(r, pw, ph),
        SDL_FRect{ b.x, b.y, lw, lh }
    });
}

void Scene::addButton(const Box& b, Action action)
{
    _buttons.push_back(Button{
        {
            static_cast<int>(std::lround(b.x)),
            static_cast<int>(std::lround(b.y)),
            static_cast<int>(std::lround(b.w)),
            static_cast<int>(std::lround(b.h))
        },
        action
    });
}

Action Scene::hit(int x, int y) const
{
    const SDL_Point p = { x, y };
    for (const Button& b : _buttons)
    {
        if (SDL_PointInRect(&p, &b.rect))
            return b.action;
    }
    return Action::None;
}

void Scene::addClock(SDL_Renderer* r, const Box& b)
{
    _clock = std::make_unique<Clock>(r, asset("common/clock.svg"),
            b.x, b.y, b.w, b.h);
}

void Scene::draw(SDL_Renderer* r) const
{
    for (const Sprite& sprite : _sprites)
    {
        SDL_RenderCopyF(r, sprite.tex.get(), nullptr, &sprite.dst);
    }
    if (_clock)
    {
        _clock->draw(r);
    }
}

void Scene::update()
{
    if (_clock)
        _clock->update();
}
