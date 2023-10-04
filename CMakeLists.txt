cmake_minimum_required(VERSION 3.5)

project(pathfinding_test_assignment VERSION 1.0 LANGUAGES CXX)

# Forbid in-source build
if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(SEND_ERROR "In-source building prohibited")
endif()

# Turn on automatic invocation of the MOC and UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Enable Windows platform
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Set path to *.ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/UI)

# Find Qt5 libraries
find_package(Qt5 REQUIRED COMPONENTS Widgets LinguistTools)

# Include "Headers" directory
include_directories(Headers)

# Set project files
set(PROJECT_SOURCES Sources/Main.cxx
                    Headers/MainWindow.hxx
                    Sources/MainWindow.cxx
                    Headers/PathfindScene.hxx
                    Sources/PathfindScene.cxx
)

# Set other files
set(TS_FILES pathfinding_test_assignment_ru_RU.ts)
set(UI_FILES UI/MainWindow.ui)

# Set target executable
add_executable(pathfinding_test_assignment
    ${PROJECT_SOURCES} ${TS_FILES} ${UI_FILES}
)

# Create translation
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# Set linked libraries
target_link_libraries(pathfinding_test_assignment PRIVATE Qt5::Widgets)

