message(STATUS "Generate ModModuleContainer")


set(ModModuleContainer-Sources
	${LittleBoat_SOURCE_DIR}/Modules/ModuleContainer/
)

file(GLOB_RECURSE SRCS ${ModModuleContainer-Sources}/*.cpp)
add_library(ModModuleContainer
	${SRCS}
)

target_link_libraries(ModModuleContainer
	PRIVATE
		Poco::Foundation
)

target_include_directories(ModModuleContainer
	PUBLIC
		${ModModuleContainer-Sources}
)
