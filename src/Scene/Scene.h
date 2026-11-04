/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Scene.h                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 20:36:29 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/03 11:33:49 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include "Clock/Clock.h"
#include "Status/Status.h"

#include <string>
#include <vector>
#include <algorithm>

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
            SDL_FRect dst;
        };

        struct Button
        {
            SDL_Rect rect;
            Action   action;
        };

        std::vector<Button> _buttons;
        std::vector<Sprite> _sprites;
        std::unique_ptr<Clock> _clock;

        std::vector<Sprite> _hovers;
        int                 _hovered = -1;

        Sprite _dot[2];
        Sprite _battery[5];
        Status _status;
        bool   _hasStatus = false;

    protected:
        struct Box
        {
            float x, y, w, h;
        };

        void addButton(const Box& box, Action action);
        void add(SDL_Renderer* renderer, const std::string& file, const Box& box);
        void addClock(SDL_Renderer* renderer, const Box& box);
        void addHover(SDL_Renderer* renderer, const std::string& file, const Box& box);
        void addStatus(SDL_Renderer* renderer, const Box& dot, const Box& battery);

    private:
        Sprite load(SDL_Renderer* renderer, const std::string& file, const Box& box) const;

    public:
        virtual ~Scene() = default;

        Action hit(int x, int y) const;
        void hover(int x, int y);
        void setStatus(const Status& status);
        void update();
        void draw(SDL_Renderer* renderer) const;
};
