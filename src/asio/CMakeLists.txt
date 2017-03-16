

add_executable(DaytimeClient1 daytime_client1.cpp)

target_link_libraries(DaytimeClient1 ${Boost_LIBRARIES})

add_executable(DaytimeServer1 daytime_server1.cpp)

target_link_libraries(DaytimeServer1 ${Boost_LIBRARIES})

add_executable(DaytimeServer2 daytime_server2.cpp)

target_link_libraries(DaytimeServer2 ${Boost_LIBRARIES})
