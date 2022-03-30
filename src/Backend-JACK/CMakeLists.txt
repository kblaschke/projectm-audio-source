if(NOT ENABLE_JACK)
    return()
endif()

add_library(projectM-AudioBackend-JACK OBJECT
        JACKBackend.cpp
        JACKBackend.h
        )

target_include_directories(projectM-AudioBackend-JACK
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        )

target_link_libraries(projectM-AudioBackend-JACK
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

target_sources(projectM-AudioSource
        PRIVATE
        $<TARGET_OBJECTS:projectM-AudioBackend-JACK>
        )

add_audio_backend(JACK JACKBackend)
