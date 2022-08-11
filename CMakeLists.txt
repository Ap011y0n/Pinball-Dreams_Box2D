cmake_minimum_required(VERSION 3.0)
project(pinball_dreams LANGUAGES CXX)

set(PROJECT_VERSION 1.0)
set(PROJECT_DESCRIPTION "Pinball Dreams")

if(CMAKE_C_COMPILER_LOADED)
  include (CheckIncludeFile)
  include (CheckCSourceCompiles)
elseif(CMAKE_CXX_COMPILER_LOADED)
  include (CheckIncludeFileCXX)
  include (CheckCXXSourceCompiles)
else()
  message(FATAL_ERROR "FindMath only works if either C or CXX language is enabled")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)
include(FindPkgConfig)
include(FindMath)
include(FindSDL2_mixer)
include(FindSDL2_image)
if(MSYS AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX $ENV{MINGW_PREFIX} CACHE PATH $ENV{MINGW_PREFIX} FORCE)
endif()

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 23 )

file( GLOB_RECURSE SOURCE_FILES src/*.cpp )
file( GLOB_RECURSE INCLUDE_FILES src/*.h )

set(CMAKE_INSTALL_DATADIR ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} ${INCLUDE_FILES} )

find_package(Math REQUIRED)
find_package(box2d REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

if(Math_FOUND AND SDL2_FOUND AND SDL2_mixer_FOUND AND SDL2_image_FOUND)
	target_compile_options(${PROJECT_NAME} PUBLIC
		-DDATADIR=\"${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/\")
	target_include_directories(${PROJECT_NAME} PUBLIC Math::Math
		${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDES}
		${SDL2_IMAGE_INCLUDES} ${OPENGL_INCLUDE_DIR}
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> )
	target_link_libraries(${PROJECT_NAME} SDL2 Math::Math ${SDL2_LIBRARY}
		${SDL2_MIXER_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
		${OPENGL_LIBRARIES} box2d::box2d )
endif()

message("-- Data files will be installed to: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/")

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config )
install(DIRECTORY Data TYPE DATA COMPONENT assets)
