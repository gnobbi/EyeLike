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

MACRO(ADD_MSVC_PRECOMPILED_HEADER precompiledSrc srcs)
if (MSVC)
    foreach( src_file ${srcs} )
        set_source_files_properties(
            ${src_file}
            PROPERTIES
            COMPILE_FLAGS "/Yuprecompiled.h"
            )
    endforeach( src_file ${srcs} )
	
	set_source_files_properties(${precompiledSrc}
        PROPERTIES
        COMPILE_FLAGS "/Ycprecompiled.h"
        )
	list(APPEND srcs ${precompiledSrc})
endif (MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)