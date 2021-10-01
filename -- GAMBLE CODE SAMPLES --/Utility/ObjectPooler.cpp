//
// Created by joemi on 05/04/2020.
//

#include "gamelib/ObjectPooler.h"

/*
ObjectPool::ObjectPool(ASGE::Renderer* renderer)
{

}

 */

std::vector<std::reference_wrapper<SceneObject>>* ObjectPool::getObjects()
{
  return &objects;
}

void ObjectPool::addObject(
  ObjectType object,
  const std::string& fn,
  const std::string& n,
  Vector3 p,
  Vector2 size)
{
  switch (object)
  {
  case ObjectType::Undefined:
  {
    addEmptyObject(p);
    return;
  }
  case ObjectType::Scene_GO:
  {
    auto* scene_go            = new SceneObject();
    scene_go->getData()->type = object;
    scene_go->init(this, _RD->p_renderer, fn, n, p, size);
    break;
  }
  case ObjectType::UI_Object:
  {
    auto* ui_object            = new InteractableObject();
    ui_object->getData()->type = object;
    ui_object->init(this, _RD->p_renderer, fn, n, p, size);
    break;
  }
  default:
  {
    return;
  }
  }

  if (objects.back().get().getData()->type == UI_Object)
  {
    auto* i = dynamic_cast<InteractableObject*>(&objects.back().get());
    // i->setDetectionRadius({{p},0, 0});
  }
}

void ObjectPool::addObjects(const std::vector<SceneObject*>& _objects)
{
  for (auto i : _objects) { addObject(i); }
}

void ObjectPool::addRenderedObject(SceneObject* object)
{
  object->instantiate(_RD->p_renderer, object->getData()->filename);
  objects.emplace_back(*object);
}

void ObjectPool::addObject(SceneObject* object)
{
  objects.emplace_back(*object);
}

void ObjectPool::addNewObject(std::reference_wrapper<SceneObject> object)
{
  auto* ref_object = new ItemReference();
  ref_object->init(
    this,
    _RD->p_renderer,
    object.get().getData()->filename,
    object.get().getData()->name,
    object.get().getData()->pos,
    {50, 50});
  ref_object->item = &object.get();
  objects.emplace_back(*ref_object);
}

void ObjectPool::resetObjects()
{
  if (!objects.empty())
  {
    for (auto& o : objects) { o.get().resetScalar(); }
  }
}

void ObjectPool::moveObject(ObjectPool* old_pool, SceneObject* object)
{
  addObject(object);
  old_pool->removeObject(object);
}

void ObjectPool::addEmptyObject(Vector3 p)
{
  auto* undefined_object = new SceneObject();

  undefined_object->getData()->type = ObjectType::Undefined;
  objects.emplace_back(*undefined_object);
}

void ObjectPool::removeObject(SceneObject* object)
{
  if (!objects.empty())
  {
    int ob_id = 0;
    for (auto& o : objects)
    {
      SceneObject* ob = &o.get();
      if (object == ob)
      {
        objects.erase(objects.begin() + ob_id);
      }
      ob_id++;
    }
  }
}

void SceneObject::init(
  ObjectPool* op,
  ASGE::Renderer* renderer,
  const std::string& fn,
  const std::string& n,
  Vector3 v3,
  Vector2 size)
{
  this->getData()->pos      = v3;
  this->getData()->filename = fn;
  this->getData()->name     = n;
  this->getData()->type     = ObjectType::Scene_GO;
  instantiate(renderer, fn, v3.x, v3.y, size.x, size.y);
  this->setSize(size);
  op->addObject(this);
}

void InteractableObject::init(
  ObjectPool* op,
  ASGE::Renderer* renderer,
  const std::string& fn,
  const std::string& n,
  Vector3 v3,
  Vector2 size)
{
  this->getData()->pos      = v3;
  this->getData()->filename = fn;
  this->getData()->name     = n;
  this->getData()->type     = ObjectType ::UI_Object;
  instantiate(renderer, fn, v3.x, v3.y, size.x, size.y);
  op->addObject(this);
}

void SceneObject::updatePos(Vector3 newPos)
{
  this->getData()->pos = newPos;
}
