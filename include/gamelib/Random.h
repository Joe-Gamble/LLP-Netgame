//
// Joe Gamble - 15/04/2020
// Global Random utility
//

#ifndef MYNETGAME_RANDOM_H
#define MYNETGAME_RANDOM_H

#include <random>

class Random
{
 public:
  Random();
  static void init() { s_random_engine.seed(std::random_device()()); }

  static float randomFloat()
  {
    return (float)s_distribution(s_random_engine) / (float)std::numeric_limits<uint32_t>::max();
  }

  template<typename Distribution>
  static typename Distribution::result_type
  getNumber(std::mt19937& random_engine, Distribution& distribution)
  {
    return distribution(random_engine);
  }

 private:
  static std::mt19937 s_random_engine;
  static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
};

#endif  // MYNETGAME_RANDOM_H
