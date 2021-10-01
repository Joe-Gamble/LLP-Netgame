//
// Created by miles on 05/04/2020.
//

#ifndef MYNETGAME_UITEXTBOX_H
#define MYNETGAME_UITEXTBOX_H
#include "gamelib/UISystem/UIObject.h"
#include "string"

#include <mutex>

enum TextBoxType
{
  NONE,
  INPUT_,
  OUTPUT
};

class UITextBox : public UIObject
{
 public:
  UITextBox() = default;

  UITextBox(float x, float y, float w, float h, std::string& texture, UIManager* _UIM, int _type);

  ~UITextBox() override = default;

  void update(GameData* _GD) override;
  void render(RenderData* _RD) override;

  void onMouseOver() override;
  void onMouseOut() override;
  void onMouseClick() override;

  void displayNewMsg(std::string msg);
  void addToInput(char key);
  void delFromInput();
  void clearInput() { text = ""; };

  std::string getText() { return text; };
  void setCharSize(int size) { char_size = size; };

 protected:
  std::string text;
  std::string last_received;
  bool input_active = false;

  std::mutex mut_ex;

  int char_size = 35;
  int type      = NONE;
};

#endif  // MYNETGAME_UITEXTBOX_H
