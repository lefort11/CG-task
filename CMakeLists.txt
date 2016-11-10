cmake_minimum_required(VERSION 3.6)
project(mashgraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(ext/glm)

find_package(PkgConfig REQUIRED)


#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#########################################################
# find freeglut
#########################################################
FIND_PATH(Freeglut_INCLUDE_DIRS GL/freeglut.h /opt/X11/include)
FIND_LIBRARY(Freeglut_LIBRARY glut.3 /opt/X11/lib)

include_directories(${Freeglut_INCLUDE_DIRS})

#link_directories(${Freeglut_LIBRARY})
link_directories("/opt/X11/lib")

IF(Freeglut_INCLUDE_DIRS)
    message("*** freeglut inlclude is found!")
ENDIF(Freeglut_INCLUDE_DIRS)

IF(Freeglut_LIBRARY)
    message("*** freeglut lib is found!")
ENDIF(Freeglut_LIBRARY)

#########################################################
# find glew
#########################################################
FIND_PATH(GlEW_INCLUDE_DIRS GL/glew.h /usr/local/include)
FIND_LIBRARY(GlEW_LIBRARY GLEW.2.0.0 /usr/local/lib)

include_directories(${GLEW_INCLUDE_DIRS})
link_directories("/usr/local/lib")

IF(GLEW_INCLUDE_DIRS)
    message("*** Glew inlclude is found!")
ENDIF(GLEW_INCLUDE_DIRS)

IF(GLEW_LIBRARY)
    message("*** Glew lib is found!")
ENDIF(GLEW_LIBRARY)

#########################################################
# find glfw
#########################################################
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#########################################################
# find FreeImage
#########################################################
FIND_PATH(FREEIMAGE_INCLUDE_DIRS freeimage.h /usr/local/include)
FIND_LIBRARY(FREEIMAGE_LIBRARY  freeimage.3.17.0 /usr/local/lib)

include_directories(${FREEIMAGE_INCLUDE_DIRS})
#link_directories("/usr/local/lib")



#set (CMAKE_SHARED_LINKER_FLAGS "-lglut -lX11 -lGL -lGlEW")

set(SOURCE_FILES src/main.cpp src/Window.h src/Engine.h src/Camera.h src/Shader.h)
add_executable(mashgraph ${SOURCE_FILES})
FIND_LIBRARY(COCOA_LIBRARY Cocoa)

target_link_libraries(mashgraph ${FREEIMAGE_LIBRARY})
target_link_libraries(mashgraph ${GLFW_LIBRARIES})
#target_link_libraries(mashgraph ${Freeglut_LIBRARY})
target_link_libraries(mashgraph ${GLEW_LIBRARY}  ${OPENGL_LIBRARIES} ${COCOA_LIBRARY} "-framework Cocoa -framework IOKit -framework CoreVideo")
set_target_properties(mashgraph PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")

