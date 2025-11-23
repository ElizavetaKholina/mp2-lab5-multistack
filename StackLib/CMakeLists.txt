file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_library(${library} STATIC ${srcs} ${hdrs})
