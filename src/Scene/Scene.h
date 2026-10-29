/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.h                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:29 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/29 11:09:15 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include "Clock/Clock.h"

#include <string>
#include <vector>

enum class Action
{
    None,
    ToggleMenu,
    Search, Continue, Library,
    Browser, Shutdown, Exit
};

class Scene
{
    private:
        struct Sprite
        {
            TexturePtr tex;
            SDL_Rect dst;
        };

        struct Button
        {
            SDL_Rect rect;
            Action   action;
        };

        std::vector<Button> _buttons;
        std::vector<Sprite> _sprites;
        std::unique_ptr<Clock> _clock;

    protected:
        struct Box
        {
            float x, y, w, h;
        };

        void addButton(const Box& box, Action action);
        void add(SDL_Renderer* renderer, const std::string& file, const Box& box);
        void addClock(SDL_Renderer* renderer, const Box& box);

    public:
        virtual ~Scene() = default;

        Action hit(int x, int y) const;
        void update();
        void draw(SDL_Renderer* renderer) const;
};
