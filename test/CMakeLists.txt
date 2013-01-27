cmake_minimum_required(VERSION 2.6)

#macro(add_python_target tgt)
#  foreach(file ${ARGN})
#    set(OUT ${CMAKE_CURRENT_BINARY_DIR}/${file}.pyo)
#    list(OUT_FILES APPEND ${OUT})
#    add_custom_command(OUTPUT ${OUT}
#        COMMAND <python command you use to byte-compile .py file>)
#  endforeach()

#  add_custom_target(${tgt} ALL
#    DEPENDS ${OUT_FILES}
#endmacro()


# list of C++ executables 
set( EXEC sphere_vector_test.cpp)
add_executable(sphere_vector_test ${EXEC})


# list of executables implemented in scripting language
#set(SCRIPTS displayPoints.py )
#add_python_target( displayPoints ${SCRIPTS} )

