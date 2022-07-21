project(Crawler.Utility LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

file(GLOB_RECURSE HEADERS "include/${PROJECT_NAME}/*")
file(GLOB_RECURSE SOURCES "src/*.h" "src/*.cpp")

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED
    ${HEADERS}
    ${SOURCES}
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_MACRO_NAME UTILITY_API
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}/API.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    "${CMAKE_BINARY_DIR}/include"
)
