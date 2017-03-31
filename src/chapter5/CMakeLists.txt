

add_executable(WorkQueue work_queue.cpp)
target_link_libraries(WorkQueue ${Boost_LIBRARIES})

add_executable(SharedLock shared_lock.cpp)
target_link_libraries(SharedLock ${Boost_LIBRARIES})