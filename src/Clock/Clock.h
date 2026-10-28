/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Clock.h                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/28 11:49:39 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 11:55:31 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include <ctime>
#include <string>

class Clock
{
	private:
		static constexpr int GLYPHS = 11;

		void refresh();

		TexturePtr  _tex;
		int         _cell = 0;
		int         _h    = 0;
		int         _x    = 0;
		int         _y    = 0;
		std::string _text;
		std::time_t _last = 0;

	public:
		Clock(SDL_Renderer* r, const std::string& file,
		      float x, float y, float w, float h);

		void update();
		void draw(SDL_Renderer* r) const;
};
