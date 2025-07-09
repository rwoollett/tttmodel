
#ifndef EVENT_SUBJECTS_H
#define EVENT_SUBJECTS_H

#include <string>
#include <map>

namespace Events
{
  
  enum class Subject
  {
    Invalid = -1,
    ClientCSConnected,
    ClientCSDisconnected,
    CSTokenRequest,
    CSTokenAcquire
  };

  static const std::map<Subject, std::string_view> SubjectNames = {
      {Subject::ClientCSConnected, "clientCS_Connected"},
      {Subject::ClientCSDisconnected, "clientCS_Disconnected"},
      {Subject::CSTokenRequest, "csToken_request"},
      {Subject::CSTokenAcquire, "csToken_acquire"}};

  static const std::map<std::string_view, Subject> SubjectFromNames = {
      {"clientCS_Connected", Subject::ClientCSConnected},
      {"clientCS_Disconnected", Subject::ClientCSDisconnected},
      {"csToken_request", Subject::CSTokenRequest},
      {"csToken_acquire", Subject::CSTokenAcquire}};

}
#endif // EVENT_SUBJECTS_H
