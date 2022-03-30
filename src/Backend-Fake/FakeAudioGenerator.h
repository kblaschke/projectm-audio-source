#pragma once

#include <libprojectM/projectM.h>

#include <atomic>
#include <random>

namespace projectMAudio {

/**
 * @brief Background thread class for generating fake audio data
 *
 * Each function will run in a thread and generates a different type of fake audio.
 * Which one is used depends on the output device selection of the fake backend.
 */
class FakeAudioGenerator
{
public:

    explicit FakeAudioGenerator(projectm_handle projectMInstance);

    /**
     * @brief Generates random noise in a loop until terminated.
     */
    void GenerateRandomNoise();

    /**
     * @brief Generates rhythmically pulsing sine waves in a loop until terminated.
     */
    void GenerateBeat();

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