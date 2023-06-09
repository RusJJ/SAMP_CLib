cmake_minimum_required(VERSION 3.0)
project(clib)

set(PLUGIN_VERSION "1.0.0")
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_definitions("/MP")
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")

set(SAMP_SDK_ROOT "${PROJECT_SOURCE_DIR}/samp-plugin-sdk")
find_package(SAMPSDK REQUIRED)
include_directories(${SAMPSDK_DIR})
include_directories(${SAMPSDK_DIR}/amx)
include_directories(${PROJECT_SOURCE_DIR}/sampgdk/include)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY True)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY True)

add_subdirectory(src)

set(CPACK_PACKAGE_VERSION ${PLUGIN_VERSION})

if(COMMIT_ID)
	string(TIMESTAMP CURRENT_DATE "%Y%m%d")
	set(PACKAGE_FILE_NAME plugin-${PLUGIN_VERSION}-${CURRENT_DATE}-${COMMIT_ID})
else()
	set(PACKAGE_FILE_NAME plugin-${PLUGIN_VERSION})
endif()

set(CPACK_OUTPUT_FILE_PREFIX package/${PACKAGE_FILE_NAME})

if(WIN32)
	set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME}-win32)
	set(CPACK_GENERATOR ZIP)
else()
	set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME}-linux)
	set(CPACK_GENERATOR TGZ)
endif()

if(CPACK_OUTPUT_FILE_POSTFIX)
	string(TOLOWER "${CPACK_OUTPUT_FILE_POSTFIX}" CPACK_OUTPUT_FILE_POSTFIX)
	set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_FILE_NAME}-${CPACK_OUTPUT_FILE_POSTFIX})
endif()

include(CPack)
