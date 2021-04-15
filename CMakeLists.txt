#set(CMAKE_BUILD_TYPE Debug)
cmake_minimum_required(VERSION 3.12.0)
project(omega)
file(GLOB_RECURSE omega_SRC CONFIGURE_DEPENDS "omega/*.h" "omega/*.cpp")
set(HEADER_ONLY_SOURCES lib/mdcore-cpp/lib/catch.hpp lib/mdcore-cpp/lib/json.hpp lib/mdcore-cpp/lib/emoji.h)

#target_include_directories(omega PUBLIC ${PROJECT_SOURCE_DIR}/lib/opus/include
add_executable(omega ${omega_SRC} ${HEADER_ONLY_SOURCES})
add_subdirectory(lib/mdcore-cpp)
find_package( Threads )
find_package(OpenSSL REQUIRED)
target_link_libraries(omega mdcore ${CMAKE_THREAD_LIBS_INIT} OpenSSL::SSL)
