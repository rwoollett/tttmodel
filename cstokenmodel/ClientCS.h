
#ifndef MODEL_CLIENTCS_H
#define MODEL_CLIENTCS_H

#include <string>
#include <map>
#include <set>
#include <algorithm> //for_each
#include <iostream>
#include <chrono>

namespace Model
{

  // Define a struct to encapsulate ClientCS
  struct ClientCS
  {
    std::string name;
    std::string host;
    std::string ip;
    bool connected;
    std::string processId;
    std::string connectedAt;
    std::chrono::system_clock::time_point tpConnectedAt{};
    std::string disconnectedAt;
    std::chrono::system_clock::time_point tpDisconnectedAt{};
    int parentId;         // From RequestParent
    std::string clientIp; // From RequestParent (same as id of ClientCS)

    ClientCS() = default;
    ClientCS(const std::string &h, const std::string &s) : host(h), ip(s) {}
    ClientCS(const std::string &n, const std::string &h, const std::string &s) : name(n), host(h), ip(s) {}
  };

  // Define a struct to encapsulate Connect/Disconnect ClientCS
  struct ClientConnectCS
  {
    std::string sourceIp;
    bool connected;
    std::string processId;
    std::string connectedAt;
    std::chrono::system_clock::time_point tpConnectedAt{};

    ClientConnectCS() = default;
  };

  // Define a struct to encapsulate Connect/Disconnect ClientCS
  struct ClientDisconnectCS
  {
    std::string sourceIp;
    bool connected;
    std::string disconnectedAt;
    std::chrono::system_clock::time_point tpDisconnectedAt{};

    ClientDisconnectCS() = default;
  };

  struct CSTokenRequest
  {
    std::string sourceIp;
    std::string originalIp;
    std::string parentIp;
    bool relayed;
    CSTokenRequest() = default;
  };

  struct CSTokenAcquire
  {
    std::string ip;
    std::string sourceIp;
    CSTokenAcquire() = default;
  };


  namespace Validate
  {
    bool ClientCS(const Model::ClientCS &c);
    bool ClientConnectCS(const Model::ClientConnectCS &c);
    bool ClientDisconnectCS(const Model::ClientDisconnectCS &c);
    bool CSTokenRequest(const Model::CSTokenRequest &obj);
    bool CSTokenAcquire(const Model::CSTokenAcquire &obj);
  }
  // class NetworkMessage
  // {
  // public:
  //   enum MessageType
  //   {
  //     TOKEN,
  //     REQUEST_TOKEN,
  //     ECHO,
  //     EMPTY
  //   };

  // private:
  //   MessageType m_type;
  //   ClientIP m_source;

  // public:
  //   explicit NetworkMessage(MessageType msg_type, std::string sourceHost, std::string sourceIp);
  //   NetworkMessage();
  //   virtual ~NetworkMessage();

  //   MessageType GetMessageType() const { return m_type; }
  //   std::string SourceHost() const;
  //   std::string SourceIP() const;

  //   //    virtual void JSONDecode(const std::string &json_text, NetworkMessage& message) = 0;

  //   std::string BaseJSON() const;
  //   virtual std::string JSONEncode() const = 0;

  //   static MessageType MessageTypeFromJSON(const std::string json);
  // };

  // class EchoMessage : public NetworkMessage
  // {

  // public:
  //   explicit EchoMessage(std::string sourceHost, std::string sourceIp);
  //   EchoMessage();

  //   virtual std::string JSONEncode() const;
  // };

  // class TokenMessage : public NetworkMessage
  // {

  // public:
  //   explicit TokenMessage(std::string sourceHost, std::string sourceIp);
  //   TokenMessage();

  //   virtual std::string JSONEncode() const;
  // };

  // class TokenRequestMessage : public NetworkMessage
  // {
  //   ClientIP m_originator;
  //   std::set<std::string> m_relayVisited;

  // public:
  //   explicit TokenRequestMessage(std::string sourceHost, std::string sourceIp, std::string originatorHost, std::string originatorIp);
  //   TokenRequestMessage();

  //   std::string OriginatorHost() const;
  //   std::string OriginatorIP() const;
  //   const std::set<std::string> &GetRelayVisited() const
  //   {
  //     return m_relayVisited;
  //   };
  //   int RelayVisitedCount() const
  //   {
  //     return m_relayVisited.size();
  //   };
  //   void AddVisited(const std::string &value)
  //   {
  //     m_relayVisited.insert(value);
  //   };
  //   bool InRelayVisited(const std::string &value)
  //   {
  //     // std::cout << "InRelayVisited " << value << " " << m_relayVisited.count(value) << "\n";
  //     return (m_relayVisited.count(value) > 0);
  //   };

  //   virtual std::string JSONEncode() const;
  // };
}
#endif // MODEL_CLIENTCS_H
