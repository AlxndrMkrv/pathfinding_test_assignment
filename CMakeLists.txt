cmake_minimum_required(VERSION 3.5)

################################################################################
#                                Project setup                                 #

project(pathfinding_test_assignment VERSION 1.0 LANGUAGES CXX)

# Forbid in-source build
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(SEND_ERROR "In-source building prohibited")
endif()

# Turn off automatic invocation of the MOC and UIC
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)

# Enable Windows platform
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Set path to *.ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/UI)

# Find Qt5 libraries
find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent LinguistTools)

# Create translation
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

################################################################################
#                                  Build setup                                 #

# Include "Headers" directory
include_directories(Headers)

set(GRAPH_SOURCES Headers/Cell.hxx
                  Headers/Graph.hxx
                  Sources/Graph.cxx
                  Sources/Graph_DFS.cxx
)

add_library(graph_static STATIC ${GRAPH_SOURCES})


# Set project files
set(PROJECT_SOURCES Sources/Main.cxx
                    Headers/MainWindow.hxx
                    Sources/MainWindow.cxx

                    Headers/MatrixScene.hxx
                    Sources/MatrixScene.cxx
                    Headers/ZoomView.hxx
                    Sources/ZoomView.cxx
                    Headers/MatrixCell.hxx
                    #Sources/MatrixCell.cxx
                    Headers/CellsNumberValidator.hxx
                    Headers/Settings.hxx
                    Sources/Settings.cxx
)

# Set other files
set(TS_FILES pathfinding_test_assignment_ru_RU.ts)
set(UI_FILES UI/MainWindow.ui)

# Set target executable
set(PROJECT_APP pathfinding_test_assignment)
add_executable(${PROJECT_APP}
               ${PROJECT_SOURCES}
               ${TS_FILES}
               ${UI_FILES}
               Headers/MatrixRectItem.hxx
)
set_target_properties(${PROJECT_APP} PROPERTIES
                      AUTOMOC ON
                      AUTOUIC ON
)
target_compile_definitions(${PROJECT_APP} PRIVATE KNOW_WHAT_TO_DO)

# Set linked libraries
target_link_libraries(pathfinding_test_assignment PRIVATE
                      Qt5::Widgets
                      graph_static
)

################################################################################
#                                    Testing                                   #

enable_testing()
add_subdirectory(Tests)
