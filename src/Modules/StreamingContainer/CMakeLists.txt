message(STATUS "Generate ModStreamingContainer")


set(ModStreamingContainer-Sources
	${LittleBoat_SOURCE_DIR}/Modules/StreamingContainer/
	${LittleBoat_SOURCE_DIR}/Modules/StreamingContainer/private/
)

file(GLOB_RECURSE SRCS ${ModStreamingContainer-Sources}/*.cpp)
add_library(ModStreamingContainer
	${SRCS}
)

target_compile_definitions(ModModuleContainer PRIVATE CompilerDefinationsList)

target_link_libraries(ModStreamingContainer
	PRIVATE
		Poco::Foundation

		${FFMPEG_LIBRARIES}
)

target_include_directories(ModStreamingContainer
	PUBLIC
		${ModStreamingContainer-Sources}
)
