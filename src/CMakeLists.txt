cmake_minimum_required(VERSION 3.20)

project(LittleBoat LANGUAGES CXX)

set(USE_VCPKG 1)

include("cmake/framework.cmake")
include("cmake/default-libs.cmake")
include("cmake/default-modules.cmake")

# message(STATUS "LittleBoat_SOURCE_DIR: ${LittleBoat_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
# message(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# message(STATUS "CMAKE_CROSSCOMPILING: ${CMAKE_CROSSCOMPILING}")
# message(STATUS "HomeDir: $ENV{HOME}")
# message(STATUS "gRPC_INSTALL_INCLUDEDIR: ${CMAKE_CROgRPC_INSTALL_INCLUDEDIRSSCOMPILING}")


include_directories(
	${LittleBoat_SOURCE_DIR}
)


add_subdirectory(Navigator)
add_subdirectory(Modules)
add_subdirectory(Libs)
add_subdirectory(Tests)
