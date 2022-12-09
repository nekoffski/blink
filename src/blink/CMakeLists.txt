find_package(Boost 1.79.0 COMPONENTS system) 


set (BLINK_LIBS dl kc ${Boost_LIBRARIES} pthread)
set (BLINK_TARGET blink)

file (GLOB_RECURSE BLINK_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${BLINK_TARGET} STATIC ${BLINK_SRC})

target_include_directories(${BLINK_TARGET} PRIVATE ${BLINK_INCLUDE} ${Boost_INCLUDE_DIRS})
set_property(TARGET ${BLINK_TARGET} PROPERTY CXX_STANDARD 20)
target_link_libraries(${BLINK_TARGET} PUBLIC ${BLINK_LIBS})
target_compile_options(${BLINK_TARGET} PUBLIC "-fcoroutines")
