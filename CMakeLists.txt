cmake_minimum_required (VERSION 3.26)

project (oop2_project)
set (COURSE_EXAMPLE OFF)
set (MY_AUTHORS "Noam_mazouz-Ofek_Cohen-Orel_Zabriko-Nadav_Ben_Melech")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})


if (NOT MSVC)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

set (SFML_LOCATION "C:/SFML/SFML-2.6.1")
set (SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package (SFML 2.6 COMPONENTS graphics audio REQUIRED)

set_target_properties (sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

target_link_libraries (${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio sfml-main)

include (cmake/SFML.cmake)

