### projectM frontend audio backend library

# Check whether we have dlopen()/dlsym() or Load[Packaged]Library()/GetProcAddress() available,
# then select the proper implementation
include(CheckSymbolExists)
check_symbol_exists(dlopen "dlfcn.h" AUDIO_SOURCE_HAVE_DLOPEN)
check_symbol_exists(dlsym "dlfcn.h" AUDIO_SOURCE_HAVE_DLSYM)
check_symbol_exists(LoadLibrary "libloaderapi.h" AUDIO_SOURCE_HAVE_LOADLIBRARY)
check_symbol_exists(LoadPackagedLibrary "winbase.h" AUDIO_SOURCE_HAVE_LOADPACKAGEDLIBRARY)
check_symbol_exists(GetProcAddress "libloaderapi.h" AUDIO_SOURCE_HAVE_GETPROCADDRESS)

#if(AUDIO_SOURCE_HAVE_DLOPEN AND AUDIO_SOURCE_HAVE_DLSYM)
set(AUDIO_SOURCE_LIBRARY_LOAD_IMPL dlopen)
#elseif((AUDIO_SOURCE_HAVE_LOADLIBRARY OR AUDIO_SOURCE_HAVE_LOADPACKAGEDLIBRARY) AND AUDIO_SOURCE_HAVE_GETPROCADDRESS)
#    set(AUDIO_SOURCE_LIBRARY_LOAD_IMPL windows)
#else()
# message(FATAL_ERROR "projectM-AudioSource: Could not determine dynamic library loader interface.\n"
#         "Currently, only systems using dlopen() and Load[Packaged]Library() are supported.")
#endif()

add_library(projectM-AudioSource STATIC
        "${CMAKE_CURRENT_BINARY_DIR}/BackendList_Generated.h"
        projectMAudioSource/Device.cpp
        projectMAudioSource/Device.h
        projectMAudioSource/Backend.cpp
        projectMAudioSource/Backend.h
        projectMAudioSource/DynamicLibraryLoader/DynamicLibraryLoader.cpp
        projectMAudioSource/DynamicLibraryLoader/DynamicLibraryLoader.h
        projectMAudioSource/DynamicLibraryLoader/DynamicLibraryLoaderImpl_${AUDIO_SOURCE_LIBRARY_LOAD_IMPL}.cpp
        projectMAudioSource/DynamicLibraryLoader/DynamicLibraryLoaderImpl_${AUDIO_SOURCE_LIBRARY_LOAD_IMPL}.h
        )

target_include_directories(projectM-AudioSource
        PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}"
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:projectMAudioSource>
        )

set_target_properties(projectM-AudioSource PROPERTIES
        OUTPUT_NAME projectMAudioSource
        )

target_link_libraries(projectM-AudioSource
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

# This is the template code to return a new backend instance. Replace "#NAME#" with the backend name and
# "#CLASS#" with the class to be instantiated.
set(AUDIO_BACKEND_FACTORY_TEMPLATE "    if (backendName == \"#NAME#\")\n    {\n        return std::make_unique<#CLASS#>(projectMInstance);\n    }\n")

# Backend CMakeLists.txt must populate these variables using add_audio_backend()
set(AUDIO_BACKEND_INCLUDE_LIST "")
set(AUDIO_BACKEND_NAME_LIST "")
set(AUDIO_BACKEND_FACTORY_LIST "")

macro(add_audio_backend _name _class)
    set(AUDIO_BACKEND_INCLUDE_LIST "${AUDIO_BACKEND_INCLUDE_LIST}#include \"${CMAKE_CURRENT_SOURCE_DIR}/${_class}.h\"\n" PARENT_SCOPE)
    string(REPLACE "#NAME#" "${_name}" ${_name}_FACTORY "${AUDIO_BACKEND_FACTORY_TEMPLATE}")
    string(REPLACE "#CLASS#" "${_class}" ${_name}_FACTORY "${${_name}_FACTORY}")
    set(AUDIO_BACKEND_NAME_LIST ${AUDIO_BACKEND_NAME_LIST} "\"${_name}\"" PARENT_SCOPE)
    set(AUDIO_BACKEND_FACTORY_LIST "${AUDIO_BACKEND_FACTORY_LIST}${${_name}_FACTORY}" PARENT_SCOPE)
endmacro()

add_subdirectory(Backend-Fake)
add_subdirectory(Backend-JACK)
add_subdirectory(Backend-PulseAudio)
add_subdirectory(Backend-SDL2)
add_subdirectory(Backend-WASAPI)

list(LENGTH AUDIO_BACKEND_NAME_LIST AUDIO_BACKEND_COUNT)
list(JOIN AUDIO_BACKEND_NAME_LIST ",\n    " AUDIO_BACKEND_NAME_LIST)

configure_file(projectMAudioSource/BackendList_Generated.h.in
        "${CMAKE_CURRENT_BINARY_DIR}/BackendList_Generated.h"
        @ONLY
        )
