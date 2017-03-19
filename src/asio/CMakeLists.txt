

add_executable(Timer1 timer1.cpp)
target_link_libraries(Timer1 ${Boost_LIBRARIES})

add_executable(Timer2 timer2.cpp)
target_link_libraries(Timer2 ${Boost_LIBRARIES})

add_executable(Timer3 timer3.cpp)
target_link_libraries(Timer3 ${Boost_LIBRARIES})

add_executable(Timer4 timer4.cpp)
target_link_libraries(Timer4 ${Boost_LIBRARIES})

add_executable(Timer5 timer5.cpp)
target_link_libraries(Timer5 ${Boost_LIBRARIES})

add_executable(DaytimeClient1 daytime_client1.cpp)

target_link_libraries(DaytimeClient1 ${Boost_LIBRARIES})

add_executable(DaytimeServer1 daytime_server1.cpp)

target_link_libraries(DaytimeServer1 ${Boost_LIBRARIES})

add_executable(DaytimeServer2 daytime_server2.cpp)

target_link_libraries(DaytimeServer2 ${Boost_LIBRARIES})

add_subdirectory(chat)
