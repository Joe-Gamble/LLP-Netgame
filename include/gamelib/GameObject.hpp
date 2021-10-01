// Joe Gamble 22/03/20 - Credit to James Huxtable for the original GameObject class

#ifndef MYNETGAME_GAMEOBJECT_HPP
#define MYNETGAME_GAMEOBJECT_HPP

#include "Components/SpriteComponent.hpp"
#include "Vector.hpp"

#include <string>

/**
 *  Objects used throughout the game.
 *  Provides a nice solid base class for objects in this game world.
 *  They currently support only sprite components, but this could easily
 *  be extended to include things like rigid bodies or input systems.
 *  @see SpriteComponent
 */
class GameObject
{
 public:
  GameObject() = default;
  ~GameObject();

  /// Clang Tidy destructor issue work-around
  GameObject(GameObject const&) = default;
  GameObject& operator=(GameObject const&) = default;
  GameObject(GameObject&&)                 = default;
  GameObject& operator=(GameObject&&) = default;

  /**
   *  Allocates and attaches a sprite component to the object.
   *  Part of this process will attempt to load a texture file.
   *  If this fails this function will return false and the memory
   *  allocated, freed.
   *  @param [in] renderer The renderer used to perform the allocations
   *  @param [in] texture_file_name The file path to the the texture to load
   *  @return true if the component is successfully added
   */
  bool instantiate(
    ASGE::Renderer* renderer,
    const std::string& texture_file_name,
    float xpos,
    float ypos,
    float width,
    float height);

  bool instantiate(
    ASGE::Renderer* renderer,
    const std::string& texture_file_name,
    float xpos,
    float ypos,
    float width,
    float height,
    const Vector2& coords);

  bool instantiate(
    ASGE::Renderer* renderer,
    const std::string& texture_file_name,
    float xpos,
    float ypos);

  bool instantiate(ASGE::Renderer* renderer, const std::string& texture_file_name);

  /**
   *  Returns the sprite componenent.
   *  IT IS HIGHLY RECOMMENDED THAT YOU CHECK THE STATUS OF THE POINTER
   *  IS IS VALID FOR A COMPONENT TO BE NULL AS THEY ARE OPTIONAL!
   *  @return a pointer to the objects sprite component (if any)
   */
  SpriteComponent* spriteComponent();
  void free();
  SpriteComponent* sprite_component = nullptr;
  void scalar(const float& multiplier);
  void resetScalar();
  void toggleVisable();
  void setPos(const Vector3& pos);
  void setOriginalPos(float xpos, float ypos);
  void setSize(Vector2 size);
  Vector3& getPos() { return pos; }

 private:
  bool hasScaled       = false;
  bool visabilty       = false;
  Vector2 original_pos = {0, 0};
  Vector3 pos          = {0, 0, 0};
};

#endif  // MYNETGAME_GAMEOBJECT_HPP
