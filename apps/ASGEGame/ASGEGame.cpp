#include "ASGEGame.hpp"

#include <Engine/FileIO.h>
#include <Engine/Logger.hpp>

/// Initialises the game.
/// Setup your game and initialise the core components.
/// @param settings
Game::Game(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  key_callback_id        = inputs->addCallbackFnc(ASGE::E_KEY, &Game::keyHandler, this);
  mouse_callback_id      = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &Game::clickHandler, this);
  mouse_move_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_MOVE, &Game::mouseHandler, this);

  inputs->use_threads = true;
  toggleFPS();
  renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
  /// GD & RD Initialisation
  m_GD       = new GameData;
  m_GD->m_gs = GS_START_UP;

  m_RD             = new RenderData;
  m_RD->p_renderer = renderer.get();

  /// State Manager Initialisation
  stateManager = std::make_unique<StateManager>(m_GD, m_RD, inputs.get());
  stateManager->init();

  gameManager = std::make_unique<GameManager>(m_RD, inputs.get());
  gameManager->getSceneManager()->setStateManager(stateManager.get());

  gameManager->getSceneManager()->switchScene(
    &gameManager->getSceneManager()->getScenes().at(0).get());
  gameManager->addPlayer(m_RD);
  netCommunicator = std::make_unique<NetworkCommunicator>();

  game_components.emplace_back(new GCNetServer(netCommunicator->getSelf()));
  game_components.emplace_back(new GCNetClient(netCommunicator->getSelf()));

  auto* p_client = dynamic_cast<GCNetClient*>(game_components[1]);
  netCommunicator->init(p_client, gameManager->getSelf(), stateManager->getSelf());
  stateManager->setNetCom(netCommunicator->getSelf());

  soundManager = std::make_unique<SoundManager>();
  soundManager->intSound();
  soundManager->playSound(soundManager->getPlayList()->menu_sound);
  gameManager->getPlayer(1)->addItem(ItemType::WEAPON, 1);
  gameManager->getPlayer(1)->addItem(ItemType::UTILITY, 1);
}

/// Destroys the game.
Game::~Game()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_callback_id));

  this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_move_callback_id));
  delete m_GD;
  m_GD = nullptr;
}

/// Processes key inputs.
/// This function is added as a callback to handle the game's
/// keyboard input. For this game, calls to this function
/// are not thread safe, so you may alter the game's state
/// but your code needs to designed to prevent data-races.
/// @param data
/// @see KeyEvent
void Game::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  m_GD->setKD(key);

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    // soundManager->stopAllSound();
    // soundManager->deInt();
    signalExit();
  }

  if (key->key == ASGE::KEYS::KEY_J && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    gameManager->getPlayer(1)->addItem(WEAPON, 1);
  }

  if (key->key == ASGE::KEYS::KEY_M && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    soundManager->pauseAllSound(true);
  }

  if (key->key == ASGE::KEYS::KEY_K && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    gameManager->getPlayer(1)->addItem(UTILITY, 1);
  }

  if (key->key == ASGE::KEYS::KEY_G && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    gameManager->getSceneManager()->switchScene(
      &gameManager->getSceneManager()
         ->getScenes()
         .at(gameManager->getSceneManager()->getCurrentScene()->getProps()->scene_id + 1)
         .get());
  }

  if (key->key == ASGE::KEYS::KEY_C && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    int a = 24;
    int c = 9;
    int d = 99;
    int f = 999;
    int e = 9999;

    char* b = reinterpret_cast<char*>(&a);
    Logging::DEBUG("Casting int 24  to string = " + std::to_string(a) + " / to char = " + b);
    Logging::DEBUG(
      "size of ints: 9 = " + std::to_string(sizeof(c)) + ", 99 = " + std::to_string(sizeof(d)) +
      ", 999 = " + std::to_string(sizeof(f)) + ", 9999 = " + std::to_string(sizeof(e)));
    netCommunicator->serializeMessage({11, 23, 45, 700, 9999});
    netCommunicator->serializeMessage({1, 2, 3, 4, 5});
  }

  if (key->key == ASGE::KEYS::KEY_H && key->action == ASGE::KEYS::KEY_PRESSED)
  {
    gameManager->getTurnHandler()->nextTurn();
    // Logging::INFO(std::to_string(gameManager->getTurnHandler()->getCurrentTurn()));
  }
}
void Game::clickHandler(ASGE::SharedEventData data)
{
  const auto* const click = dynamic_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;
}

void Game::mouseHandler(ASGE::SharedEventData data)
{
  const auto* const mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
}

/// Updates your game and all it's components.
/// @param us
void Game::update(const ASGE::GameTime& us)
{
  for (auto& gc : game_components) { gc->update(us.deltaInSecs()); }
  m_GD->m_dt = us.deltaInSecs();
  stateManager->updateState(m_GD);
}

/// Render your game and its scenes here.
void Game::render()
{
  m_RD->p_renderer = renderer.get();
  /// scene render function
  stateManager->drawState(m_RD);
}
