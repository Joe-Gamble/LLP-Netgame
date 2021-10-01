//
// Created by miles on 27/04/2020.
//

#ifndef MYNETGAME_COMMAND_H
#define MYNETGAME_COMMAND_H

#include "../../apps/ASGEGame/Managers/NetworkCommunicator.h"
#include "string"

#include <cstring>

class Command
{
 public:
  virtual ~Command()     = default;
  virtual void execute() = 0;  /// parameters can dictate the target of the command
};

class NetworkCommunicator;

class JoinLobbyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm, int lobby_num);
};

class CreateLobbyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm, int lobby_size);
};

class SetLobbyNameCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm, const std::string& message);
};

class SendMessageCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm, const std::string& message);
};

class GetLobbiesCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm);
};

class ReadyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm);
};

class UnReadyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm);
};

class CloseLobbyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm);
};

class OpenLobbyCmd : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm);
};

class KickPlayer : public Command
{
 public:
  static void execute(NetworkCommunicator& netComm, int client_id);
};
#endif  // MYNETGAME_COMMAND_H
