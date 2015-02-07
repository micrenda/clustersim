file(GLOB MyCSources *.c)

add_executable(clustersim ${MyCSources})
target_link_libraries(clustersim m config png lua5.2 check pthread rt)
