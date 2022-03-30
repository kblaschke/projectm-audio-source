if(libprojectM_VERSION VERSION_LESS 3.1.13)
    message(FATAL_ERROR "libprojectM version 3.13 or higher is required. Version found: ${libprojectM_VERSION}.")
endif()

if(PROJECTM_LINKAGE STREQUAL "shared" AND NOT TARGET libprojectM::shared)
    message(FATAL_ERROR "libprojectM was found, but does not contain a shared library. Try setting PROJECTM_LINKAGE to \"static\".")
endif()

if(PROJECTM_LINKAGE STREQUAL "static" AND NOT TARGET libprojectM::static)
    message(FATAL_ERROR "libprojectM was found, but does not contain a static library. Try setting PROJECTM_LINKAGE to \"shared\".")
endif()

if(SDL2_VERSION VERSION_LESS 2.0.5)
    message(FATAL_ERROR "libSDL version 2.0.5 or higher is required. Version found: ${SDL2_VERSION}.")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND SDL2_VERSION VERSION_LESS 2.0.16)
    message(AUTHOR_WARNING
            "NOTE: libSDL 2.0.15 and lower do not support capture from PulseAudio \"monitor\" devices.\n"
            "It is highly recommended to use at least version 2.0.16!"
            )
endif()
