//
// Joe Gamble 22/03/20 - credit to James Huxtable for the original code form last year
// Iterated over many projects for different requirements by Joe Gamble.
//

#ifndef MYNETGAME_SPRITECOMPONENT_HPP
#define MYNETGAME_SPRITECOMPONENT_HPP

#include <Engine/Game.h>
#include <Engine/Sprite.h>
#include <gamelib/Rect.hpp>
#include <gamelib/Vector.hpp>

class SpriteComponent
{
 public:
  /**
   *  Default constructor.
   */
  SpriteComponent() = default;

  /// Clang Tidy destructor issue work-around
  SpriteComponent(SpriteComponent const&) = default;
  SpriteComponent& operator=(SpriteComponent const&) = default;
  SpriteComponent(SpriteComponent&&)                 = default;
  SpriteComponent& operator=(SpriteComponent&&) = default;

  /**
   *  Destructor. Frees dynamic memory.
   */
  ~SpriteComponent();

  /**
   *  Allocates and loads the sprite.
   *  Part of this process will attempt to load a texture file.
   *  If this fails this function will return false and the memory
   *  allocated, freed.
   *  @param [in] renderer The renderer used to perform the allocations
   *  @param [in] texture_file_name The file path to the the texture to load
   *  @return true if the sprite was successfully loaded
   */
  bool loadSprite(ASGE::Renderer* renderer, const std::string& texture_file_name);

  bool loadSprite(
    ASGE::Renderer* renderer,
    const std::string& texture_file_name,
    const Vector2& coords,
    float width,
    float height);

  /**
   *  Returns a pointer to the sprite residing in this component.
   *  As this is a pointer, you will need to check its contents before
   *  attempting to read from it. A simple nullptr will be solve this.
   *  @return a pointer to the objects sprite (if any)
   */
  ASGE::Sprite* getSprite();

  /**
   *  Grabs a bounding box for the sprite.
   *  Will create a bounding box as a rectangle. This can be used to check
   *  for collisions with other rects.
   *  @return a rectangle represent the sprite's position and bounds.
   */
  [[nodiscard]] Rect getBoundingBox() const;

 private:
  void free();
  ASGE::Sprite* sprite = nullptr;
};
#endif  // MYNETGAME_SPRITECOMPONENT_HPP
