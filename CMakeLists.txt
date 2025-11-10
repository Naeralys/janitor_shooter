# This project has a dependency on SDL2 and SDL2_image and
# was originally configured to work on MacOS build system.
# Make sure SDL2 is installed, and if it is not working on 
# Linux or Windows then please add configuration for those platforms
# here.

cmake_minimum_required(VERSION 3.10)
project(Shooter)

if (WIN32)
    set(SDL2_DIR "lib/")
    set(DSDL2_IMAGE_PATH "lib/SDL2_image")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 14)


# Locate and include SDL2 and SDL2_image as dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Include source files as well as assets folder
file(GLOB SOURCE_FILES
  "src/*.cpp"
)
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Create executable and link libraries to build
add_executable(Shooter ${SOURCE_FILES})
target_link_libraries(Shooter PUBLIC SDL2::SDL2 SDL2_image::SDL2_image)

# Package the installer with CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Shooter")
set(CPACK_SOURCE_GENERATOR "TGZ")
SET(CPACK_OUTPUT_FILE_PREFIX packages)
include(CPack)