set(PAECS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories (${PAECS_SRC_DIR})
file(GLOB_RECURSE SRC_FILES ${PAECS_SRC_DIR}/*.cpp ${PAECS_SRC_DIR}/*.cc)
# list(APPEND IMGUI_PUBLIC_HEADERS
#         "${IMGUI_SRC_DIR}/imgui.h"
#         )

# list(APPEND IMGUI_PRIVATE_HEADERS
#         "${IMGUI_SRC_DIR}/imgui_internal.h"
#         "${IMGUI_SRC_DIR}/imconfig.h"
#         "${IMGUI_SRC_DIR}/stb_rect_pack.h"
#         "${IMGUI_SRC_DIR}/stb_textedit.h"
#         "${IMGUI_SRC_DIR}/stb_truetype.h"
#         )

#     list(APPEND IMGUI_SOURCES
#         "${IMGUI_SRC_DIR}/imgui.cpp"
#         "${IMGUI_SRC_DIR}/imgui_draw.cpp"
#         "${IMGUI_SRC_DIR}/imgui_demo.cpp"
#         ${CRYPTO_PUBLIC_HEADERS}
#         ${CRYPTO_PRIVATE_HEADERS}
#         )

# list(APPEND IMGUI_PUBLIC_INCLUDE_DIRS
#         ${IMGUI_SRC_DIR}
#         )

# list(APPEND IMGUI_PUBLIC_LIBRARIES)

set(NAME paecs)
add_library(${NAME} STATIC ${SRC_FILES})
# SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:"libcmt.lib")
# if (MSVC)
#     if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
#         foreach (flag CMAKE_C_FLAGS
#                       CMAKE_C_FLAGS_DEBUG
#                       CMAKE_C_FLAGS_RELEASE
#                       CMAKE_C_FLAGS_MINSIZEREL
#                       CMAKE_C_FLAGS_RELWITHDEBINFO)

#             if (${flag} MATCHES "/MD")
#                 string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
#             endif()
#             if (${flag} MATCHES "/MDd")
#                 string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
#             endif()

#         endforeach()
#     endif()
# endif()
# if(MSVC)
#     # message(${CMAKE_BUILD_TYPE})
#     IF (CMAKE_BUILD_TYPE MATCHES "Debug")
#         set_target_properties( ${NAME} PROPERTIES
#             COMPILE_FLAGS "/MTd"
#         )
#     ELSE()
#         set_target_properties( ${NAME} PROPERTIES
#             COMPILE_FLAGS "/MT"
#         )
#     ENDIF()
    
# endif()
    

# target_link_libraries(${NAME} PUBLIC ${IMGUI_PUBLIC_LIBRARIES})
# target_include_directories(${NAME}
#         PUBLIC  ${IMGUI_PUBLIC_INCLUDE_DIRS}
#         PRIVATE ${IMGUI_PRIVATE_INCLUDE_DIRS}
#         )
