/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  ExtraMenuScene.cpp                                     ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/27 21:04:05 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/27 22:28:24 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "ExtraMenuScene.h"

ExtraMenuScene::ExtraMenuScene(SDL_Renderer* r)
{
    // Top bar
    add(r, "common/divider.svg",             { 48.0f,    80.0f,  1824.0f, 10.0f });
    add(r, "menu/menu_icon.svg",             { 116.2f,   33.1f,  23.2f,   23.2f });
    add(r, "menu/menu_extra.svg",            { 154.3f,   33.0f,  105.0f,  23.8f });
    add(r, "common/clock.svg",               { 924.5f,   33.6f,  90.7f,   23.2f });
    add(r, "controller/controller_on.svg",   { 1666.77f, 35.45f, 12.51f,  12.51f });
    add(r, "controller/controller_icon.svg", { 1695.00f, 24.57f, 66.71f,  32.13f });
    add(r, "batteries/battery_100.svg",      { 1761.26f, 32.35f, 35.34f,  18.33f });

    // Browser tile
    add(r, "buttons/browser_bg.svg",  { 150.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/browser_icon.svg",  { 344.8f, 442.9f, 60.5f,  60.5f });
    add(r, "buttons/browser_txt.svg", { 302.75f, 567.2f, 144.5f, 30.0f });

    // Shutdown tile
    add(r, "buttons/shutdown_bg.svg",  { 735.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/shutdown_icon.svg",  { 929.8f, 442.9f, 60.5f,  60.5f });
    add(r, "buttons/shutdown_txt.svg", { 873.5f, 567.2f, 173.0f, 30.0f });

    // Exit tile
    add(r, "buttons/exit_bg.svg",  { 1320.0f, 390.0f, 450.0f, 300.0f });
    add(r, "icons/exit_icon.svg",  { 1514.8f, 442.9f, 60.5f,  60.5f });
    add(r, "buttons/exit_txt.svg", { 1516.0f, 567.2f, 58.0f,  30.0f });
}
