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

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>")

# ==============================================================================
# Precompiled Library Helper
# ==============================================================================
function(add_precompiled_lib TARGET_NAME LIB_FOLDER LIB_NAME)
    add_library(${TARGET_NAME} SHARED IMPORTED GLOBAL)
    
    set(LIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_FOLDER}")
    
    set_target_properties(${TARGET_NAME} PROPERTIES
        IMPORTED_IMPLIB "${LIB_ROOT}/lib/${LIB_NAME}.lib"
        IMPORTED_LOCATION "${LIB_ROOT}/bin/${LIB_NAME}.dll"
        INTERFACE_INCLUDE_DIRECTORIES "${LIB_ROOT}/include"
    )
endfunction()

# Register precompiled dependencies
add_precompiled_lib(SDL3::SDL3 "SDL" "SDL3")
add_precompiled_lib(SDL3_image::SDL3_image "SDL_image" "SDL3_image")

# ==============================================================================
# Sources
# ==============================================================================
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes/*.c"
)

if (WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/app.rc")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/app.rc")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

# Precompiled headers
if (MSVC)
    target_precompile_headers(${PROJECT_NAME} PRIVATE
        "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h>"
    )
endif()

# ==============================================================================
# Include Directories
# ==============================================================================
set(ALL_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/scenes"
)

file(GLOB_RECURSE SUBDIRS_INCLUDE LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
file(GLOB_RECURSE SUBDIRS_SCENES LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/scenes/*")

foreach(DIR ${SUBDIRS_INCLUDE} ${SUBDIRS_SCENES})
    if(IS_DIRECTORY ${DIR})
        list(APPEND ALL_INCLUDE_DIRS ${DIR})
    endif()
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${ALL_INCLUDE_DIRS})

# Link imported targets
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "FLV FNF - Dev"
)

if (WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE "/ENTRY:mainCRTStartup")

    # Post-build: Copy precompiled runtime DLLs to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL/bin/SDL3.dll"
            "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL_image/bin/SDL3_image.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Deploying precompiled DLLs to output directory..."
    )
endif()

# Post-build: Copy assets folder
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
        COMMENT "Deploying assets to output directory..."
    )
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)