message(STATUS "Generate FltkExt")


set(LibFltkExt-Sources
	${LittleBoat_SOURCE_DIR}/Libs/FltkExt/
)

include_directories(
	${LittleBoat_SOURCE_DIR}/Libs/FltkExt/framework
)

file(GLOB_RECURSE SRCS ${LibFltkExt-Sources}/*.cpp)
add_library(LibFltkExt
	${SRCS}
)

target_link_libraries(LibFltkExt
	PRIVATE
		Poco::Foundation

		fltk fltk_gl
		fltk_forms
		fltk_images

)

target_include_directories(LibFltkExt
	PUBLIC
		${LibFltkExt-Sources}
)
