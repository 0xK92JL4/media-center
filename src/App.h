/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  App.h                                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:40 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/26 11:45:41 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Sdl.h"
#include "Svg.h"
#include <string>

class App
{
	private:
		struct SdlContext
		{
			SdlContext();
			~SdlContext();
			SdlContext(const SdlContext&) = delete;
			SdlContext& operator=(const SdlContext&) = delete;
		};

		void initWindow();
		void initRenderer();
		void loadSvg(const std::string& path);

		void events();
		void update();
		void draw();

		SdlContext  _sdl;
		WindowPtr   _window;
		RendererPtr _renderer;
		TexturePtr  _texture;
		bool        _running = true;

	public:
		explicit App(const std::string& svgPath);

		void run();
};
