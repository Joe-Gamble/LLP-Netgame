//
// Created by huxy on 23/02/2020.
//

#ifndef NETGAME_GCNETCLIENT_HPP
#define NETGAME_GCNETCLIENT_HPP
#include "GameComponent.hpp"

#include <NetLib/ClientConnection.h>
#include <atomic>
#include <queue>

class NetworkCommunicator;

class GCNetClient : public GameComponent
{
 public:
  explicit GCNetClient(NetworkCommunicator* _netCom);
  ~GCNetClient() override;
  void update(double dt) override;
  void input();

  GCNetClient(const GCNetClient&) = delete;
  GCNetClient& operator=(const GCNetClient&) = delete;

  void handleNetworkEvents();

  void sendCommand(const std::string& str);

  void connectToServer();
  void sendMessage(const std::string& str);
  void createLobby(int lobby_size);
  void joinLobby(int lobby_number);
  void getLobbies();
  void kickPlayer(int client_id);
  void ready();
  void unready();
  void closeLobby();
  void openLobby();
  void setLobbyName(const std::string& name);

 private:
  NetworkCommunicator* netCommunicator;
  netlib::ClientConnection client;
  std::atomic<bool> exiting = false;
};

#endif  // NETGAME_GCNETCLIENT_HPP
