//
// Created by huxy on 23/02/2020.
//

#include "gamelib/Components/GCNetServer.hpp"

#include "../../apps/ASGEGame/Managers/NetworkCommunicator.h"

#include <thread>

GCNetServer::GCNetServer(NetworkCommunicator* _netCom) : GameComponent(ID::NETWORK_SERVER)
{
  server.Start(32488);
  netCommunicator = _netCom;
}

void GCNetServer::update(double dt)
{
  using namespace netlib;

  // while server should not terminate

  //  while (!terminate)
  //{
  std::queue<NetworkEvent> all_events = server.GetNetworkEvents();
  while (!all_events.empty())
  {
    std::stringstream ss;
    ss << "(Server) ";
    NetworkEvent& event = all_events.front();  /// We set a refernce to network event
    /// NetworkEvent, a struct containing - EventType, data (for message events),
    /// senderId (client uniqueID) & a void WriteData(T new data, int writePos) +
    /// T ReadData(int readPos), template functions.

    switch (event.eventType)
    {
    case NetworkEvent::EventType::ON_CONNECT:
    {
      ClientInfo info = server.GetClientInfo(event.senderId);
      ss << "New client " << info.name << "connected on ip: " << info.ipv4 << " - ID:[" << info.uid
         << "]" << std::endl;
      netCommunicator->debugPrint(ss.str());
      break;
    }
    case NetworkEvent::EventType::ON_DISCONNECT:
    {
      ss << "Client " << event.senderId << " has disconnected." << std::endl;
      netCommunicator->debugPrint(ss.str());
      break;
    }
    case NetworkEvent::EventType::MESSAGE:
    {
      ClientInfo info = server.GetClientInfo(event.senderId);
      server.SendMessageToAllExcluding(event.data, event.senderId, info.lobbyID);
      ss << "Client " << event.data.data() << std::endl;
      netCommunicator->debugPrint(ss.str());
      break;
    }
    }
    all_events.pop();
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void GCNetServer::terminateServer()
{
  terminate = true;
}
