project(Crawler.Gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo")
set(BUILD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/x64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Quick
    Concurrent
)

file(GLOB_RECURSE HEADERS "include/${PROJECT_NAME}/*")
file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

qt5_add_resources(RESOURCES src/qml/qml.qrc)

include_directories(searcher/controller)

add_executable(MultiWebSearcher
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
)

target_link_libraries(MultiWebSearcher PRIVATE
    # Qt
    Qt5::Core
    Qt5::Quick

    # Internal
    Crawler.Core
    Crawler.Logger
)

target_include_directories(MultiWebSearcher PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}"
    "${CMAKE_BINARY_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)
