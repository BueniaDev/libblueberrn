message(STATUS "Building BeePSG...")
add_subdirectory(psg/BeePSG/BeePSG/ay8910)
add_subdirectory(fm/BeeNuked/BeeNuked/OPM)
add_subdirectory(pcm/BeePCM/BeePCM/uPD7759)

set(INTERFACE_HEADERS
	ay8910.h
	ym2151.h
	upd7759.h)

add_library(audio INTERFACE)
target_sources(audio INTERFACE ${INTERFACE_HEADERS})
target_include_directories(audio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(audio INTERFACE ay8910 ym2151 upd7759)