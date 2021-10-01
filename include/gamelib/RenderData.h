//
// Created by miles on 28/03/2020.
//

#ifndef MYNETGAME_RENDERDATA_H
#define MYNETGAME_RENDERDATA_H
//#include "Renderer.h"
#include <Engine/OGLGame.h>

/// Reference to be sent to all GammeObjets for Render() methods outside game.cpp

struct RenderData
{
  ASGE::Renderer* p_renderer;
};

#endif  // MYNETGAME_RENDERDATA_H
