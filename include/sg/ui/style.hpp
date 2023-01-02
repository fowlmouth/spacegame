#pragma once

#include "../asset-cache.hpp"

namespace sg::ui
{

struct Style
{
  AssetCache::FontRef font;
  int font_size;
  sf::Color background, foreground;
};

using StyleRef = std::shared_ptr< Style >;

}
