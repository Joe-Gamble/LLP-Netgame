//
// Created by huxy on 23/02/2020.
//

#ifndef NETGAME_GCNETSERVER_HPP
#define NETGAME_GCNETSERVER_HPP

#include "GameComponent.hpp"

#include <NetLib/ServerConnection.h>
#include <sstream>

class NetworkCommunicator;

class GCNetServer : public GameComponent
{
 public:
  explicit GCNetServer(NetworkCommunicator* _netCom);
  ~GCNetServer() final = default;

  GCNetServer(const GCNetServer&) = delete;
  GCNetServer& operator=(const GCNetServer&) = delete;

  void update(double dt) override;
  void terminateServer();

 private:
  NetworkCommunicator* netCommunicator;
  netlib::ServerConnection server;
  bool terminate = false;
};

#endif  // NETGAME_GCNETSERVER_HPP
