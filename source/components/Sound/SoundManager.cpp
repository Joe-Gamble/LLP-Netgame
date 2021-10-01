//
// Created by Tahir on 26/04/2020.
//

#include <gamelib/Sound/SoundManager.h>

void SoundManager::intSound()
{
  soloud_core.init();

  play_list = std::make_unique<PlayList>();

  play_list->intSound();
}

void SoundManager::playSound(Sound& sound)
{
  if (!sound.getSoundPlaying())
  {
    soloud_core.play(sound.playSource());
  }
}

void SoundManager::pauseAllSound(bool set_pause)
{
  soloud_core.setPauseAll(set_pause);

  // This checks to make sure you don't go
  // bellow or over the parameters for the function

  playing_global_sound = !set_pause;

  paused_all_sound = set_pause;
}

void SoundManager::changeSound(Sound& sound)
{
  if (sound.getSoundStopped())
  {
    stopAllSound();

    soloud_core.play(sound.playSource());
  }
}

void SoundManager::changeSound(Sound& sound, Sound& sound_to_play)
{
  if (!sound_to_play.getSoundPlaying())
  {
    sound.stopSound();

    soloud_core.play(sound_to_play.playSource());
  }

  if (paused_all_sound)
  {
    paused_all_sound = false;
  }
}

void SoundManager::changeVolumeAll(float volume)
{
  soloud_core.setGlobalVolume(volume);

  // Checks if sound isn't too low or too high

  // volume < 0
  if (soloud_core.getGlobalVolume() < 0)
  {
    soloud_core.setGlobalVolume(0);
  }

  // volume > 1
  if (soloud_core.getGlobalVolume() > 1)
  {
    soloud_core.setGlobalVolume(1);
  }
}

void SoundManager::stopAllSound()
{
  soloud_core.stopAll();

  play_list->menu_sound.setSourcePlaying(false);
  play_list->map1_sound.setSourcePlaying(false);
  play_list->map2_sound.setSourcePlaying(false);
  play_list->map3_sound.setSourcePlaying(false);

  playing_global_sound = false;
  paused_all_sound     = false;
}

void SoundManager::stopSoundSource(Sound& sound)
{
  sound.stopSound();
}

bool SoundManager::getGlobalPlaying()
{
  playing_global_sound = getSoloudEngine().getActiveVoiceCount() != 0;

  return playing_global_sound;
}

bool SoundManager::getGlobalPaused() const
{
  return paused_all_sound;
}

bool SoundManager::getGlobalStop() const
{
  return !playing_global_sound;
}

float SoundManager::getGlobalVolume()
{
  return soloud_core.getGlobalVolume();
}

PlayList* SoundManager::getPlayList()
{
  return play_list.get();
}

SoLoud::Soloud SoundManager::getSoloudEngine()
{
  return soloud_core;
}

void SoundManager::deInt()
{
  // clean-up
  soloud_core.deinit();
}