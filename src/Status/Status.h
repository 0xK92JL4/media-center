/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Status.h                                               ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/11/04 23:10:46 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/11/04 23:14:01 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include <SDL2/SDL.h>

struct Status
{
    bool connected = false;
    int  battery   = 0;      // 0-100
};

class StatusSource
{
    public:
        virtual ~StatusSource() = default;
        virtual Status poll() = 0;
};

class SysfsStatusSource : public StatusSource
{
    private:
        Uint32 _last = 0;
        bool   _init = false;
        Status _cached;

    public:
        Status poll() override;
};
