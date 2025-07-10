
#ifndef EVENT_ACTIONS_H
#define EVENT_ACTIONS_H

#include "Subjects.h"
#include <string>
#include <chrono>

namespace Events
{
  // Define a struct to encapsulate Connect/Disconnect ClientCS
  struct ClientConnectEvent
  {
    Subject subject{Subject::ClientCSConnected};
    std::string sourceIp;
    std::string processId;
    std::string connectedAt;
    std::chrono::system_clock::time_point tpConnectedAt{};
    ClientConnectEvent() = default;
  };

  struct ClientDisconnectEvent
  {
    Subject subject{Subject::ClientCSDisconnected};
    std::string sourceIp;
    std::string disconnectedAt;
    std::chrono::system_clock::time_point tpDisconnectedAt{};
    ClientDisconnectEvent() = default;
  };

  struct CSTokenRequestEvent
  {
    Subject subject{Subject::CSTokenRequest};
    std::string sourceIp;
    std::string originalIp;
    std::string parentIp;
    std::string requestedAt;
    bool relayed;
    std::chrono::system_clock::time_point tpRequestedAt{};
    CSTokenRequestEvent() = default;
  };

  struct CSTokenAcquireEvent
  {
    Subject subject{Subject::CSTokenAcquire};
    std::string ip;
    std::string sourceIp;
    std::string acquiredAt;
    std::chrono::system_clock::time_point tpAcquiredAt{};
    CSTokenAcquireEvent() = default;
  };

}
#endif // EVENT_ACTIONS_H
