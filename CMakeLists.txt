cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(CVP-impl VERSION 1.0)

# Function to prepend the subdirectory to source files in subdirectories
FUNCTION(PREPEND var )
   SET(listVar "")
   FOREACH(f ${${var}})
       LIST(APPEND listVar "${CMAKE_CURRENT_SOURCE_DIR}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

add_subdirectory(src)

add_executable(cvp ${CVP_SRC})


