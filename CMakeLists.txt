cmake_minimum_required(VERSION 2.8)

project(cuteinformer)
find_package(Qt4 REQUIRED)

# Pick up sources
include ("sources.cmake")
qt4_wrap_cpp(SOURCES_MOC ${HEADERS})

# Set up Qt
set(QT_USE_QTDBUS TRUE)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# Set up target
add_executable(cuteinformer ${SOURCES} ${SOURCES_MOC})
target_link_libraries(cuteinformer ${QT_LIBRARIES})

# Installation rules
set(CUTEINFORMER_BIN_PATH ${CMAKE_INSTALL_PREFIX}/bin/cuteinformer)
configure_file(resources/org.freedesktop.Notifications.service.in org.freedesktop.Notifications.service)

install(
  TARGETS cuteinformer
  DESTINATION bin
)
install(
  FILES ${PROJECT_BINARY_DIR}/org.freedesktop.Notifications.service 
  DESTINATION share/dbus-1/services/
)
install(
  DIRECTORY resources/theme
  DESTINATION share/cuteinformer
)
