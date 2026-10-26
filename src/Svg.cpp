/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  Svg.cpp                                                ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: 0xK92JL4                                               ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/10/26 11:46:02 by 0xK92JL4                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/10/26 11:46:04 by 0xK92JL4                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#define NANOSVG_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg.h"
#include "nanosvgrast.h"

#include "Svg.h"

#include <vector>

namespace
{
    struct RastDel
    {
        void operator()(NSVGrasterizer* p) const { nsvgDeleteRasterizer(p); }
    };
}

Svg::Svg(const std::string& path)
    : _image(nsvgParseFromFile(path.c_str(), "px", 96.0f))
{
    if (!_image)
    {
        throw std::runtime_error("cannot parse " + path);
    }
    if (_image->width < 2.0f || _image->height < 2.0f)
    {
        throw std::runtime_error("suspicious size in " + path +
                                 " (width/height 100%? see note)");
    }
}

float Svg::width() const
{
    return _image->width;
}

float Svg::height() const
{
    return _image->height;
}

TexturePtr Svg::toTexture(SDL_Renderer* renderer, int w, int h) const
{
    std::unique_ptr<NSVGrasterizer, RastDel> rast(nsvgCreateRasterizer());
    if (!rast)
    {
        throw std::runtime_error("nsvgCreateRasterizer failed");
    }

    std::vector<unsigned char> px(static_cast<size_t>(w) * h * 4);
    float scale = static_cast<float>(w) / _image->width;
    nsvgRasterize(rast.get(), _image.get(), 0, 0, scale, px.data(), w, h, w * 4);

    TexturePtr tex(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                     SDL_TEXTUREACCESS_STATIC, w, h));
    if (!tex)
    {
        throw SdlError("SDL_CreateTexture");
    }
    SDL_UpdateTexture(tex.get(), nullptr, px.data(), w * 4);
    SDL_SetTextureBlendMode(tex.get(), SDL_BLENDMODE_BLEND);
    return tex;
}
