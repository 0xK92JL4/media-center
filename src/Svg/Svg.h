/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Svg.h                                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:46:10 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 12:24:04 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include "nanosvg.h"
#include <string>

class Svg
{
	private:
		struct ImageDel
		{
			void operator()(NSVGimage* p) const { nsvgDelete(p); }
		};

		std::unique_ptr<NSVGimage, ImageDel> _image;

	public:
		explicit Svg(const std::string& path);

		float width() const;
		float height() const;

		TexturePtr toTexture(SDL_Renderer* renderer, int w, int h) const;
        TexturePtr toTexture(SDL_Renderer* renderer, int w, int h, float scale) const;
};
