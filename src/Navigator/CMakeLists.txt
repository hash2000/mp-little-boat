message(STATUS "Navigator")

set(Navigator-Sources
	${LittleBoat_SOURCE_DIR}/Navigator
)

file(GLOB_RECURSE SRCS ${Navigator-Sources}/*.cpp)
add_executable(Navigator
	${SRCS}
)

target_link_libraries(Navigator
	PRIVATE
		Poco::Foundation
		Poco::Util
		Poco::Net
		Poco::NetSSL
		Poco::Crypto

#		mp-lib-module-system
)

target_include_directories(Navigator
	PUBLIC
		${Navigator-Sources}
)
