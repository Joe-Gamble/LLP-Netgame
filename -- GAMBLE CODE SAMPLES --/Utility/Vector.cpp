#include "gamelib/Vector.hpp"

#include <cmath>

Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

/**
 *   @brief   Copies a vector.
 *   @details Constructs a new vector2 from an existing.
 *   @return  void
 */
Vector2::Vector2(Vector2&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
  if (&rhs != this)
  {
    *this = Vector2(rhs);
  }
  return *this;
}

/**
 *   @brief   Copies a vector.
 *   @details Updates vector3 from an existing.
 *   @return  void
 */
Vector2& Vector2::operator=(Vector2&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;

  return *this;
}

bool Vector2::operator==(const Vector2& rhs)
{
  return this->x == rhs.x && this->y == rhs.y;
}

Vector2& Vector2::operator*=(float scalar)
{
  this->x *= scalar;
  this->y *= scalar;

  return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;

  return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
  Vector2 vec(*this);
  vec.x -= rhs.x;
  vec.y -= rhs.y;

  return vec;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
  Vector2 vec(*this);
  vec.x += rhs.x;
  vec.y += rhs.y;

  return vec;
}

Vector2 Vector2::operator+=(const Vector2& rhs)
{
  this->x += rhs.x;
  this->y += rhs.y;

  return *this;
}

/**
 *   @brief   Scales the vector.
 *   @details Uses a single scalar value to adjust the vector.
 *   @return  void
 */
Vector2 Vector2::operator*(float scalar)
{
  Vector2 vec(*this);
  vec.x *= scalar;
  vec.y *= scalar;
  return vec;
}

/**
 *   @brief   Normalises vector.
 *   @details Turns the vector into a unit vector.
 *   @return  void
 */
void Vector2::normalise()
{
  float magnitude = sqrtf((x * x) + (y * y));

  if (magnitude == 0.0F)
  {
    return;
  }
  x /= magnitude;
  y /= magnitude;
}

/**
 *  @brief   returns the distance between two vectors.
 *  @details Uses the distance formula to calculate teh exact distance between 2 points in space.
 *  @param The end point of the distance calculation.
 *  @return float
 */
float Vector2::distance(const Vector2& rhs) const
{
  float distance = sqrtf(powf(this->x - rhs.x, 2) + powf(this->y - rhs.y, 2));
  return distance;
}

Vector2 Vector2::midpoint(const Vector2& rhs)
{
  const float scale = 0.5F;
  Vector2 midpoint  = (this->operator+(rhs).operator*(scale));
  return midpoint;
}

/**
 *   @brief   Constructor.
 *   @details Requires values for it's x and y magnitudes.
 *   @return  void
 */
Vector3::Vector3(float x_, float y_, float z_) noexcept : x(x_), y(y_), z(z_) {}

/**
 *   @brief   Copies a vector.
 *   @details Constructs a new vector3 from an existing.
 *   @return  void
 */
Vector3::Vector3(Vector3&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
  if (&rhs != this)
  {
    *this = Vector3(rhs);
  }
  return *this;
}

/**
 *  @brief   Converts a vector2 position into a vector3 value.
 *   @details Constructs a new vector3 from an existing vector 2 with the utility to pass through a
 * z value.
 *   @return  void
 */
Vector3::Vector3(const Vector2& rhs, float z) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = z;
}
/**
 *   @brief   Copies a vector.
 *   @details Updates vector3 from an existing.
 *   @return  void
 */

Vector3& Vector3::operator=(Vector3&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;

  return *this;
}

