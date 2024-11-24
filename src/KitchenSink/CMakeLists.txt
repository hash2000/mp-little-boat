message(STATUS "KitchenSink Build")

set(KitchenSink-Sources
	${LittleBoat_SOURCE_DIR}/KitchenSink/	
)

file(GLOB_RECURSE SRCS ${KitchenSink-Sources}/*.cpp)
add_executable(KitchenSink
	${SRCS}
)

target_compile_definitions(KitchenSink PRIVATE CompilerDefinationsList)

target_link_libraries(KitchenSink
	PRIVATE
		Poco::Foundation
		Poco::Util
		Poco::Net
		Poco::NetSSL
		Poco::Crypto

		fltk fltk_gl
		fltk_forms
		fltk_images

		LibFltkExt

		ModModuleContainer
		ModStreamingContainer
)

target_include_directories(KitchenSink
	PUBLIC
		${KitchenSink-Sources}
)
