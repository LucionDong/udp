cmake_minimum_required (VERSION 2.8)

# projectname is the same as the main-executable
project(udpLnx)

# set(SOURCE /home/lucion/empty_project/src/client.c /home/lucion/empty_project/src/epoll.c /home/lucion/empty_project/src/lnx_udp.c)
set(SOURCE ../src/client.c ../src/epoll.c ../src/lnx_udp.c)
add_executable(${PROJECT_NAME} ${SOURCE})
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
