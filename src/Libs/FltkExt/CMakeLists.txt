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

if (WIN32)
message(STATUS "Navigator OS_WINDOWS")
	target_compile_definitions(LibFltkExt
		PRIVATE
			UNICODE
			_UNICODE
			_CRT_SECURE_NO_WARNINGS
			NOMINMAX
			_WIN32
			WIN32_LEAN_AND_MEAN
			WIN32_NO_STATUS
			WINVER=0x0a00
			_WIN32_WINNT=0x0a00
			NDEBUG
			_MSC_BUILD
	)

	#target_compile_options(Navigator
	#	PRIVATE
	#		-W4
	#		-permissive-
	#		-nologo
	#		-Zc:__cplusplus
	#		-Zc:preprocessor
	#)
endif()

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