bool Vector3::operator==(const Vector3& rhs)
{
  return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

Vector3 Vector3::operator*=(float scalar)
{
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;

  return *this;
}

Vector3 Vector3::operator-=(const Vector3& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;

  return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
  Vector3 vec(*this);
  vec.x -= rhs.x;
  vec.y -= rhs.y;
  vec.z -= rhs.z;

  return vec;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{
  Vector3 vec(*this);
  vec.x += rhs.x;
  vec.y += rhs.y;
  vec.z += rhs.z;

  return vec;
}

/**
 *   @brief   Scales the vector.
 *   @details Uses a single scalar value to adjust the vector.
 *   @return  void
 */
Vector3 Vector3::operator*(float scalar)
{
  Vector3 vec(*this);
  vec.x *= scalar;
  vec.y *= scalar;
  vec.z *= scalar;
  return vec;
}

/**
 *   @brief   Normalises vector.
 *   @details Turns the vector into a unit vector.
 *   @return  void
 */
void Vector3::normalise()
{
  float magnitude = sqrtf((x * x) + (y * y) + (z * z));

  if (magnitude == 0.0F)
  {
    return;
  }

  x /= magnitude;
  y /= magnitude;
  z /= magnitude;
}

/**
 *  @brief   returns the distance between two vectors.
 *  @details Uses the distance formula to calculate teh exact distance between 2 points in space.
 *  @param The end point of the distance calculation.
 *  @return float
 */
float Vector3::distance(const Vector3& rhs) const
{
  float distance =
    sqrtf(powf(this->x - rhs.x, 2) + powf(this->y - rhs.y, 2) + powf(this->z - rhs.z, 2));
  return distance;
}

Vector3 Vector3::midpoint(const Vector3& rhs)
{
  const float scale = 0.5F;
  Vector3 midpoint  = (this->operator+(rhs).operator*(scale));
  return midpoint;
}

/**
 *   @brief   Constructor.
 *   @details Requires values for it's x and y magnitudes.
 *   @return  void
 */
Vector4::Vector4(float x_, float y_, float z_, float b_) noexcept : x(x_), y(y_), z(z_), b(b_) {}

/**
 *   @brief   Copies a vector.
 *   @details Constructs a new vector3 from an existing.
 *   @return  void
 */
Vector4::Vector4(Vector4&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  this->b = rhs.b;
}

Vector4& Vector4::operator=(const Vector4& rhs)
{
  if (&rhs != this)
  {
    *this = Vector4(rhs);
  }
  return *this;
}

/**
 *   @brief   Copies a vector.
 *   @details Updates vector3 from an existing.
 *   @return  void
 */

Vector4& Vector4::operator=(Vector4&& rhs) noexcept
{
  this->x = rhs.x;
  this->y = rhs.y;
  this->z = rhs.z;
  this->b = rhs.b;

  return *this;
}

bool Vector4::operator==(const Vector4& rhs)
{
  return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->b == rhs.b;
}

Vector4 Vector4::operator*=(float scalar)
{
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
  this->b *= scalar;

  return *this;
}

Vector4 Vector4::operator-=(const Vector4& rhs)
{
  this->x -= rhs.x;
  this->y -= rhs.y;
  this->z -= rhs.z;
  this->b -= rhs.b;

  return *this;
}

Vector4 Vector4::operator-(const Vector4& rhs)
{
  Vector4 vec(*this);
  vec.x -= rhs.x;
  vec.y -= rhs.y;
  vec.z -= rhs.z;
  vec.b -= rhs.b;

  return vec;
}

Vector4 Vector4::operator+(const Vector4& rhs)
{
  Vector4 vec(*this);
  vec.x += rhs.x;
  vec.y += rhs.y;
  vec.z += rhs.z;
  vec.b += rhs.b;

  return vec;
}

/**
 *   @brief   Scales the vector.
 *   @details Uses a single scalar value to adjust the vector.
 *   @return  void
 */
Vector4 Vector4::operator*(float scalar)
{
  Vector4 vec(*this);

  vec.x *= scalar;
  vec.y *= scalar;
  vec.z *= scalar;
  vec.b *= scalar;

  return vec;
}

/**
 *   @brief   Normalises vector.
 *   @details Turns the vector into a unit vector.
 *   @return  void
 */
void Vector4::normalise()
{
  float magnitude = sqrtf((x * x) + (y * y) + (z * z) + (b * b));

  if (magnitude == 0.0F)
  {
    return;
  }

  x /= magnitude;
  y /= magnitude;
  z /= magnitude;
  b /= magnitude;
}
