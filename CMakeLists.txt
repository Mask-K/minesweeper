cmake_minimum_required(VERSION 3.22)
project(minesweeper)

set(CMAKE_CXX_STANDARD 20)

add_executable(minesweeper main.cpp headers/Menu.h headers/Grid.h)


include_directories(D:/SFML/include)

set(SFML_ROOT D:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics audio network)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(minesweeper ${SFML_LIBRARIES})

endif()


if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()