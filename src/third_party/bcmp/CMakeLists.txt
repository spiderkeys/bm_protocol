cmake_minimum_required(VERSION 3.13)

project(bcmp VERSION 0.0.1 LANGUAGES C)

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(LIBRARY_NAME "bcmp")

# Options
option(WITH_FREERTOS_LWIP "Build for FreeRTOS with LWIP network stack" OFF)
set(BCMP_DEBUG 0 CACHE STRING "Sets the BCMP_DEBUG definition")

# Compile definitions
set(COMPILE_DEFINITIONS "")
list(APPEND COMPILE_DEFINITIONS "BCMP_DEBUG=${BCMP_DEBUG}")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND COMPILE_DEFINITIONS "BCMP_LINUX")
elseif(CMAKE_SYSTEM_NAME MATCHES "Generic")
  if(WITH_FREERTOS_LWIP)
    list(APPEND COMPILE_DEFINITIONS "BCMP_FREERTOS_LWIP")
  else()
    message(FATAL_ERROR "BCMP is currently only available for FreeRTOS Generic Platform")
  endif()
else()
  message(FATAL_ERROR "BCMP is not yet available on ${CMAKE_SYSTEM_NAME} platform")
  return()
endif()

# Compile Options
set(COMPILE_OPTIONS "")
if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  if(UNIX)
    list(APPEND COMPILE_OPTIONS -c -Wall -Wextra -Werror -Wshadow -Wpedantic -Wunused -Wstrict-prototypes -pipe -g -O0)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Generic")
    list(APPEND COMPILE_OPTIONS -Wall -Wextra -Wno-unused-parameter -Wmissing-prototypes -pipe -g -O0)
  endif()
elseif(CMAKE_BUILD_TYPE MATCHES "RELEASE")
  if(UNIX)
    list(APPEND COMPILE_OPTIONS -pipe -O3)
  elseif(CMAKE_SYSTEM_NAME MATCHES "Generic")
    list(APPEND COMPILE_OPTIONS -pipe -O3)
  endif()
endif()

# Create Library Target
add_library(${LIBRARY_NAME} STATIC)

# Enforce C11 support
target_compile_features(${LIBRARY_NAME} 
PUBLIC 
    c_std_11
)

target_compile_definitions(${LIBRARY_NAME} 
PUBLIC
    ${COMPILE_DEFINITIONS}
)

target_compile_options(${LIBRARY_NAME} 
PUBLIC
    ${COMPILE_OPTIONS}
)

target_include_directories(${LIBRARY_NAME} 
PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

set(BCMP_SOURCES
  "src/api/api.c"
)

if(WITH_FREERTOS_LWIP)
  file (GLOB BCMP_SOURCES_FREERTOS_LWIP "src/system/freertos_lwip/*.c")
  list(APPEND BCMP_SOURCES ${BCMP_SOURCES_FREERTOS_LWIP})
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "BSD" OR POSIX_COMPATIBLE)
  file (GLOB BCMP_SOURCES_UNIX "src/system/unix/*.c" "src/system/unix/link/*.c")
  list(APPEND BCMP_SOURCES ${BCMP_SOURCES_UNIX})
endif()

target_sources(${LIBRARY_NAME} 
PRIVATE 
    ${BCMP_SOURCES}
)

# Install only if current source dir is the project root
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${LIBRARY_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  COMPONENT Library
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/bcmp
  DESTINATION include
  COMPONENT Headers
)

endif()