set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(csize cache_size.c)
add_executable(cppsize cache_size.cpp)
add_executable(fshare false_sharing.c)