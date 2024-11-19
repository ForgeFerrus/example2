cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(example2)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(example2 example2.cpp ${sources} ${headers})
target_link_libraries(example2 ${Geant4_LIBRARIES})

set(EXAMPLE1_SCRIPTS
  run2.mac
  vis.mac
  )

foreach(_script ${EXAMPLE2_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(ex2 DEPENDS example2)

install(TARGETS example2 DESTINATION bin)
