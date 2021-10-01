//
// Joe Gamble 21/04/20
//

#include <../apps/ASGEGame/Managers/SceneManager.hpp>

void Map::init(
  SceneManager* _sceneManager,
  SceneTypes sceneType,
  int scene_id,
  const std::string& filename)
{
  this->setSceneManager(_sceneManager);
  this->getProps()->scene_type = sceneType;
  this->getProps()->scene_id   = scene_id;
  this->getProps()->filename   = filename;
}

void Map::addLocation(Scene* scene_ptr, Vector2& pos, int loc_id)
{
  Location new_loc = Location(scene_ptr, loc_id, pos);
  locations.push_back(new_loc);
}

void Map::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());

  if (click->action == ASGE::MOUSE::BUTTON_PRESSED)
  {
    for (auto& current : *getLocations())
    {
      if (current.selected)
      {
        getSceneManager()->switchScene(current.select());
      }
    }
  }
}

void Map::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  float scalar      = 1.25F;

  for (auto& current : *getLocations())
  {
    Vector3 mouse_pos = {float(mouse->xpos), float(mouse->ypos), 0};
    if (!current.selected)
    {
      if (current.preview.spriteComponent()->getBoundingBox().isInside(mouse_pos))
      {
        current.preview.scalar(scalar);
        current.selected = true;
      }
    }
    else if (!(current.preview.spriteComponent()->getBoundingBox().isInside(mouse_pos)))
    {
      current.preview.resetScalar();
      current.selected = false;
    }
  }
}

void Map::render(RenderData* _RD)
{
  _RD->p_renderer->renderSprite(*this->getBackground()->spriteComponent()->getSprite());

  for (auto& object : *getObjectPool()->getObjects())
  {
    if (object.get().getData()->type != ObjectType::Undefined)
    {
      _RD->p_renderer->renderSprite(*object.get().spriteComponent()->getSprite());
    }
  }
}

void Map::update(double dt) {}