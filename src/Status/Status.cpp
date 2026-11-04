/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Status.cpp                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/11/04 23:09:58 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/04 23:13:52 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#include "Status.h"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace
{
    bool isController(const std::string& name)
    {
        return name.rfind("sony_controller_battery", 0) == 0 ||
               name.rfind("ps-controller-battery", 0) == 0;
    }

    bool readLine(const fs::path& p, std::string& out)
    {
        std::ifstream f(p);
        return static_cast<bool>(std::getline(f, out));
    }
}

Status SysfsStatusSource::poll()
{
    const Uint32 now = SDL_GetTicks();
    if (_init && now - _last < 1000)
    {
        return _cached;
    }
    _init = true;
    _last = now;

    Status s;
    std::error_code ec;
    for (const auto& e : fs::directory_iterator("/sys/class/power_supply", ec))
    {
        if (!isController(e.path().filename().string()))
        {
            continue;
        }
        std::string cap;
        if (!readLine(e.path() / "capacity", cap))
        {
            continue;
        }
        s.connected = true;
        s.battery   = std::clamp(std::atoi(cap.c_str()), 0, 100);
        break;
    }
    _cached = s;
    return s;
}
