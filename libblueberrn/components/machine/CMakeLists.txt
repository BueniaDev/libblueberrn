add_subdirectory(mb14241)
add_subdirectory(i8255)
add_subdirectory(er2055)

set(INTERFACE_HEADERS
	${ER2055_HEADERS}
	${MB14241_HEADERS}
	${I8255_HEADERS}
	"er2055.h"
	"mb14241.h"
	"i8255.h")

add_library(machine INTERFACE)
target_sources(machine INTERFACE ${INTERFACE_HEADERS})
target_include_directories(machine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})