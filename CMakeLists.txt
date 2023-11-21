cmake_minimum_required(VERSION 3.27)

project(
  TodoApp
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# for promoted widgets
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt_add_executable(
  TodoApp
  MANUAL_FINALIZATION
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  listspanel.h
  listspanel.cpp
  listspanel.ui
  itemspanel.h
  itemspanel.cpp
  itemspanel.ui
  items_table_model.hpp
  data.sql
  checkboxdelegate.h checkboxdelegate.cpp)

target_link_libraries(TodoApp PRIVATE Qt6::Widgets Qt6::Sql)

set_target_properties(
  TodoApp
  PROPERTIES ${BUNDLE_ID_OPTION} MACOSX_BUNDLE_BUNDLE_VERSION
             ${PROJECT_VERSION} MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} MACOSX_BUNDLE
             TRUE WIN32_EXECUTABLE
             TRUE)

include(GNUInstallDirs)
install(
  TARGETS TodoApp
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

qt_finalize_executable(TodoApp)
