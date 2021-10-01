// Joe Gamble 22/03/20 - Credit to James Huxtable for the original 2D implementation

/**
 * Rect Utility for defining the constraints of objects within the game
 * Functionaility for bounds
 */

#ifndef MYNETGAME_RECT_HPP
#define MYNETGAME_RECT_HPP

#include "Vector.hpp"

struct Rect
{
  Vector3 origin = {0, 0, 0};
  float length   = 0;
  float height   = 0;
  float depth    = 0;

  [[nodiscard]] bool isInside(const Vector3& rhs) const;
  [[nodiscard]] bool isInside(const Rect& rhs) const;
  [[nodiscard]] bool isBetween(float value, float min, float max) const;

  Vector3 getCenter();
};

#endif  // MYNETGAME_RECT_HPP
