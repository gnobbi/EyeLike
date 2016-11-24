cmake_minimum_required(VERSION 2.8)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

project(EyeLike)
set(BUILD_SHARED_LIBS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# EyeLike_exe
set(EyeLike_exe EyeLikeApp)
file(GLOB_RECURSE EyeLike_srcs *.cpp)


add_executable(${EyeLike_exe} ${EyeLike_srcs})
include_directories(include)
include_directories(src)

# 3rdParty libs
SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR}/3rdParty)
message(warning ${SUBDIRS})

FOREACH(subdir ${SUBDIRS})
	message(warning ${CMAKE_SOURCE_DIR}/3rdParty/${subdir})
	set(base_dir ${CMAKE_SOURCE_DIR}/3rdParty/${subdir})
	add_subdirectory(${base_dir})
	include_directories(${mybase_dir}/include)
	link_directories(${mybase_dir}/lib)
ENDFOREACH()
	


# set(mybase_dir ${CMAKE_SOURCE_DIR}/3rdParty/mybase)
# set(mycv_dir ${CMAKE_SOURCE_DIR}/3rdParty/mycv)
# set(mygui_dir ${CMAKE_SOURCE_DIR}/3rdParty/mygui)
# 
# add_subdirectory(${mybase_dir})
# add_subdirectory(${mycv_dir})
# add_subdirectory(${mygui_dir})
# 
# include_directories(${mybase_dir}/include)
# include_directories(${mycv_dir}/include)
# include_directories(${mygui_dir}/include)
# 
# link_directories(${mybase_dir}/lib)
# link_directories(${mycv_dir}/lib)
# link_directories(${mygui_dir}/lib)

target_link_libraries(${EyeLike_exe} mybase)
target_link_libraries(${EyeLike_exe} mycv)
target_link_libraries(${EyeLike_exe} mygui)


