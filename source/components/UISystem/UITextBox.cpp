//
// Created by miles on 05/04/2020.
//

#include "gamelib/UISystem/UITextBox.h"

UITextBox::UITextBox(
  float x,
  float y,
  float w,
  float h,
  std::string& texture,
  UIManager* _UIM,
  int _type)
{
  properties = new UiProperties(x, y, w, h, texture);
  type       = _type;
  ui_manager = _UIM;
}

void UITextBox::update(GameData* _GD)
{
  switch (type)
  {
  case INPUT_:
  {
    INPUT_;
    break;
  }
  case OUTPUT:
  {
    OUTPUT;
    break;
  }
  }
}

void UITextBox::render(RenderData* _RD)
{
  switch (type)
  {
  case INPUT_:
  {
    _RD->p_renderer->renderSprite(*spriteComponent()->getSprite());
    _RD->p_renderer->renderText(
      text, int(properties->m_x), int(properties->m_y + 25), ASGE::COLOURS::BLACK);

    if (text.size() > 35)
    {
      _RD->p_renderer->renderText(
        "Max characters reached",
        int(properties->m_x),
        int(properties->m_y) + 40,
        ASGE::COLOURS::BLACK);
      input_active = false;
    }
    break;
  }
  case OUTPUT:
  {
    _RD->p_renderer->renderSprite(*spriteComponent()->getSprite());
    _RD->p_renderer->renderText(
      text, int(properties->m_x), int(properties->m_y + 25), ASGE::COLOURS::BLACK);
    break;
  }
  }
}

void UITextBox::onMouseOver() {}

void UITextBox::onMouseOut() {}

void UITextBox::onMouseClick() {}

void UITextBox::delFromInput()
{
  if (!text.empty())
  {
    text.erase(text.size() - 1);
  }
}

void UITextBox::addToInput(char key)
{
  if (text.size() < 36)
  {
    text += key;
  }
}

void UITextBox::displayNewMsg(std::string msg)
{
  mut_ex.lock();
  if (last_received != msg)
  {
    text.push_back('\n');

    if (msg.size() > char_size)
    {
      for (int i = 0; i < char_size; i++) { text.push_back(msg[i]); }
      text.push_back('\n');
      for (int i = 0; i < (msg.size() - char_size); i++) { text.push_back(msg[char_size + i]); }
    }

    text += msg;
    last_received = msg;
  }
  mut_ex.unlock();
}
