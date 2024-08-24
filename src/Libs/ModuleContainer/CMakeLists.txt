message(STATUS "Generate ModuleContainer")


set(LibModuleContainer-Sources
	${LittleBoat_SOURCE_DIR}/Libs/ModuleContainer/
)

include_directories(
	${LittleBoat_SOURCE_DIR}/Libs/ModuleContainer/framework
)

file(GLOB_RECURSE SRCS ${LibModuleContainer-Sources}/*.cpp)
add_library(LibModuleContainer
	${SRCS}
)

target_link_libraries(LibModuleContainer
	PRIVATE
		Poco::Foundation
)

target_include_directories(LibModuleContainer
	PUBLIC
		${LibModuleContainer-Sources}
)
