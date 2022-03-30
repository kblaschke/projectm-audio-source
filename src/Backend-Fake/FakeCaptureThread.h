#pragma once

#include <libprojectM/projectM.h>

#include <atomic>
#include <random>

namespace projectMAudio {

/**
 * @brief Background thread for generating fake audio data
 */
class FakeCaptureThread
{
public:

    explicit FakeCaptureThread(projectm_handle projectMInstance);

    /**
     * @brief Generates fake audio in a loop until terminated.
     */
    void GenerateFakeAudio();

    /**
     * @brief Stops the thread.
     */
    void Stop();

private:
    std::atomic_bool _stopped{ false };
    projectm_handle _projectMInstance;
    std::default_random_engine _random;
};


} // namespace project