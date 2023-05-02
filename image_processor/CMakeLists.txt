cmake_minimum_required( VERSION 3.15 )
project( ImageProcessor )

file( GLOB IMAGE_PROCESSOR_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/* )
file( GLOB IMAGE_PROCESSOR_SOURCE  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/* )

find_package( PkgConfig REQUIRED )
find_package(ImageMagick COMPONENTS Magick++)
pkg_check_modules( GTK3 REQUIRED gtk+-3.0 )

set( CMAKE_CXX_STANDARD 17 )
include_directories( ${GTK3_INCLUDE_DIRS} ${ImageMagick_INCLUDE_DIRS} )
link_directories( ${GTK3_LIBRARY_DIRS} /usr/local/lib )

add_executable( ImageProcessor ${IMAGE_PROCESSOR_HEADERS} ${IMAGE_PROCESSOR_SOURCE} )

add_definitions( ${GTK3_CFLAGS_OTHER} )
add_definitions( -DMAGICKCORE_QUANTUM_DEPTH=16 )
add_definitions( -DMAGICKCORE_HDRI_ENABLE=0 )

target_include_directories( ImageProcessor PRIVATE include )
target_link_libraries( ImageProcessor ${GTK3_LIBRARIES} ${ImageMagick_LIBRARIES} )