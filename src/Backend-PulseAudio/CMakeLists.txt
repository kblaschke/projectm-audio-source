if(NOT ENABLE_PULSEAUDIO)
    return()
endif()

add_library(projectM-AudioBackend-PulseAudio OBJECT
        PulseAudioBackend.cpp
        PulseAudioBackend.h
        PulseAudioDevice.cpp
        PulseAudioDevice.h
        PulseAudioServerConnection.cpp
        PulseAudioServerConnection.h
        )

target_include_directories(projectM-AudioBackend-PulseAudio
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        )

target_link_libraries(projectM-AudioBackend-PulseAudio
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

target_sources(projectM-AudioSource
        PRIVATE
        $<TARGET_OBJECTS:projectM-AudioBackend-PulseAudio>
        )

add_audio_backend(PulseAudio PulseAudioBackend)
