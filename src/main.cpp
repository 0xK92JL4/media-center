/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  main.cpp                                               ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:45:47 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/26 11:45:49 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "App.h"

#include <cstdio>
#include <exception>

int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : "build/menu/menu_home.svg";

    try
    {
        App app(path);
        app.run();
    }
    catch (const std::exception& e)
    {
        std::fprintf(stderr, "error: %s\n", e.what());
        return 1;
    }
    return 0;
}
