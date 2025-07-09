#include "ClientCS.h"

namespace Model
{

  bool Validate::ClientCS(const Model::ClientCS &c)
  {
    return !(c.name.empty() ||
             c.host.empty() ||
             c.ip.empty());
  }

  bool Validate::ClientConnectCS(const Model::ClientConnectCS &c)
  {
    return !(c.sourceIp.empty());
  }

  bool Validate::ClientDisconnectCS(const Model::ClientDisconnectCS &c)
  {
    return !(c.sourceIp.empty());
  }

  bool Validate::CSTokenRequest(const Model::CSTokenRequest &o)
  {
    return !(o.sourceIp.empty() ||
             o.originalIp.empty() ||
             o.parentIp.empty());
  }

  bool Validate::CSTokenAcquire(const Model::CSTokenAcquire &o)
  {
    return !(o.sourceIp.empty() ||
             o.ip.empty());
  }

  // NetworkMessage::NetworkMessage(MessageType msg_type, std::string sourceHost, std::string sourceIp) : m_type(msg_type),
  //                                                                                                      m_source(sourceHost, sourceIp)
  // {
  // }

  // NetworkMessage::NetworkMessage() : m_type(MessageType::EMPTY), m_source("", "")
  // {
  // }

  // NetworkMessage::~NetworkMessage()
  // {
  // }

  // std::string NetworkMessage::BaseJSON() const
  // {
  //   std::string json_string;
  //   json encode;
  //   switch (GetMessageType())
  //   {
  //   case TOKEN:
  //     encode["type"] = "token";
  //     break;
  //   case REQUEST_TOKEN:
  //     encode["type"] = "request";
  //     break;
  //   case ECHO:
  //     encode["type"] = "echo";
  //     break;
  //   default:
  //     break;
  //   }
  //   encode["source_host"] = m_source.host;
  //   encode["source_ip"] = m_source.ip;
  //   std::string serialized_string = encode.dump();
  //   return std::move(serialized_string);
  // }

  // std::string NetworkMessage::SourceHost() const
  // {
  //   return m_source.host;
  // }

  // std::string NetworkMessage::SourceIP() const
  // {
  //   return m_source.ip;
  // }

  // NetworkMessage::MessageType NetworkMessage::MessageTypeFromJSON(std::string json_text)
  // {
  //   json msg = json::parse(json_text);
  //   std::string type_msg;
  //   if (msg["type"].is_string())
  //   {
  //     type_msg = msg["type"].get<std::string>();
  //     if (type_msg == "token")
  //     {
  //       return TOKEN;
  //     }
  //     else if (type_msg == "request")
  //     {
  //       return REQUEST_TOKEN;
  //     }
  //     else if (type_msg == "echo")
  //     {
  //       return ECHO;
  //     }
  //     else
  //     {
  //       return EMPTY;
  //     }
  //   }
  //   else
  //   {
  //     return EMPTY;
  //   }
  // }

  // //
  // EchoMessage::EchoMessage(std::string sourceHost, std::string sourceIp) : NetworkMessage(MessageType::ECHO, sourceHost, sourceIp)
  // {
  // }

  // EchoMessage::EchoMessage() : NetworkMessage()
  // {
  // }

  // std::string EchoMessage::JSONEncode() const
  // {
  //   return BaseJSON();
  // }

  // //
  // TokenMessage::TokenMessage(std::string sourceHost, std::string sourceIp) : NetworkMessage(MessageType::TOKEN, sourceHost, sourceIp)
  // {
  // }

  // TokenMessage::TokenMessage() : NetworkMessage()
  // {
  // }

  // std::string TokenMessage::JSONEncode() const
  // {
  //   return BaseJSON();
  // }

  // //
  // TokenRequestMessage::TokenRequestMessage(
  //     std::string sourceHost,
  //     std::string sourceIp,
  //     std::string originatorHost,
  //     std::string originatorIp) : NetworkMessage(MessageType::REQUEST_TOKEN, sourceHost, sourceIp),
  //                                 m_originator(originatorHost, originatorIp),
  //                                 m_relayVisited{}
  // {
  // }

  // TokenRequestMessage::TokenRequestMessage() : NetworkMessage()
  // {
  // }

  // std::string TokenRequestMessage::OriginatorHost() const
  // {
  //   return m_originator.host;
  // }

  // std::string TokenRequestMessage::OriginatorIP() const
  // {
  //   return m_originator.ip;
  // }

  // std::string TokenRequestMessage::JSONEncode() const
  // {
  //   json encode = json::parse(BaseJSON());
  //   encode["originator_host"] = m_originator.host;
  //   encode["originator_ip"] = m_originator.ip;
  //   encode["relayVisited"] = m_relayVisited;
  //   std::string serialized_string = encode.dump();
  //   return std::move(serialized_string);
  // }
}