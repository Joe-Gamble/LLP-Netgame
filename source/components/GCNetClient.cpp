//
// Created by huxy on 23/02/2020.
//
#include "gamelib/Components/GCNetClient.hpp"

#include "../../apps/ASGEGame/Managers/NetworkCommunicator.h"

#include <iostream>
#include <sstream>
#include <thread>

GCNetClient::GCNetClient(NetworkCommunicator* _netCom) : GameComponent(ID::NETWORK_CLIENT)
{
  netCommunicator = _netCom;
  connectToServer();
}

GCNetClient::~GCNetClient()
{
  client.Disconnect();
}

void GCNetClient::update(double dt)
{
  std::thread tr_net_events(&GCNetClient::handleNetworkEvents, this);
  tr_net_events.detach();
}

void GCNetClient::handleNetworkEvents()
{
  using namespace netlib;
  while (client.IsRunning())
  {
    std::queue<NetworkEvent> all_events = client.GetNetworkEvents();
    while (!all_events.empty())
    {
      std::stringstream ss;
      ss << "(Client) ";
      NetworkEvent& event = all_events.front();
      switch (event.eventType)
      {
      case NetworkEvent::EventType::ON_CONNECT:
      {
        ss << "Connected to the server!" << std::endl;
        std::thread tr(&GCNetClient::input, this);
        tr.detach();  /// permits the thread to execute independently from the thread handle
        netCommunicator->debugPrint(ss.str());
        break;
      }
      case NetworkEvent::EventType::ON_DISCONNECT:
      {
        event.senderId;
        ss << "Disconnected from server! Shutting down..." << std::endl;
        netCommunicator->debugPrint(ss.str());
        break;
      }
      case NetworkEvent::EventType::MESSAGE:
      {
        event.data;
        ss << event.data.data() << std::endl;
        netCommunicator->messageParser(ss.str());
        netCommunicator->setUIServerOutput(ss.str());
        break;
      }
      case NetworkEvent::EventType::ON_LOBBY_JOIN:
      {
        event.eventType;
        ss << "Joined Lobby: " << client.GetCurrentLobbyInfo().name << std::endl;
        netCommunicator->debugPrint(ss.str());
        break;
      }
      case NetworkEvent::EventType ::REMOVED_FROM_LOBBY:
      {
        ss << "Removed from lobby." << std::endl;
        netCommunicator->debugPrint(ss.str());
        break;
      }
        /*case NetworkEvent::EventType::GAME_COMMAND:
        {
          ss << event.data.data() << std::endl;
          netCommunicator->debugPrint(ss.str());
          netCommunicator->deserializeMessage(event.data);
          break;
        }*/
      }
      all_events.pop();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  exiting = true;
}

void GCNetClient::input() {}

void GCNetClient::createLobby(int lobby_size)
{
  if (lobby_size < 2)
  {
    client.CreateLobby("GameLobby", 2);
  }
  else
  {
    client.CreateLobby("GameLobby", lobby_size);
  }
  std::stringstream ss;
  ss << "(Client) "
     << "New Lobby Name: "
     << "'GameLobby' "
     << " Size: " << lobby_size;
  netCommunicator->setUIServerOutput(ss.str());
  netCommunicator->debugPrint(ss.str());
}

void GCNetClient::joinLobby(int lobby_number)
{
  std::stringstream ss;
  client.JoinLobby(lobby_number);
  ss << "(Client) "
     << "Joined Lobby: " << lobby_number;
  netCommunicator->setUIServerOutput(ss.str());
  netCommunicator->debugPrint(ss.str());
}

void GCNetClient::getLobbies()
{
  auto lobbies = client.GetAllLobbyInfo();
  std::stringstream ss;
  ss << "(Client) ";
  for (auto& lobby : lobbies)
  {
    ss << "Lobby Name: " << lobby.name << " ID: " << lobby.lobbyID << " (" << lobby.clientsInRoom
       << "/" << lobby.maxClientsInRoom;
    netCommunicator->setUIServerOutput(ss.str());
    netCommunicator->debugPrint(ss.str());
    ss.str("");
    ss << "   Clients in Lobby: ";
    netCommunicator->setUIServerOutput(ss.str());
    netCommunicator->debugPrint(ss.str());
    ss.str("");
    for (auto& member : lobby.memberInfo)
    {
      ss << "     "
         << "\t[" << member.lobbySlot << "]"
         << " Name: " << member.name << " ID:" << member.uid << " (" << member.ping << " ms)"
         << (member.ready ? "(READY)" : "(NOT READY)");
      netCommunicator->setUIServerOutput(ss.str());
      netCommunicator->debugPrint(ss.str());
      ss.str("");
    }
  }
}

void GCNetClient::kickPlayer(int client_id)
{
  client.RemoveFromLobby(client_id);
  std::stringstream ss;
  ss << "(Client) "
     << "Client " << client_id << " has been kicked";
  netCommunicator->setUIServerOutput(ss.str());
  netCommunicator->debugPrint(ss.str());
}

void GCNetClient::ready()
{
  client.SetReady(true);
}

void GCNetClient::unready()
{
  client.SetReady(false);
}

void GCNetClient::closeLobby()
{
  client.SetLobbyOpen(false);
}

void GCNetClient::openLobby()
{
  client.SetLobbyOpen(true);
}

void GCNetClient::setLobbyName(const std::string& name)
{
  client.SetLobbyName(name);
  std::stringstream ss;
  ss << "(Client) "
     << "Lobby name set to " << name;
  netCommunicator->setUIServerOutput(ss.str());
  netCommunicator->debugPrint(ss.str());
}

void GCNetClient::sendMessage(const std::string& str)
{
  std::string msg = str;
  if (client.IsInLobby())
  {
    msg = client.GetMemberInfo().name + ": " + msg;
  }
  else
  {
    msg = std::to_string(client.GetUID()) + ": " + msg;
  }
  client.SendMessageToServer(msg.c_str(), static_cast<int>(msg.size()) + 1);
}

void GCNetClient::connectToServer()
{
  static const int port = 32488;
  client.ConnectToIP("localhost", port);
}

/*
void GCNetClient::sendCommand(const std::string& str)
{
  client.SendMessageToServer(str.c_str(), static_cast<int>(str.size()) + 1);
}
 */
