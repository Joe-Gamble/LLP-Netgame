//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_UIPANEL_H
#define MYNETGAME_UIPANEL_H

#include "gamelib/UISystem/UIObject.h"

/// A collapsable

class UIPanel : public UIObject
{
 public:
  UIPanel();

  void update(GameData* _GD) override;
  void render(RenderData* _RD) override;

  void onMouseOver() override;
  void onMouseOut() override;
  void onMouseClick() override;

 private:
  std::vector<UIObject*> contained;
};

#endif  // MYNETGAME_UIPANEL_H
