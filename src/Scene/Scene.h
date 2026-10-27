/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.h                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:29 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/27 21:20:37 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"

#include <string>
#include <vector>

class Scene
{
    private:
        struct Sprite
        {
            TexturePtr tex;
            SDL_Rect dst;
        };

        std::vector<Sprite> _sprites;

    protected:
        struct Box
        {
            float x, y, w, h;
        };

        void add(SDL_Renderer* renderer, const std::string& file, const Box& box);

    public:
        virtual ~Scene() = default;

        void draw(SDL_Renderer* renderer) const;
};
