if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set (OS_LINUX 1)
    add_definitions(-D OS_LINUX)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set (OS_WINDOWS 1)
    add_definitions(-D OS_WINDOWS)
endif()

message (STATUS "Target framework: ${CMAKE_SYSTEM_NAME}")
message (STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
message (STATUS "VCPKG_TARGET_TRIPLET: ${VCPKG_TARGET_TRIPLET}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#if(OS_WINDOWS)
#    set(CMAKE_CXX_FLAGS /EHsc)
#endif()
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

list(APPEND CompilerDefinationsList
	UNICODE
	_UNICODE
	_CRT_SECURE_NO_WARNINGS
	NOMINMAX
	NDEBUG
)

if (WIN32)
	list(APPEND CompilerDefinationsList
		_WIN32
		WIN32_LEAN_AND_MEAN
		WIN32_NO_STATUS
		WINVER=0x0a00
		_WIN32_WINNT=0x0a00
		_MSC_BUILD
	)
endif()

#if(WIN32)
#    # When we build statically (MT):
#    if(NOT BUILD_SHARED_LIBS)
#        # Select MSVC runtime based on CMAKE_MSVC_RUNTIME_LIBRARY.
#        # We switch from the multi-threaded dynamically-linked library (default)
#        # to the multi-threaded statically-linked runtime library.
#        cmake_policy(SET CMP0091 NEW)
#        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#    endif()
#
#    # Global Compiler flags for optimized Release and RelWithDebugInfo builds
#    # All overrides are for multi-threaded dynamically-linked libs: MD + MDd.
#    if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
#        set(CMAKE_USER_MAKE_RULES_OVERRIDE "CMakeOverride.txt")
#    endif()
#
#endif()
