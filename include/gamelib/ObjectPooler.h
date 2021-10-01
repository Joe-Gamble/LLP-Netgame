//
// Joe Gamble - 05/04/2020
//

#ifndef MYNETGAME_OBJECTPOOLER_H
#define MYNETGAME_OBJECTPOOLER_H

#include "GameObject.hpp"
#include "RenderData.h"

enum ObjectType
{
  Undefined = -1,  /// PreAllocate and empty non rendered object
  Scene_GO  = 0,   /// No Interaction with collision or UI
  UI_Object = 1    /// UI Interaction
};

class ObjectPool;

class SceneObject : public GameObject
{
 public:
  struct ObjectData
  {
    std::string filename = "undefined";
    std::string name     = "undefined";
    Vector3 pos          = {0, 0, 0};
    ObjectType type      = Undefined;
  };

  SceneObject()  = default;
  ~SceneObject() = default;

  virtual void init(
    ObjectPool* op,
    ASGE::Renderer* renderer,
    const std::string& fn,
    const std::string& n,
    Vector3 v3,
    Vector2 size);
  void updatePos(Vector3 newPos);

  ObjectData* getData() { return &data; }

 private:
  ObjectData data;
};

class InteractableObject : public SceneObject
{
 public:
  InteractableObject()  = default;
  ~InteractableObject() = default;

  void init(
    ObjectPool* op,
    ASGE::Renderer* renderer,
    const std::string& fn,
    const std::string& n,
    Vector3 v3,
    Vector2 size) override;
  Rect* setDetectionRadius(const Rect& newRect) { interaction_radius = newRect; }

 private:
  Rect interaction_radius = {this->getData()->pos};
};

struct ItemReference : public InteractableObject
{
  SceneObject* item = nullptr;
};

class ObjectPool
{
 public:
  ObjectPool() = default;
  explicit ObjectPool(RenderData* _rd) : _RD(_rd) {}
  ~ObjectPool() = default;

  void
  addObject(ObjectType object, const std::string& fn, const std::string& n, Vector3 p, Vector2 size);

  void addObject(SceneObject* object);
  void addRenderedObject(SceneObject* object);
  void addNewObject(std::reference_wrapper<SceneObject> object);
  void addObjects(const std::vector<SceneObject*>& _objects);

  void addEmptyObject(Vector3 p);
  void moveObject(ObjectPool* old_pool, SceneObject* object);

  void removeObject(SceneObject* object);
  void resetObjects();
  std::vector<std::reference_wrapper<SceneObject>>* getObjects();

 private:
  std::vector<std::reference_wrapper<SceneObject>> objects;
  RenderData* _RD = nullptr;
};

#endif  // MYNETGAME_OBJECTPOOLER_H
