cmake_minimum_required(VERSION 3.6)
project(mashgraph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(ext/glm)



#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(WIN32)
    #########################################################
    # find glew
    #########################################################
    FIND_PATH(GLEW_INCLUDE_DIRS GL/glew.h ${CMAKE_SOURCE_DIR}/ext/Bin/glew-2.0.0/include)
    FIND_LIBRARY(GLEW_LIBRARY glew32 ${CMAKE_SOURCE_DIR}/ext/Bin/glew-2.0.0/lib/Release/Win32)

    include_directories(${GLEW_INCLUDE_DIRS})
    link_directories(${CMAKE_SOURCE_DIR}/ext/Bin/glew-2.0.0/lib/Release/Win32)
    link_directories(${CMAKE_SOURCE_DIR}/ext/Bin/glew-2.0.0/Bin/Release/Win32)

    #########################################################
    # find glfw
    #########################################################
    FIND_PATH(GLFW_INCLUDE_DIRS GLFW/glfw3.h ${CMAKE_SOURCE_DIR}/ext/Bin/glfwWIN32/include)
    FIND_LIBRARY(GLFW_LIBRARIES glfw3 ${CMAKE_SOURCE_DIR}/ext/Bin/glfwWIN32/lib-vc2015)

    include_directories(${GLFW_INCLUDE_DIRS})
    link_directories(${CMAKE_SOURCE_DIR}/ext/Bin/glfwWIN32/lib-vc2015)

    #########################################################
    # find FreeImage
    #########################################################
    FIND_PATH(FREEIMAGE_INCLUDE_DIRS freeimage.h ${CMAKE_SOURCE_DIR}/ext/Bin/FreeImage/Dist/x32)
    FIND_LIBRARY(FREEIMAGE_LIBRARY FreeImage ${CMAKE_SOURCE_DIR}/ext/Bin/FreeImage/Dist/x32)

    include_directories(${FREEIMAGE_INCLUDE_DIRS})
    link_directories(${CMAKE_SOURCE_DIR}/ext/Bin/FreeImage/Dist/x32)

endif(WIN32)

if(APPLE)

    find_package(PkgConfig REQUIRED)

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
    FIND_PACKAGE(GLEW REQUIRED) #some bug here
    FIND_PATH(GLEW_INCLUDE_DIRS GL/glew.h /usr/local/include)
    FIND_LIBRARY(GLEW_LIBRARY GLEW.2.0.0 /usr/local/lib)

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

    IF(FREEIMAGE_INCLUDE_DIRS)
        message("*** FreeImage inlclude is found!")
    ENDIF(FREEIMAGE_INCLUDE_DIRS)

    IF(FREEIMAGE_LIBRARY)
        message("*** FreeImage lib is found!")
    ENDIF(FREEIMAGE_LIBRARY)

    include_directories(${FREEIMAGE_INCLUDE_DIRS})
    #link_directories("/usr/local/lib")
endif(APPLE)



#set (CMAKE_SHARED_LINKER_FLAGS "-lglut -lX11 -lGL -lGlEW")

set(SOURCE_FILES src/main.cpp src/Window.h src/Engine.h src/Camera.h src/Shader.h src/TangentSpace.h src/Vertex.h)
add_executable(mashgraph ${SOURCE_FILES})
FIND_LIBRARY(COCOA_LIBRARY Cocoa)


target_link_libraries(mashgraph ${FREEIMAGE_LIBRARY})
target_link_libraries(mashgraph ${GLFW_LIBRARIES})
if(APPLE)
    target_link_libraries(mashgraph ${COCOA_LIBRARY} "-framework Cocoa -framework IOKit -framework CoreVideo")
endif(APPLE)
target_link_libraries(mashgraph ${GLEW_LIBRARY}  ${OPENGL_LIBRARIES})
set_target_properties(mashgraph PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")

