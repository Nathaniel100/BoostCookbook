
add_executable(OptionsExample options_example.cpp)
target_link_libraries(OptionsExample ${Boost_LIBRARIES})

add_executable(AnyExample any_example.cpp)

add_executable(VariantExample variant_example.cpp)

add_executable(AnyDB any_db.cpp)

add_executable(VariantDB variant_db.cpp)

add_executable(OptionalExample optional_example.cpp)

add_executable(Bind bind.cpp)

add_executable(Move move.cpp)