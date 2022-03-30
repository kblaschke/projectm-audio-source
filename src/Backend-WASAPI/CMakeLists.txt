include(CheckIncludeFiles)

check_include_files("AudioClient.h;audiopolicy.h" WASAPI_INCLUDE_FILES LANGUAGE CXX)

if(NOT WASAPI_INCLUDE_FILES)
    return()
endif()

add_library(projectM-AudioBackend-WASAPI OBJECT
        WASAPIBackend.cpp
        WASAPIBackend.h
        )

target_include_directories(projectM-AudioBackend-WASAPI
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        )

target_link_libraries(projectM-AudioBackend-WASAPI
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

target_sources(projectM-AudioSource
        PRIVATE
        $<TARGET_OBJECTS:projectM-AudioBackend-WASAPI>
        )

add_audio_backend(WASAPI WASAPIBackend)
