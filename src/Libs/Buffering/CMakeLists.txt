message(STATUS "Generate Buffering")


set(LibBuffering-Sources
	${LittleBoat_SOURCE_DIR}/Libs/Buffering/
)

include_directories(
	${LittleBoat_SOURCE_DIR}/Libs/Buffering/framework
)

file(GLOB_RECURSE SRCS ${LibBuffering-Sources}/*.cpp)
add_library(LibBuffering
	${SRCS}
)

target_compile_definitions(LibBuffering PRIVATE CompilerDefinationsList)

target_link_libraries(LibBuffering
	PRIVATE
		Poco::Foundation
)

target_include_directories(LibBuffering
	PUBLIC
		${LibBuffering-Sources}
)
