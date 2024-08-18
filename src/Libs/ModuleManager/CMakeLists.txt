message(STATUS "Generate ModuleManager")


set(LibModuleManager-Sources
	${LittleBoat_SOURCE_DIR}/Libs/ModuleManager/
)

include_directories(
	${LittleBoat_SOURCE_DIR}/Libs/ModuleManager/framework
)

file(GLOB_RECURSE SRCS ${LibModuleManager-Sources}/*.cpp)
add_library(LibModuleManager
	${SRCS}
)

target_link_libraries(LibModuleManager
	PRIVATE
		Poco::Foundation
)

target_include_directories(LibModuleManager
	PUBLIC
		${LibModuleManager-Sources}
)
