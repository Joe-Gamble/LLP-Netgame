// Joe Gamble - 20/03/20

#include "SceneManager.hpp"
//#include <gamelib/StateSystem/StateManager.h>
#include <Engine/Logger.hpp>
#include <gamelib/RenderData.h>
#include <gamelib/StateSystem/State.hpp>
#include <memory>

/**
 * SCENE MANAGER CODE
 * All code for necessary functions go here
 */
SceneManager::SceneManager(const int num_of_scenes, ASGE::Input* _input) : input(_input)
{
  scenes.reserve(num_of_scenes);
}

void SceneManager::addScene(RenderData* _RD, SceneTypes sceneType, const std::string& filename)
{
  switch (sceneType)
  {
  case SceneTypes::MENU:
  {
    // add a map scene
    Scene* menu_scene = new Menu(_RD);
    menu_scene->init(this, MENU, scenes.size(), filename);
    scenes.emplace_back(*menu_scene);
    break;
  }
  case SceneTypes::DUNGEON:
  {
    // add a dungeon scene
    Scene* dungeon_scene = new Dungeon(_RD);
    dungeon_scene->init(this, DUNGEON, scenes.size(), filename);
    scenes.emplace_back(*dungeon_scene);
    break;
  }
  case SceneTypes::MAP:
  {
    // add a map scene
    Scene* map_scene = new Map(_RD);
    map_scene->init(this, MAP, scenes.size(), filename);
    scenes.emplace_back(*map_scene);
    break;
  }
  default: break;
  }
}

bool SceneManager::switchScene(Scene* _scene)
{
  Scene* old_scene = getCurrentScene();
  current_scene    = _scene->getProps()->scene_id;

  if (old_scene != nullptr)
  {
    getCurrentScene()->setPlayers(old_scene->getPlayers());
    old_scene->disableInput();
    old_scene->removePlayers(old_scene->getPlayers());
  }
  if (getCurrentScene()->getProps()->scene_type == SceneTypes::DUNGEON)
  {
    auto* dungeon = dynamic_cast<Dungeon*>(_scene);
    dungeon->enterDungeon();
    Logging::INFO("test");
  }
  getCurrentScene()->enableInput();
  stateManager->getCurrentState()->setScene(getCurrentScene());
}

void Scene::removePlayers(std::vector<std::unique_ptr<Player>>* _players)
{
  if (_players != nullptr)
  {
    for (auto& player : *getPlayers()) { entities.removeObject(player.get()); }
    players = nullptr;
  }
}

void Scene::setPlayers(std::vector<std::unique_ptr<Player>>* _players)
{
  if (_players != nullptr)
  {
    players = _players;
    for (auto& player : *getPlayers()) { entities.addObject(player.get()); }
  }
}

std::vector<std::reference_wrapper<Scene>> SceneManager::getScenes()
{
  return scenes;
}

Scene* SceneManager::getCurrentScene()
{
  return &scenes.at(current_scene).get();
}

/**
 * @brief Scene Initialization
 * @param
 * All code for necessary functions go here
 */

void Scene::init(
  SceneManager* _sceneManager,
  SceneTypes sceneType,
  int scene_id,
  const std::string& filename)
{
  this->setSceneManager(_sceneManager);
  this->sceneProps.scene_type = sceneType;
  this->sceneProps.scene_id   = scene_id;
  this->sceneProps.filename   = filename;
}

/**
 * @brief Enable Input for scene
 * @param ASGE Input
 */

void Scene::enableInput()
{
  if (sceneManager->getInput() != nullptr)
  {
    if (!getCallBacks()->input)
    {
      ASGE::Input* input = sceneManager->getInput();
      getCallBacks()->mouse_callback_id =
        input->addCallbackFnc(ASGE::E_MOUSE_MOVE, &Scene::mouseHandler, this);
      getCallBacks()->key_callback_id =
        input->addCallbackFnc(ASGE::E_KEY, &Scene::keyHandler, this);
      getCallBacks()->click_callback_id =
        input->addCallbackFnc(ASGE::E_MOUSE_CLICK, &Scene::clickHandler, this);
      getCallBacks()->scroll_callback_id =
        input->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &Scene::scrollHandler, this);
      getCallBacks()->input = true;
    }
  }
}

/**
 * @brief Disable Input for scene - for some reason I have to call them twice?
 * @param ASGE Input
 */

void Scene::disableInput()
{
  if (sceneManager->getInput() != nullptr)
  {
    if (getCallBacks()->input)
    {
      ASGE::Input* input = sceneManager->getInput();
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->key_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->mouse_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->click_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->scroll_callback_id));

      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->key_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->mouse_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->click_callback_id));
      input->unregisterCallback(static_cast<unsigned int>(getCallBacks()->scroll_callback_id));

      input->setCursorMode(ASGE::MOUSE::CursorMode::NORMAL);
      getObjectPool()->resetObjects();
      getCallBacks()->input = false;
    }
  }
}

void Scene::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
}

void Scene::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());
}

void Scene::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
}

void Scene::scrollHandler(ASGE::SharedEventData data)
{
  const auto* scroll = dynamic_cast<const ASGE::ScrollEvent*>(data.get());
  Logging::INFO(std::to_string(scroll->yoffset));
}

void Scene::render(RenderData* _RD)
{
  _RD->p_renderer->renderSprite(*this->background.spriteComponent()->getSprite());
  for (auto& object : *getObjectPool()->getObjects())
  {
    if (object.get().getData()->type != ObjectType::Undefined)
    {
      _RD->p_renderer->renderSprite(*object.get().spriteComponent()->getSprite());
    }
  }
}

void Menu::render(RenderData* _RD)
{
  _RD->p_renderer->renderSprite(*this->getBackground()->spriteComponent()->getSprite());
  _RD->p_renderer->renderText("PRESS M TO MUTE SOUND", 200, 200, ASGE::COLOURS::BLACK);
  _RD->p_renderer->renderText("PRESS G TO SWITCH SCENE", 200, 400, ASGE::COLOURS::BLACK);
}

void Scene::update(double dt)
{
  // Logging::INFO(std::to_string(this->getObjectPool()->getObjects()->size()));
}
