//
// Joe Gamble - 26/03/20
//
#include "GameManager.h"

GameManager::GameManager(RenderData* _RD, ASGE::Input* _input)
{
  game_data = init("Json/Gamedata");

  /// SCENE SETUP

  int scenes   = game_data["Game"]["NumberOfScenes"].get<int>();
  sceneManager = SceneManager(scenes, _input);

  for (int i = 0; i < scenes; i++)
  {
    nlohmann::json scene_data = game_data["Game"]["Scenes"][i];

    auto filename = scene_data["background"]["sprite"].get<std::string>();
    auto type     = SceneTypes(scene_data["type"].get<int>());

    sceneManager.addScene(_RD, type, filename);

    auto* scene = dynamic_cast<Scene*>(&sceneManager.getScenes().at(i).get());

    scene->getBackground()->instantiate(_RD->p_renderer, scene->getProps()->filename);
    Vector2 size = {scene_data["background"]["size"]["size_x"].get<float>(),
                    scene_data["background"]["size"]["size_y"].get<float>()};
    scene->getBackground()->setSize(size);

    int scene_objects = game_data["Game"]["Scenes"][i]["NumberOfObjects"].get<int>();

    for (int j = 0; j < scene_objects; j++)
    {
      nlohmann::json object_data = game_data["Game"]["Scenes"][i]["Objects"][j];

      int obj_type = object_data["type"].get<int>();

      auto filename = object_data["filename"].get<std::string>();
      auto name     = object_data["name"].get<std::string>();

      nlohmann::json sprite_data = object_data["sprite"];

      Vector2 size = {sprite_data["width"].get<float>(), sprite_data["height"].get<float>()};

      Vector3 object_pos = {sprite_data["x"].get<float>(),
                            sprite_data["y"].get<float>(),
                            sprite_data["z"].get<float>()};

      scene->getObjectPool()->addObject(ObjectType(obj_type), filename, name, object_pos, size);
      scene->getObjectPool()->getObjects()->back().get().setSize(size);
    }
  }

  /// SCENE SPECIFIC CODE
  for (auto& scene : sceneManager.getScenes())
  {
    /// MAP
    if (scene.get().getProps()->scene_type == SceneTypes::MAP)
    {
      auto* map =
        dynamic_cast<Map*>(&sceneManager.getScenes().at(scene.get().getProps()->scene_id).get());

      nlohmann::json map_info =
        game_data["Game"]["Scenes"][scene.get().getProps()->scene_id]["map_params"];

      int locations = map_info["NumberOfLocations"].get<int>();

      for (int j = 0; j < locations; j++)
      {
        int scene_ptr = map_info["locations"][j]["scene"].get<int>();
        Vector2 pos   = {map_info["locations"][j]["x"].get<float>(),
                       map_info["locations"][j]["y"].get<float>()};

        Scene* target = &sceneManager.getScenes().at(scene_ptr).get();
        map->addLocation(target, pos, scene_ptr);
      }

      for (auto& loc : *map->getLocations())
      {
        loc.preview.init(
          map->getObjectPool(),
          _RD->p_renderer,
          loc.scene_ptr->getProps()->filename,
          loc.scene_ptr->getProps()->name,
          {loc.pos.x, loc.pos.y, 0},
          {50, 50});
      }
    }
    else if (scene.get().getProps()->scene_type == SceneTypes::DUNGEON)
    {
      /// DUNGEON
      auto* dungeon = dynamic_cast<Dungeon*>(&sceneManager.getScenes().back().get());

      nlohmann::json dungeon_data =
        game_data["Game"]["Scenes"][scene.get().getProps()->scene_id]["dungeon_params"];
      dungeon->initDungeon(_RD->p_renderer, &turnHandler, dungeon_data);

      Logging::INFO("test");
    }
  }
}

nlohmann::json GameManager::init(const std::string& file_name)
{
  using File = ASGE::FILEIO::File;
  File file  = File();

  if (file.open(file_name + ".json"))
  {
    // load the file into a buffer object and convert into string
    using Buffer  = ASGE::FILEIO::IOBuffer;
    Buffer buffer = file.read();

    // parse the loaded string, you could
    nlohmann::json g_data =
      nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);

    file.close();
    return g_data;
  }
  Logging::ERRORS("Could not open file");
}

void GameManager::addPlayer(RenderData* _RD)
{
  /// PLAYER SETUP
  int player_id              = players.size();
  nlohmann::json player_data = game_data["Game"]["Players"]["player_data"][player_id];

  players.emplace_back(std::make_unique<Player>(_RD, player_id + 1, player_data));

  Player* player          = players.back().get();
  player->getData()->name = "player " + player_id;

  player->instantiate(_RD->p_renderer, player->getData()->filename, 0, 0, 50, 50);

  /// PLAYER SPRITE ELEMENTS
  nlohmann::json elements = game_data["Game"]["Players"]["screen_sprites"];
  int num_sprites         = elements["NumberOfSprites"].get<int>();

  for (int i = 0; i < num_sprites; i++)
  {
    nlohmann::json element_data = elements["sprites"][i];

    auto fn   = element_data["filename"].get<std::string>();
    auto name = element_data["name"].get<std::string>();

    Vector3 pos  = {element_data["sprite"]["x"].get<float>(),
                   element_data["sprite"]["y"].get<float>(),
                   element_data["sprite"]["z"].get<float>()};
    Vector2 size = {element_data["sprite"]["width"].get<float>(),
                    element_data["sprite"]["height"].get<float>()};

    player->getElements()->addObject(ObjectType(1), fn, name, pos, size);
    player->getElements()->getObjects()->back().get().setSize(size);
  }

  /// WHY DOESN'T THIS INSTANTIATE IN THE PLAYER CONSTRUCTOR???
  for (auto& current_slot : *player->getInventory()->getSlots())
  {
    current_slot.instantiate(
      _RD->p_renderer, "slot.png", current_slot.getSlotPos().x, current_slot.getSlotPos().y, 80, 80);
    current_slot.spriteComponent()->getSprite()->colour(ASGE::COLOURS::BLACK);
  }
  int bag_level = player_data["inventory"]["bag"]["level"].get<int>();

  player->getInventory()->setBagLevel(bag_level);
  sceneManager.getCurrentScene()->setPlayers(&players);
}
