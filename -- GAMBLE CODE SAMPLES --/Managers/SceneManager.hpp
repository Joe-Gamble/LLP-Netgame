// Joe Gamble 20/03/20
#ifndef MYNETGAME_SCENEMANAGER_HPP
#define MYNETGAME_SCENEMANAGER_HPP

#include "gamelib/Components/TileComponent.h"

#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/OGLGame.h>
#include <gamelib/Handlers/EnemyHandler.h>
#include <gamelib/Handlers/TurnHandler.h>
#include <gamelib/ObjectPooler.h>
#include <gamelib/Player/Entity.h>
#include <gamelib/RenderData.h>
#include <gamelib/Vector.hpp>
#include <memory>
#include <utility>
#include <vector>

enum SceneTypes
{
  UNDEFINED = -1,
  MENU      = 0,
  DUNGEON   = 1,
  MAP       = 2
};

struct CallbackData
{
  int click_callback_id  = -1;
  int key_callback_id    = -1;
  int mouse_callback_id  = -1;
  int scroll_callback_id = -1;
  bool input             = false;
};

class SceneManager;
class StateManager;

/**
 *  @brief Scene Object that contains all necessary components for the scene
 */
class Scene
{
 public:
  explicit Scene(RenderData* _RD) : objectPool(_RD), entities(_RD) {}
  ~Scene() = default;

  virtual void
  init(SceneManager* sceneManager, SceneTypes sceneType, int scene_id, const std::string& filename);
  virtual void render(RenderData* _RD);
  virtual void update(double dt);

  virtual void keyHandler(ASGE::SharedEventData data);
  virtual void clickHandler(ASGE::SharedEventData data);
  virtual void mouseHandler(ASGE::SharedEventData data);
  virtual void scrollHandler(ASGE::SharedEventData data);

  struct SceneProps
  {
    SceneTypes scene_type = UNDEFINED;
    int scene_id          = 0;
    std::string filename  = "";
    std::string name      = "";
  };

  void enableInput();
  void disableInput();
  void setPlayers(std::vector<std::unique_ptr<Player>>* _players);
  void removePlayers(std::vector<std::unique_ptr<Player>>* _players);

  SceneProps* getProps() { return &sceneProps; }
  CallbackData* getCallBacks() { return &callbacks; }
  GameObject* getBackground() { return &background; }
  ObjectPool* getObjectPool() { return &objectPool; }
  ObjectPool* getEntityPool() { return &entities; }
  SceneManager* getSceneManager() { return sceneManager; }
  std::vector<std::unique_ptr<Player>>* getPlayers() { return players; }

  void setSceneManager(SceneManager* _sceneManager) { sceneManager = _sceneManager; }

 private:
  SceneProps sceneProps;
  GameObject background;

  CallbackData callbacks;
  SceneManager* sceneManager                    = nullptr;
  std::vector<std::unique_ptr<Player>>* players = nullptr;

 protected:
  ObjectPool objectPool;
  ObjectPool entities;
};

class Menu : public Scene
{
 public:
  explicit Menu(RenderData* _RD) : Scene(_RD) {}
  ~Menu() = default;

  void render(RenderData* _RD) override;
  /*
    void init(SceneManager* sceneManager, SceneTypes sceneType, int scene_id, const std::string&
    filename) override; void render(ASGE::Renderer& renderer) override; void update(double dt)
    override;

    void mouseHandler(ASGE::SharedEventData data) override;
    void clickHandler(ASGE::SharedEventData data) override;
  */

 private:
};

class Dungeon : public Scene
{
 public:
  explicit Dungeon(RenderData* _RD) : Scene(_RD) {}
  ~Dungeon() = default;

  void initDungeon(
    ASGE::Renderer* renderer,
    TurnHandler* _turnHandler,
    const nlohmann::json& dungeon_data);
  void
  init(SceneManager* sceneManager, SceneTypes sceneType, int scene_id, const std::string& filename)
    override;
  void enterDungeon();
  void render(RenderData* _RD) override;
  void update(double dt) override;

  void keyHandler(ASGE::SharedEventData data) override;
  void mouseHandler(ASGE::SharedEventData data) override;
  void clickHandler(ASGE::SharedEventData data) override;
  void scrollHandler(ASGE::SharedEventData data) override;

  bool mouseInside(Player* player, Vector3& mouse_pos, float scalar);
  SceneObject* mouseOutside(Player* player, Vector3& mouse_pos);

  TileComponent* getTileComponent();
  TurnHandler* getTurnHandler()
  {
    if (turnHandler != nullptr)
    {
      return turnHandler;
    }
  }

 private:
  TileComponent tileComponent;
  EnemyHandler enemyHandler;
  TurnHandler* turnHandler = nullptr;
  std::string status       = "";
};

class Map : public Scene
{
  struct Location
  {
    Location(Scene* scene, int l_id, Vector2 p) : scene_ptr(scene), pos(std::move(p)), id(l_id) {}
    Scene* select() { return scene_ptr; }

    SceneObject preview;
    Scene* scene_ptr = nullptr;
    Vector2 pos;
    int id        = 0;
    bool selected = false;
  };

 public:
  explicit Map(RenderData* _RD) : Scene(_RD) {}
  ~Map() = default;

  void
  init(SceneManager* sceneManager, SceneTypes sceneType, int scene_id, const std::string& filename)
    override;

  void render(RenderData* _RD) override;
  void update(double dt) override;
  void addLocation(Scene* scene_ptr, Vector2& pos, int loc_id);

  void mouseHandler(ASGE::SharedEventData data) override;
  void clickHandler(ASGE::SharedEventData data) override;

  std::vector<Location>* getLocations() { return &locations; }

 private:
  std::vector<Location> locations;
};

/**
 *  @brief Scene Manager that stores data regarding the current gamestate
 */

class SceneManager
{
 public:
  SceneManager() = default;
  SceneManager(int num_of_scenes, ASGE::Input* _input);

  void addScene(RenderData* _RD, SceneTypes sceneType, const std::string& filename);
  bool switchScene(Scene* _scene);
  void setStateManager(StateManager* _state_manager) { stateManager = _state_manager; };
  std::vector<std::reference_wrapper<Scene>> getScenes();
  Scene* getCurrentScene();
  ASGE::Input* getInput() { return input; }

 private:
  std::vector<std::reference_wrapper<Scene>> scenes;
  int current_scene = 0;

  ASGE::Input* input         = nullptr;
  StateManager* stateManager = nullptr;
};

#endif  // MYNETGAME_SCENEMANAGER_HPP
