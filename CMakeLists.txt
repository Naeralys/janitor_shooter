cmake_minimum_required(VERSION 3.10)
project(Shooter)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB SOURCE_FILES
  "src/*.cpp"
)

file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(Shooter ${SOURCE_FILES})

target_link_libraries(Shooter ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
