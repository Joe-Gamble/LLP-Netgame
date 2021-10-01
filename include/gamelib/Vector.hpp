//
// Joe Gamble 20/03/20
//

#ifndef MYNETGAME_VECTOR_HPP
#define MYNETGAME_VECTOR_HPP

struct Vector2
{
  // construction
  Vector2(const Vector2& rhs) = default;   /// Default constructor
  Vector2(float x_, float y_);             /// 2 Separate inputs
  Vector2(Vector2&& rhs) noexcept;         /// copy constructor
  Vector2& operator=(const Vector2& rhs);  /// copy assignment operator

  ~Vector2() = default;

  // operations
  Vector2& operator=(Vector2&& rhs) noexcept;  ///        =
  Vector2& operator*=(float scalar);           ///        *=
  Vector2& operator-=(const Vector2& rhs);     ///        -=
  Vector2 operator*(float scalar);             ///        *
  Vector2 operator-(const Vector2& rhs);       ///        -
  Vector2 operator+(const Vector2& rhs);       ///        +
  Vector2 operator+=(const Vector2& rhs);      ///        +=
  bool operator==(const Vector2& rhs);         ///        ==

  // utility
  [[nodiscard]] float distance(const Vector2& rhs) const;
  [[nodiscard]] Vector2 midpoint(const Vector2& rhs);

  void normalise();

  // data
  float x = 0;
  float y = 0;
};

struct Vector3
{
  // construction!
  Vector3(const Vector3&) = default;               /// Default constructor
  Vector3(float x_, float y_, float z_) noexcept;  /// 3 Separate inputs
  Vector3(Vector3&& rhs) noexcept;                 /// copy constructor
  Vector3& operator=(const Vector3& rhs);          /// copy assignment operator
  Vector3(const Vector2& rhs, float z) noexcept;   /// Vector2 and Z inputs

  ~Vector3() = default;

  // operations
  Vector3& operator=(Vector3&& rhs) noexcept;  ///       =
  Vector3 operator*=(float scalar);            ///             *=
  Vector3 operator-=(const Vector3& rhs);      ///       -=
  Vector3 operator*(float scalar);             ///              *
  Vector3 operator-(const Vector3& rhs);       ///        -
  Vector3 operator+(const Vector3& rhs);       ///        +
  bool operator==(const Vector3& rhs);         ///          ==

  // utility
  [[nodiscard]] float distance(const Vector3& rhs) const;
  [[nodiscard]] Vector3 midpoint(const Vector3& rhs);

  void normalise();

  // data
  float x = 0;
  float y = 0;
  float z = 0;
};

struct Vector4
{
  // construction
  Vector4(const Vector4&) = default;                         /// Default constructor
  Vector4(float x_, float y_, float z_, float b_) noexcept;  /// 3 Separate inputs
  Vector4(Vector4&& rhs) noexcept;                           /// copy constructor
  Vector4& operator=(const Vector4& rhs);                    /// copy assignment operator

  ~Vector4() = default;

  // operations
  Vector4& operator=(Vector4&& rhs) noexcept;  ///       =
  Vector4 operator*=(float scalar);            ///             *=
  Vector4 operator-=(const Vector4& rhs);      ///       -=
  Vector4 operator*(float scalar);             ///              *
  Vector4 operator-(const Vector4& rhs);       ///        -
  Vector4 operator+(const Vector4& rhs);       ///        +
  bool operator==(const Vector4& rhs);         ///          ==

  // utility
  void normalise();

  // data
  float x = 0;
  float y = 0;
  float z = 0;
  float b = 0;
};

#endif  // MYNETGAME_VECTOR_HPP
