#CMakeLists.txt
cmake_minimum_required (VERSION 3.6)
project(XurBot)

add_executable(XurBot main.cpp Bot.cpp randomExotic.cpp imageMsg.cpp)

#Add these two lines
add_subdirectory(deps/sleepy-discord)
target_link_libraries(XurBot sleepy-discord)
