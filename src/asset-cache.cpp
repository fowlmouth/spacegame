#include "asset-cache.hpp"

namespace sg
{

AssetCache::AssetCache(const std::string& path)
: _path(path)
{
}

const std::string& AssetCache::path() const
{
  return _path;
}
void AssetCache::set_path(const std::string& new_path)
{
  _path = new_path;
}

void AssetCache::clear()
{
  fonts.clear();
  textures.clear();
}

AssetCache::FontRef AssetCache::font(const std::string& path)
{
  const auto iter = fonts.find(path);
  if(iter == fonts.end())
  {
    AssetCache::FontRef font = std::make_shared< sf::Font >();
    if(!font->loadFromFile(_path + "/" + path))
      font = {};
    return fonts[path] = font;
  }
  return iter->second;
}

AssetCache::TextureRef AssetCache::texture(const std::string& path)
{
  const auto iter = textures.find(path);
  if(iter == textures.end())
  {
    AssetCache::TextureRef texture = std::make_shared< sf::Texture >();
    if(!texture->loadFromFile(_path + "/" + path))
      texture = {};
    return textures[path] = texture;
  }
  return iter->second;
}


}

