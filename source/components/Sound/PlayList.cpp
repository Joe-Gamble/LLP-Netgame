//
// Created by Tahir on 27/04/2020.
//

#include <gamelib/Sound/PlayList.h>
void PlayList::intSound()
{
  // Menu
  menu_sound.intSound(BACKGROUND_VOLUME, true, "/data/sound/Background/Infint.mp3");

  // Map sounds
  map1_sound.intSound(BACKGROUND_VOLUME, true, "/data/sound/Background/Map1Sound.mp3");
  map2_sound.intSound(BACKGROUND_VOLUME, true, "/data/sound/Background/Map2Sound.mp3");
  map3_sound.intSound(BACKGROUND_VOLUME, true, "/data/sound/Background/Map3Sound.mp3");
}
