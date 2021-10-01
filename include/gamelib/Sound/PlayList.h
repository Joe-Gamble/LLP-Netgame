//
// Created by Tahir on 27/04/2020.
//

#ifndef MYNETGAME_PLAYLIST_H
#define MYNETGAME_PLAYLIST_H

#include "Sound.h"

class PlayList
{
 public:
  PlayList()  = default;
  ~PlayList() = default;

  void intSound();

  Sound menu_sound;

  Sound map1_sound;
  Sound map2_sound;
  Sound map3_sound;

 private:
  const float BACKGROUND_VOLUME = 1;
};

#endif  // MYNETGAME_PLAYLIST_H
