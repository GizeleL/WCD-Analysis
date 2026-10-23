#cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_minimum_required(VERSION 3.16...3.21)
project(swgo)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})


list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/home/ubuntu20/root/cmake)
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
add_definitions(${ROOT_CXX_FLAGS})

#find_package(ROOT REQUIRED COMPONENTS RIO)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})

include_directories(${ROOT_INCLUDE_DIRS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB macros ${PROJECT_SOURCE_DIR}/*.mac)

#file(GLOB inputs ${PROJECT_SOURCE_DIR}/*.in)

#add_executable(sim sim.cc ${sources})

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SWGO SWGO.cc ${sources} ${headers})
target_link_libraries(SWGO ${Geant4_LIBRARIES})
target_link_libraries(SWGO ${ROOT_LIBRARIES})
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build OpNovice. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(SWGO_SCRIPTS
    muon.mac
    gui.mac
    vis.mac
   )

# foreach(_script ${LXe_SCRIPTS})
#   configure_file(
#     ${PROJECT_SOURCE_DIR}/${_script}
#     ${PROJECT_BINARY_DIR}/${_script}
#     COPYONLY
#     )
# endforeach()

foreach(_script ${SWGO_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(swgo DEPENDS SWGO)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS SWGO DESTINATION bin)
