//
// Created by Tahir on 04/04/2020.
//

#ifndef MYNETGAME_SOUND_H
#define MYNETGAME_SOUND_H

#include "soloud.h"

#include <Engine/FileIO.h>
#include <soloud_wav.h>

class Sound
{
 public:
  Sound()  = default;
  ~Sound() = default;

  void intSound(float volume, bool loop, const std::string& path);

  // This function activates the bool playing_sound
  SoLoud::Wav& playSource();

  // Call this after the sound you what the sound to be off
  void stopSound();

  void setSourcePlaying(bool set_state);

  bool getSoundPlaying();
  bool getSoundStopped();

  SoLoud::Wav& getSource();

 private:
  SoLoud::Wav source;  // Sound source

  bool play_sound = false;  // bool for the source being stopped
};

#endif  // MYNETGAME_SOUND_H
