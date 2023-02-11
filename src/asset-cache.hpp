#pragma once

#include "SFML/Graphics.hpp"


#include <unordered_map>
#include <memory>
#include <string>


namespace sg
{

class AssetCache
{
public:
  using FontRef = std::shared_ptr< sf::Font >;
  using TextureRef = std::shared_ptr< sf::Texture >;
  

  AssetCache(const std::string& path);

  const std::string& path() const;
  void set_path(const std::string&);

  void clear();

  FontRef font(const std::string& path);
  TextureRef texture(const std::string& path);

private:
  std::string _path;
  std::unordered_map< std::string, FontRef > fonts;
  std::unordered_map< std::string, TextureRef > textures;

};

}

