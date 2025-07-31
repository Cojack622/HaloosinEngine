cmake_minimum_required(VERSION 3.30)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(HaloosinEngine VERSION 1.0)

option(BUILD_SHARED_LIBS "Build Haloosin as a shared library" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(reflectcpp CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)


add_library(Haloosin)

file(GLOB_RECURSE INCLUDES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp"

)

file(GLOB_RECURSE SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c"
)

target_include_directories(Haloosin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")


target_sources(Haloosin PRIVATE ${SOURCES})
target_sources(Haloosin PUBLIC ${INCLUDES})

target_link_libraries(Haloosin PRIVATE
	glad
	glfw3
	assimp
	reflectcpp::reflectcpp
	EnTT::EnTT
	glm::glm
)

target_compile_definitions(Haloosin PUBLIC GLFW_INCLUDE_NONE)

if(MSVC)
	target_compile_options(Haloosin PRIVATE
		/W3
		/MP
		/WX
		/ZI
	)
else()
	target_compile_options(Haloosin PRIVATE 
		-Wall
		-Wextra
		-Wpedantic
	)
endif()
