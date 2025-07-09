cmake_minimum_required(VERSION 3.16)

# CSToken services model structures (to enable using model structures in other applications)
add_library(CSTokenModel
  ClientCS.cpp
  ClientCS.h
  Events.h
  events/Actions.h
  events/json.h
  events/Subjects.h
  json.h
  pq.cpp
  pq.h
  timestamp.cpp
  timestamp.h
)


target_include_directories(
  CSTokenModel PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/..
  $<INSTALL_INTERFACE:include>
)
