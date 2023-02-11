#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

template< typename T >
std::ostream& operator<< (std::ostream& stream, const sf::Rect<T>& rect)
{
  return stream << "{" << rect.left << ", " << rect.top << " size= " << rect.width << " x " << rect.height << " }";
}
