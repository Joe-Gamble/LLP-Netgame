//
// Created by Tahir on 26/04/2020.
//

#ifndef MYNETGAME_SOUNDMANAGER_H
#define MYNETGAME_SOUNDMANAGER_H

#include "PlayList.h"
#include "Sound.h"
#include "soloud.h"

#include <Engine/FileIO.h>

class SoundManager
{
 public:
  SoundManager()  = default;
  ~SoundManager() = default;

  void intSound();
  void playSound(Sound& sound);

  /// if int set_pause 0 then sound will play
  /// if int set_pause 1 the sound will be paused
  void pauseAllSound(bool set_pause);

  // This function stops all sound then plays the new sound
  void changeSound(Sound& sound);

  // Ths function stops a specific type of sound and play the new sound
  void changeSound(Sound& sound_playing, Sound& sound_to_play);

  void changeVolumeAll(float volume);
  // void changeSourceVolume(float volume);

  // stop sounds
  void stopAllSound();
  void stopSoundSource(Sound& sound);

  // Global
  bool getGlobalPlaying();
  [[nodiscard]] bool getGlobalPaused() const;
  [[nodiscard]] bool getGlobalStop() const;
  float getGlobalVolume();

  PlayList* getPlayList();

  SoLoud::Soloud getSoloudEngine();

  void deInt();

 private:
  SoLoud::Soloud soloud_core;  // SoLoud engine core

  std::unique_ptr<PlayList> play_list;

  bool playing_global_sound = false;
  bool paused_all_sound     = false;
};

#endif  // MYNETGAME_SOUNDMANAGER_H
