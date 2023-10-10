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
set(CMAKE_AUTORCC OFF)

# Enable Windows platform
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Set path to *.ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/UI)

# Find Qt5 libraries
find_package(Qt5 REQUIRED COMPONENTS Widgets Concurrent LinguistTools)

# Include "Headers" directory
include_directories(Headers)


################################################################################
#                             Graph static library                             #

# Add Graph static library
set(GRAPH_SOURCES Headers/Cell.hxx
                  Headers/Graph.hxx
                  Sources/Graph.cxx
                  Sources/Graph_DFS.cxx
)

add_library(graph_static STATIC ${GRAPH_SOURCES})


################################################################################
#                                 Graph tests                                  #

enable_testing()
add_subdirectory(Tests)


################################################################################
#                               GUI Application                                #

# Set project files
set(PROJECT_SOURCES Sources/Main.cxx
                    Headers/Settings.hxx
                    Sources/Settings.cxx
                    Headers/MainWindow.hxx
                    Sources/MainWindow.cxx
                    Headers/ZoomView.hxx
                    Sources/ZoomView.cxx
                    Headers/MatrixScene.hxx
                    Sources/MatrixScene.cxx
                    Headers/MatrixRectItem.hxx
                    Headers/MatrixCell.hxx
                    Headers/CellsNumberValidator.hxx
)

# UI file
set(UI_FILE UI/MainWindow.ui)

# Create translation from given ts file and save it in build/i18n
set(TS_FILE ${PROJECT_NAME}_ru_RU.ts)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/i18n)
set_source_files_properties(${TS_FILE} PROPERTIES OUTPUT_LOCATION i18n)
qt5_create_translation(QM_FILE ${PROJECT_SOURCES} ${UI_FILE} ${TS_FILE})

# Copy qrc file from source to build dir and add to project
file(CREATE_LINK ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.qrc
     ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.qrc SYMBOLIC
)
qt5_add_resources(RC_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.qrc)

# Set target executable
add_executable(${PROJECT_NAME}
               ${PROJECT_SOURCES}
               ${TS_FILE}
               ${QM_FILE}
               ${UI_FILE}
               ${RC_FILE}
)

# Enable automoc & autouic for GUI only
set_target_properties(${PROJECT_NAME} PROPERTIES
                      AUTOMOC ON
                      AUTOUIC ON
                      AUTORCC ON
)

# Suppress the error in MatrixScene.hxx about a Graph size limitation
target_compile_definitions(${PROJECT_NAME} PRIVATE KNOW_WHAT_TO_DO)

# Set linked libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets graph_static)

