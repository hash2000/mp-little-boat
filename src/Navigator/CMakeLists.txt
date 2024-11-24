message(STATUS "Navigator")

set(Navigator-Sources
	${LittleBoat_SOURCE_DIR}/Navigator	
)

include_directories(
	${LittleBoat_SOURCE_DIR}/Navigator/framework
)

file(GLOB_RECURSE SRCS ${Navigator-Sources}/*.cpp)
add_executable(Navigator
	${SRCS}
)


target_compile_definitions(Navigator PRIVATE CompilerDefinationsList)


target_link_libraries(Navigator
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

target_include_directories(Navigator
	PUBLIC
		${Navigator-Sources}		
)
