/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.h                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:29 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 23:16:48 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include "Clock/Clock.h"

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

        SDL_Rect _toggleMenu = { 0, 0, 0, 0 };
        std::vector<Sprite> _sprites;
        std::unique_ptr<Clock> _clock;

    protected:
        struct Box
        {
            float x, y, w, h;
        };

        void setToggle(const Box& box);
        void add(SDL_Renderer* renderer, const std::string& file, const Box& box);
        void addClock(SDL_Renderer* renderer, const Box& box);

    public:
        virtual ~Scene() = default;

        bool hitToggle(int x, int y) const;
        void update();
        void draw(SDL_Renderer* renderer) const;
};
