//
// Created by miles on 27/04/2020.
//
#include "gamelib/Command.h"

#include "gamelib/Components/GCNetClient.hpp"

void JoinLobbyCmd::execute(NetworkCommunicator& netComm, int lobby_num)
{
  netComm.getNetClient()->joinLobby(lobby_num);
}

void CreateLobbyCmd::execute(NetworkCommunicator& netComm, int lobby_size)
{
  netComm.getNetClient()->createLobby(lobby_size);
}

void SetLobbyNameCmd::execute(NetworkCommunicator& netComm, const std::string& message)
{
  netComm.getNetClient()->setLobbyName(message);
}

void SendMessageCmd::execute(NetworkCommunicator& netComm, const std::string& message)
{
  netComm.getNetClient()->sendMessage(message);
}

void GetLobbiesCmd::execute(NetworkCommunicator& netComm)
{
  netComm.getNetClient()->getLobbies();
}

void ReadyCmd::execute(NetworkCommunicator& netComm)
{
  netComm.getNetClient()->ready();
}

void UnReadyCmd::execute(NetworkCommunicator& netComm)
{
  netComm.getNetClient()->unready();
}

void CloseLobbyCmd::execute(NetworkCommunicator& netComm)
{
  netComm.getNetClient()->closeLobby();
}

void OpenLobbyCmd::execute(NetworkCommunicator& netComm)
{
  netComm.getNetClient()->openLobby();
}

void KickPlayer::execute(NetworkCommunicator& netComm, int client_id)
{
  netComm.getNetClient()->kickPlayer(client_id);
}
