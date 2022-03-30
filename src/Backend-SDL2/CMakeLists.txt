if(NOT ENABLE_SDL)
    return()
endif()

add_library(projectM-AudioBackend-SDL2 OBJECT
        SDL2Backend.cpp
        SDL2Backend.h
        )

target_include_directories(projectM-AudioBackend-SDL2
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        )

target_link_libraries(projectM-AudioBackend-SDL2
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

target_sources(projectM-AudioSource
        PRIVATE
        $<TARGET_OBJECTS:projectM-AudioBackend-SDL2>
        )

add_audio_backend(SDL2 SDL2Backend)
