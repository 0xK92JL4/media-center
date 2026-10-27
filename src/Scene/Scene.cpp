/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.cpp                                              ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:38 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/27 21:22:49 by 0xK92JL4                 ▒▒    ▒▒        │*/
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

void Scene::add(SDL_Renderer* r,
                const std::string& file,
                const Box& b)
{
    Svg svg(asset(file));

    const float scale = std::min(
        b.w / svg.width(),
        b.h / svg.height()
    );

    const int pw = std::max(
        1, static_cast<int>(std::lround(svg.width() * scale))
    );

    const int ph = std::max(
        1, static_cast<int>(std::lround(svg.height() * scale))
    );

    const SDL_Rect dst = {
        static_cast<int>(std::lround(b.x)),
        static_cast<int>(std::lround(b.y)),
        pw,
        ph
    };

    _sprites.push_back(Sprite{
        svg.toTexture(r, pw, ph),
        dst
    });
}

void Scene::draw(SDL_Renderer* r) const
{
    for (const Sprite& sprite : _sprites)
    {
        SDL_RenderCopy(
            r,
            sprite.tex.get(),
            nullptr,
            &sprite.dst
        );
    }
}
