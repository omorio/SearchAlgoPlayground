cmake_minimum_required(VERSION 3.5.0)
project(SearchAlgoPlayground2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(SearchAlgoPlayground2 main.cpp)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(SearchAlgoPlayground2 sfml-graphics sfml-audio)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
