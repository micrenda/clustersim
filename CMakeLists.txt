cmake_minimum_required (VERSION 3.0)
project (clustersim)

# The version number.
set (CLUSTERSIM_VERSION_MAJOR 1)
set (CLUSTERSIM_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
  
add_subdirectory (src)
  
add_executable(clustersim src/avrami.c  src/color_map.c  src/common.c  src/graph.c  src/le.c  src/main.c  src/render.c  src/test.c)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package (Lua51 REQUIRED)
if (LUA51_FOUND)
  include_directories(${LUA_INCLUDE_DIR})
  target_link_libraries (clustersim ${LUA_LIBRARIES})
endif (LUA51_FOUND)

find_package (PNG REQUIRED)
if (PNG_FOUND)
  include_directories(${PNG_INCLUDE_DIRS})
  target_link_libraries (clustersim ${PNG_LIBRARIES})
endif (PNG_FOUND)

find_package(CBLAS REQUIRED)
if (CBLAS_FOUND)
  include_directories(${CBLAS_INCLUDE_DIR})
  target_link_libraries (clustersim ${CBLAS_LIBRARIES})
endif (CBLAS_FOUND)

find_package(GSL REQUIRED) 
if (GSL_FOUND)
  include_directories(${GSL_INCLUDES})
  target_link_libraries (clustersim ${GSL_LIBRARIES})
endif (GSL_FOUND)

find_package(Config REQUIRED) 
if (CONFIG_FOUND)
  include_directories(${CONFIG_INCLUDE_DIR})
  target_link_libraries (clustersim ${CONFIG_LIBRARIES})
endif (CONFIG_FOUND)

find_package(Check REQUIRED) 
if (CHECK_FOUND)
  include_directories(${CHECK_INCLUDE_DIRS})
  target_link_libraries (clustersim ${CHECK_LIBRARIES})
endif (CHECK_FOUND)

find_package(OpenMP REQUIRED) 
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif (OPENMP_FOUND)

macro(use_c11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11")
  else ()
    set (CMAKE_C_STANDARD 11)
  endif ()
endmacro(use_c11)

use_c11()


#add_custom_command(TARGET clustersim POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/util/plot/graph-grow-linear.ct2		    $<TARGET_FILE_DIR:clustersim>)
#add_custom_command(TARGET clustersim POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/util/plot/graph-grow-linear-fit.ct2 		$<TARGET_FILE_DIR:clustersim>)
#add_custom_command(TARGET clustersim POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/util/plot/graph-grow-log.ct2  		    $<TARGET_FILE_DIR:clustersim>)
#add_custom_command(TARGET clustersim POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/util/plot/graph-grow-log-fit.ct2	 		$<TARGET_FILE_DIR:clustersim>)

install(TARGETS clustersim 						RUNTIME DESTINATION bin)
install(FILES util/plot/graph-grow-linear.ct2 		DESTINATION plot)
install(FILES util/plot/graph-grow-linear-fit.ct2 	DESTINATION plot)
install(FILES util/plot/graph-grow-log.ct2	 		DESTINATION plot)
install(FILES util/plot/graph-grow-log-fit.ct2 		DESTINATION plot)



