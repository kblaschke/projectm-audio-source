add_library(projectM-AudioBackend-Fake OBJECT
        FakeBackend.cpp
        FakeBackend.h
        FakeCaptureThread.cpp
        FakeCaptureThread.h
        )

target_include_directories(projectM-AudioBackend-Fake
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        )

target_link_libraries(projectM-AudioBackend-Fake
        PUBLIC
        libprojectM::${PROJECTM_LINKAGE}
        )

target_sources(projectM-AudioSource
        PRIVATE
        $<TARGET_OBJECTS:projectM-AudioBackend-Fake>
        )

add_audio_backend(Fake FakeBackend)
