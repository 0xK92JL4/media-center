/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.cpp                                              ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:38 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/03 11:28:48 by 0xK92JL4                 ▒▒    ▒▒        │*/
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

Scene::Sprite Scene::load(SDL_Renderer* r, const std::string& file,
                          const Box& b) const
{
    Svg svg(asset(file));

    const float k     = OutputScale(r);
    const float scale = std::min(b.w / svg.width(), b.h / svg.height());

    const float lw = svg.width()  * scale;
    const float lh = svg.height() * scale;
    const int   pw = std::max(1, static_cast<int>(std::lround(lw * k)));
    const int   ph = std::max(1, static_cast<int>(std::lround(lh * k)));

    return Sprite{ svg.toTexture(r, pw, ph), SDL_FRect{ b.x, b.y, lw, lh } };
}

void Scene::add(SDL_Renderer* r, const std::string& file, const Box& b)
{
    _sprites.push_back(load(r, file, b));
}

void Scene::addHover(SDL_Renderer* r, const std::string& file, const Box& b)
{
    _hovers.push_back(load(r, file, b));
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

void Scene::hover(int x, int y)
{
    _hovered = -1;
    for (size_t i = 0; i < _hovers.size(); ++i)
    {
        const SDL_FRect& d = _hovers[i].dst;
        if (x >= d.x && x < d.x + d.w && y >= d.y && y < d.y + d.h)
        {
            _hovered = static_cast<int>(i);
            break;
        }
    }
}

void Scene::addClock(SDL_Renderer* r, const Box& b)
{
    _clock = std::make_unique<Clock>(r, asset("common/clock.svg"),
            b.x, b.y, b.w, b.h);
}

void Scene::addStatus(SDL_Renderer* r, const Box& dot, const Box& bat)
{
    _dot[0] = load(r, "controller/controller_off.svg", dot);
    _dot[1] = load(r, "controller/controller_on.svg",  dot);

    static const char* const levels[5] = { "20", "40", "60", "80", "100" };
    for (int i = 0; i < 5; ++i)
    {
        _battery[i] = load(r, std::string("batteries/battery_") + levels[i] + ".svg", bat);
    }
    _hasStatus = true;
}

void Scene::setStatus(const Status& s)
{
    _status = s;
}

void Scene::draw(SDL_Renderer* r) const
{
    for (const Sprite& sprite : _sprites)
    {
        SDL_RenderCopyF(r, sprite.tex.get(), nullptr, &sprite.dst);
    }
    if (_hovered >= 0)
    {
        const Sprite& h = _hovers[_hovered];
        SDL_RenderCopyF(r, h.tex.get(), nullptr, &h.dst);
    }
    if (_hasStatus)
    {
        const Sprite& d = _dot[_status.connected ? 1 : 0];
        SDL_RenderCopyF(r, d.tex.get(), nullptr, &d.dst);

        if (_status.connected)
        {
            const int i = std::clamp((_status.battery - 1) / 20, 0, 4);
            const Sprite& b = _battery[i];
            SDL_RenderCopyF(r, b.tex.get(), nullptr, &b.dst);
        }
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
