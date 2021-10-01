//
// Created by Tahir on 04/04/2020.
//

#include <gamelib/Sound/Sound.h>

void Sound::intSound(float volume, bool loop, const std::string& path)
{
  ASGE::FILEIO::File file1;
  if (file1.open(path))
  {
    auto io_buffer = file1.read();
    source.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }

  source.setVolume(volume);
  source.setLooping(loop);
}

SoLoud::Wav& Sound::playSource()
{
  play_sound = true;

  return source;
}

void Sound::stopSound()
{
  play_sound = false;
  source.stop();
}

void Sound::setSourcePlaying(bool set_state)
{
  play_sound = set_state;
}

bool Sound::getSoundPlaying()
{
  return play_sound;
}

bool Sound::getSoundStopped()
{
  return !play_sound;
}

SoLoud::Wav& Sound::getSource()
{
  return source;
}