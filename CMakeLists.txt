cmake_minimum_required(VERSION 2.8)

# include makros
add_subdirectory(tools/cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EyeLike CXX)
set(BUILD_SHARED_LIBS ON)

# EyeLike_exe
set(exe_name EyeLikeApp)
message("Start " ${exe_name})
file(GLOB_RECURSE EyeLike_srcs src/*.cpp)

add_executable(${exe_name} ${EyeLike_srcs})
include_directories(include)
include_directories(src)

# 3rdParty libs
SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR}/3rdParty)
FOREACH(subdir ${SUBDIRS})
	message("   Found 3rdParty lib @ " ${CMAKE_SOURCE_DIR}/3rdParty/${subdir})
	set(base_dir ${CMAKE_SOURCE_DIR}/3rdParty/${subdir})
	add_subdirectory(${base_dir})
	include_directories(${base_dir}/include)
	link_directories(${base_dir}/lib)
ENDFOREACH()

target_link_libraries(${exe_name} mybase)
target_link_libraries(${exe_name} mycv)
target_link_libraries(${exe_name} mygui)

message("End " ${exe_name})


