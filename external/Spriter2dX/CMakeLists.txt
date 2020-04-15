cmake_minimum_required(VERSION 2.8)
project(Spriter2dX)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

add_subdirectory(SpriterPlusPlus/spriterengine)

set(SOURCE_FILES
        src/ccimagefile.cpp
        src/ccsoundfile.cpp
        src/ccfilefactory.cpp
        src/ccsoundobjectinforeference.cpp
        src/ccobjectfactory.cpp
        src/cctriggerobjectinfo.cpp
        src/ccboxinstanceinfo.cpp
        src/ccboneinstanceinfo.cpp
        src/ccpointinstanceinfo.cpp
        src/tinyxmlspriterfileattributewrapper.cpp
        src/tinyxmlspriterfiledocumentwrapper.cpp
        src/tinyxmlspriterfileelementwrapper.cpp
        src/AnimationNode.cpp
)

# find_package(Cocos2dX REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/SpriterPlusPlus/spriterengine ${COCOS2DX_ROOT_PATH})

add_library(spriter2dx STATIC ${SOURCE_FILES})

target_link_libraries(spriter2dx spriterengine cocos2d)

