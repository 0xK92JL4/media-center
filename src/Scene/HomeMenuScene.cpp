/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  HomeMenuScene.cpp                                      ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 21:00:09 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/28 23:12:01 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "HomeMenuScene.h"

HomeMenuScene::HomeMenuScene(SDL_Renderer* r)
{
    // Top bar
    add(r, "common/divider.svg",             { 48.0f,    80.0f,  1824.0f, 10.0f });
    add(r, "menu/menu_icon.svg",             { 116.2f,   33.1f,  23.2f,   23.2f });
    add(r, "menu/menu_home.svg",             { 154.3f,   33.0f,  85.0f,   23.8f });
    add(r, "controller/controller_on.svg",   { 1666.77f, 35.45f, 12.51f, 12.51f });
    add(r, "controller/controller_icon.svg", { 1695.00f, 24.57f, 66.71f, 32.13f });
    add(r, "batteries/battery_100.svg",      { 1761.26f, 32.35f, 35.34f, 18.33f });

    addClock(r, { 924.5f, 33.6f, 90.7f, 23.2f });

    // Search tile
    add(r, "buttons/search_bg.svg",  { 150.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/search_icon.svg",  { 344.8f, 442.9f, 60.5f,  60.5f });
    add(r, "buttons/search_txt.svg", { 319.0f, 567.2f, 112.0f, 30.0f });

    // Continue tile
    add(r, "buttons/continue_bg.svg",  { 735.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/continue_icon.svg",  { 929.8f, 442.9f, 60.5f,  60.5f });
    add(r, "buttons/continue_txt.svg", { 880.75f, 567.2f, 158.5f, 30.0f });

    // Library tile
    add(r, "buttons/library_bg.svg",  { 1320.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/library_icon.svg", { 1520.05f, 448.15f, 50.0f, 50.0f });
    add(r, "buttons/library_txt.svg", { 1486.5f, 567.2f, 117.0f, 40.0f });

    // Toggle Menu Button
    setToggle({ 110.0f, 24.0f, 135.0f, 40.0f });
}
