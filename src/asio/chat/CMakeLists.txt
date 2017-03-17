


add_executable(chat_client chat_client.cpp chat_message.h)
target_link_libraries(chat_client ${Boost_LIBRARIES})

add_executable(chat_server chat_server.cpp chat_message.h)
target_link_libraries(chat_server ${Boost_LIBRARIES})