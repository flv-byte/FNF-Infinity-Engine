cmake_minimum_required(VERSION 3.16)

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,\
$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,\
$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(FNF_FLV LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL" EXCLUDE_FROM_ALL)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL_image" EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SOURCES 
    CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

if (WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app.rc")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app.rc")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
set(ALL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
foreach(DIR ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${DIR})
        list(APPEND ALL_INCLUDE_DIRS ${DIR})
    endif()
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${ALL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "FLV FNF - Dev"
)

if (WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE "/ENTRY:mainCRTStartup")
endif()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)