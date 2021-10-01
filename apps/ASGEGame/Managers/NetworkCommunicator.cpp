//
// Created by miles on 27/04/2020.
//

#include "NetworkCommunicator.h"

#include "gamelib/Components/GCNetClient.hpp"
#include "gamelib/StateSystem/State.hpp"
#include "gamelib/StateSystem/StateManager.h"
#include "gamelib/UISystem/UIManager.h"
#include "gamelib/UISystem/UITextBox.h"

#include <Engine/Logger.hpp>

void NetworkCommunicator::debugPrint(const std::string& str)
{
  mut_ex.lock();
  Logging::DEBUG("] ---- " + str);
  mut_ex.unlock();
}

void NetworkCommunicator::init(GCNetClient* _client, GameManager* _gm, StateManager* _st)
{
  managers = std::make_unique<ManagerAccessors>(_gm, _st);

  client = _client;
  std::stringstream ss;
  ss << "NetworkCommunicator Initialized!" << std::endl;

  debugPrint(ss.str());
}

/// RECIEVING
void NetworkCommunicator::deserializeMessage(std::vector<char> data)
{
  /// A Command Struct - cmd type, cmd id, entity id, data a,  data b     -@ symbolises
  /// A Command Stream -  |t|t|  |id|id| |e_id|e_id| |a|a|a|a|  |b|b|b|b| |@|

  std::string data_as_string(data.begin(), data.end() - 1);  /// Creates a string out of the char
                                                             /// vec

  /// Splitting the incoming serialised code into their respective
  std::string cmd_type  = data_as_string.substr(0, 2);
  std::string cmd_id    = data_as_string.substr(2, 2);
  std::string entity_id = data_as_string.substr(4, 2);
  std::string data_a    = data_as_string.substr(6, 4);
  std::string data_b    = data_as_string.substr(10, 4);

  /// Converts the divided up command into integer values
  auto a = std::stoi(cmd_type);
  auto b = std::stoi(cmd_id);
  auto c = std::stoi(entity_id);
  auto d = std::stoi(data_a);
  auto e = std::stoi(data_b);

  // code to test debugging
  std::string str = std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ", " +
                    std::to_string(d) + ", " + std::to_string(e);
  debugPrint(str);
}
void NetworkCommunicator::deserializeMessage(const std::string& cmd_stream)
{
  /// A Command Struct - cmd type, cmd id, entity id, data a,  data b     -@ symbolises
  /// A Command Stream -  |t|t|  |id|id| |e_id|e_id| |a|a|a|a|  |b|b|b|b| |@|

  /// Creates a string out of the char vec

  /// Splitting the incoming serialised code into their respective
  std::string cmd_type  = cmd_stream.substr(0, 2);
  std::string cmd_id    = cmd_stream.substr(2, 2);
  std::string entity_id = cmd_stream.substr(4, 2);
  std::string data_a    = cmd_stream.substr(6, 4);
  std::string data_b    = cmd_stream.substr(10, 4);

  /// Converts the divided up command into integer values
  auto a = std::stoi(cmd_type);
  auto b = std::stoi(cmd_id);
  auto c = std::stoi(entity_id);
  auto d = std::stoi(data_a);
  auto e = std::stoi(data_b);

  // code to test debugging
  std::string str = std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ", " +
                    std::to_string(d) + ", " + std::to_string(e);
  debugPrint(str);
}

/// SENDING
void NetworkCommunicator::serializeMessage(CommandStruct cmd)
{
  /// A Command Struct - cmd type, cmd id,, entity id, data a, data b
  /// A Command Stream -  |t|t| |id|id| |e_id|e_id| |a|a|a|a|  |b|b|b|b|  | | |

  /// Converts the different parts of the command struct into padded strings
  std::string type_str      = padTypeOrId(cmd.command_type);
  std::string cmd_id_str    = padTypeOrId(cmd.command_id);
  std::string entity_id_str = padTypeOrId(cmd.entity_id);
  std::string a_str         = padIntData(cmd.data_a);
  std::string b_str         = padIntData(cmd.data_b);

  /// Push each string into a stream to be sent
  std::stringstream data;
  data << type_str << cmd_id_str << entity_id_str << a_str << b_str << std::endl;
  data << "@";  /// Differentiaates a command
  /// For deserialisation debugging as commands dont get sent to self
  std::string str = data.str();
  std::vector<char> vec(str.begin(), str.end());
  deserializeMessage(vec);

  /// Now message is encoded and command is sent
  /*
  getNetClient()->sendCommand(data.str());
   */
}

std::string NetworkCommunicator::padIntData(int unpad_data)
{
  std::string str;

  if (unpad_data < 10)
  {
    str = "000" + std::to_string(unpad_data);  /// 0-9 will become 0000-0009
  }
  else if (unpad_data > 9 && unpad_data < 100)  /// 10-99 will become 0010-0099
  {
    str = "00" + std::to_string(unpad_data);
  }
  else if (unpad_data > 99 && unpad_data < 1000)  /// 100-999 will become 0100-0999
  {
    str = "0" + std::to_string(unpad_data);
  }
  else if (unpad_data > 999 && unpad_data < 10000)  /// 1000-9999 will stay as is
  {
    str = std::to_string(unpad_data);
  }

  if (str.empty())
  {
    return nullptr;
  }
  return str;
}

std::string NetworkCommunicator::padTypeOrId(int unpad_data)
{
  std::string str;

  if (unpad_data < 10)  /// 0-9 will turn to 00-09
  {
    str = "0" + std::to_string(unpad_data);
  }
  else if (unpad_data > 99)
  {
    return nullptr;  /// The ids only take 0-99 as the game isnt made of too many entities
  }
  else
  {
    str = std::to_string(unpad_data);  /// 10-99 will stay as they are
  }

  return str;
}

void NetworkCommunicator::setUIServerOutput(const std::string& str)
{
  mut_ex.lock();
  auto ui = managers->getSM()->getCurrentState()->getUI();
  if (ui->getOutputTextBox() != nullptr)
  {
    ui->getOutputTextBox()->displayNewMsg(str);
  }
  mut_ex.unlock();
}

void NetworkCommunicator::commandParser(CommandStruct cmd)
{
  /*
   switch (cmd.command_type)
   {
       case LOBBY_CMD:
       {
           switch(cmd.command_id)
           {
               case 0:
               {

                   break;
               }
           }
           break;
       }
       case WORLD_CMD:
       {
           switch(cmd.command_id)
           {
               case 0:
               {

                   break;
               }
           }
           break;
       }
       case BATTLE_CMD:
       {
           switch(cmd.command_id)
           {
               case 0:
               {

                   break;
               }
           }
           break;
       }
   }
*/
}
void NetworkCommunicator::messageParser(const std::string& msg)
{
  std::string suff = msg.substr(14, 1);
  if (suff == "@")
  {
    /// Command
    deserializeMessage(msg);
    return;
  }
  setUIServerOutput(msg);
  /// message
}