find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

file(GLOB SRCS *.cpp)

add_executable(inkball ${SRCS})
target_link_libraries(inkball PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../levels DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
