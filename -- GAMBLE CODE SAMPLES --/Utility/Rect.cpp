//
// Joe Gamble 22/03/20 - Credit to James Huxtable for the original 2D implementation
//

#include "gamelib/Rect.hpp"

/**
*   @brief   Does a point reside within this rectangle?
*   @details Will check to see if the x and y coordinates
             provided reside within the area of the rectangle.
*   @return  True if they do.
*/
bool Rect::isInside(const Vector3& rhs) const
{
  if (rhs.x >= this->origin.x && rhs.x <= this->origin.x + this->length)
  {
    if (rhs.y >= this->origin.y && rhs.y <= this->origin.y + this->height)
    {
      if (rhs.z >= this->origin.z && rhs.z <= this->origin.z + this->depth)
      {
        return true;
      }
    }
  }

  return false;
}

Vector3 Rect::getCenter()
{
  Vector3 center = {origin.x + (length / 2), origin.y + (height / 2), 0};
  return center;
}

/**
 *   @brief   Does a another rectangle reside within this rectangle?
 *   @details Will check to see if the two rectanges overlap.
 *   @return  True if they do.
 */
bool Rect::isInside(const Rect& rhs) const
{
  const auto& lhs = *this;

  bool x_overlap = isBetween(lhs.origin.x, rhs.origin.x, rhs.origin.x + rhs.length) ||
                   isBetween(rhs.origin.x, lhs.origin.x, lhs.origin.x + lhs.length);

  bool y_overlap = isBetween(lhs.origin.y, rhs.origin.y, rhs.origin.y + rhs.height) ||
                   isBetween(rhs.origin.y, lhs.origin.y, lhs.origin.y + lhs.height);

  bool z_overlap = isBetween(lhs.origin.z, rhs.origin.z, rhs.origin.z + rhs.depth) ||
                   isBetween(rhs.origin.z, lhs.origin.z, lhs.origin.z + lhs.depth);

  return (x_overlap && y_overlap && z_overlap);
}

/**
 *   @brief   Checks to see if a value falls within a range.
 *   @details Takes a value and uses a min and max to generate a
 *            check to see if the value falls inside it's range.
 *   @return  True if they do.
 */
bool Rect::isBetween(float value, float min, float max) const
{
  return (value >= min) && (value <= max);
}
