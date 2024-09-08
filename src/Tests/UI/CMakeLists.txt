message(STATUS "Test UI Build")

set(TestUI-Sources
	${LittleBoat_SOURCE_DIR}/Tests/UI/	
)

file(GLOB_RECURSE SRCS ${TestUI-Sources}/*.cpp)
add_executable(TestUI
	${SRCS}
)

if (WIN32)
message(STATUS "Navigator OS_WINDOWS")
	target_compile_definitions(TestUI
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

target_link_libraries(TestUI
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
)

target_include_directories(TestUI
	PUBLIC
		${TestUI-Sources}		
)
