/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  App.h                                                  ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:40 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 23:13:04 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "Scene/Scene.h"
#include "Sdl.h"
#include <memory>

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
		void loadScene(int menu);
		void setColor(unsigned rgb) const;

		void events();
		void update();
		void draw();

        int                    _menu = 1;
		SdlContext             _sdl;
		WindowPtr              _window;
		RendererPtr            _renderer;
		std::unique_ptr<Scene> _scene;
		bool                   _running = true;

	public:
		explicit App(int menu);

		void run();
};
