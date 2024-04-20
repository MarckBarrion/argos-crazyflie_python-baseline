# Install script for directory: /home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos3/plugins/robots/crazyflie/simulator" TYPE FILE FILES
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_entity.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_battery_equipped_entity.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_battery_default_sensor.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_camera_equipped_entity.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_colored_blob_perspective_camera_default_sensor.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_proximity_equipped_entity.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_proximity_default_sensor.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_ground_equipped_entity.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/crazyflie_ground_rotzonly_sensor.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/pointmass3d_crazyflie_model.h"
    "/home/herzon/thesis/argos-crazyflie_prereq/src/plugins/robots/crazyflie/simulator/qtopengl_crazyflie.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos3" TYPE SHARED_LIBRARY FILES "/home/herzon/thesis/argos-crazyflie_prereq/build/plugins/robots/crazyflie/libargos3plugin_simulator_crazyflie.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so"
         OLD_RPATH "/usr/local/lib/argos3:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_crazyflie.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

