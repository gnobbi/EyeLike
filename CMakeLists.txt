cmake_minimum_required(VERSION 2.8)
# include makros
add_subdirectory(tools/cmake)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "AMD64")
	set(arch x64)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "IX86")
	set(arch x86)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "ARM")
	set(arch arm)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/${arch})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../bin/${arch})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../bin/${arch})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${arch})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../lib/${arch})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../lib/${arch})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib/${arch})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../lib/${arch})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../lib/${arch})
set(CMAKE_DEBUG_POSTFIX _d)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(BUILD_SHARED_LIBS ON)

################################################################################
### Main Project															 ###
################################################################################
project(EyeLike CXX)
set(main_exe_name EyeLikeApp)

################################################################################
### EyeLikeApp     															 ###
################################################################################
set(exe_name ${main_exe_name})

file(GLOB_RECURSE external_header include/*.h)
file(GLOB_RECURSE internal_header src/*.h)
file(GLOB_RECURSE srcs src/*.cpp)
ADD_MSVC_PRECOMPILED_HEADER(${CMAKE_CURRENT_SOURCE_DIR}/src/precompiled.cpp "${srcs}")

add_executable(${exe_name} ${external_header} ${internal_header} ${srcs})

### source filters ###   	
file(GLOB internal_header ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
source_group(source FILES ${internal_header})
source_group(source FILES ${srcs})
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
FOREACH(subdir ${SUBDIRS})
	file(GLOB_RECURSE internal_module_header ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.h)
	file(GLOB_RECURSE module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.cpp)
	source_group(source\\${subdir} FILES ${internal_module_header})
	source_group(source\\${subdir} FILES ${module_srcs})
ENDFOREACH()

### include filters ###   	
file(GLOB external_header ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
source_group(include FILES ${external_header})
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
FOREACH(subdir ${SUBDIRS})
	file(GLOB_RECURSE external_module_header ${CMAKE_CURRENT_SOURCE_DIR}/include/${subdir}/*.h)
	source_group(include\\${subdir} FILES ${external_module_header})
ENDFOREACH()

set_target_properties(${exe_name} PROPERTIES COMPILE_DEFINITIONS "USE_DLL=1")
include_directories(include)
include_directories(src)

################################################################################
### 3rdParty libs  															 ###
################################################################################
SUBDIRLIST(modules ${CMAKE_SOURCE_DIR}/3rdParty)
FOREACH(module_name ${modules})
	set(exe_name ${module_name})
	message("   Found 3rdParty lib @ " ${CMAKE_SOURCE_DIR}/3rdParty/${module_name})
	set(base_dir ${CMAKE_SOURCE_DIR}/3rdParty/${module_name})
	add_subdirectory(${base_dir})
	include_directories(${base_dir}/include)
	target_link_libraries(${main_exe_name} ${module_name})
ENDFOREACH()

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})



