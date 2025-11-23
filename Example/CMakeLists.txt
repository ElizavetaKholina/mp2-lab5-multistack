#set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${application} ${srcs} ${hdrs})
target_link_libraries(${application} ${library})
