message(STATUS "Building BeeKonami...")
add_subdirectory(konami/BeeKonami/BeeKonami/audio/K007232)
add_subdirectory(konami/BeeKonami/BeeKonami/video/K052109)
add_subdirectory(konami/BeeKonami/BeeKonami/video/K051962)
add_subdirectory(konami/BeeKonami/BeeKonami/video/K053251)

set(INTERFACE_HEADERS
	k052109.h
	k051962.h
	k053251.h
	k007232.h)

add_library(konami INTERFACE)
target_sources(konami INTERFACE ${INTERFACE_HEADERS})
target_include_directories(konami INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(konami INTERFACE k007232 k052109 k051962 k053251)