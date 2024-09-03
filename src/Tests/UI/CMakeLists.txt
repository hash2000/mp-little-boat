message(STATUS "Test UI Build")

set(TestUI-Sources
	${LittleBoat_SOURCE_DIR}/Tests/UI/	
)

file(GLOB_RECURSE SRCS ${TestUI-Sources}/*.cpp)
add_executable(TestUI
	${SRCS}
)


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
