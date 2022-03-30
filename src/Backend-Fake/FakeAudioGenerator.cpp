#include "FakeAudioGenerator.h"

#include <cmath>
#include <thread>

using namespace std::chrono;

namespace projectMAudio {

FakeAudioGenerator::FakeAudioGenerator(projectm_handle projectMInstance)
    : _projectMInstance(projectMInstance)
{
}

void FakeAudioGenerator::GenerateRandomNoise()
{
    short pcmData[2][512];

    _stopped = false;

    while (!_stopped)
    {
        for (int i = 0; i < 512; i++)
        {
            short neg = i % 2 == 0 ? 1 : -1;

            pcmData[0][i] = neg * static_cast<short>((static_cast<float>(_random()) /
                                                      (static_cast<float>(std::default_random_engine::max())) *
                                                      (pow(2, 14))));
            pcmData[1][i] = neg * static_cast<short>((static_cast<float>(_random()) /
                                                      (static_cast<float>(std::default_random_engine::max())) *
                                                      (pow(2, 14))));

        }

        projectm_pcm_add_16bit_2ch_512(_projectMInstance, pcmData);

        std::this_thread::sleep_for(milliseconds(10));
    }
}

void FakeAudioGenerator::GenerateBeat()
{
    _stopped = false;

    // Sample rate
    static const double sampleRate = 48000.0;

    // 125 bpm bass drum
    static const milliseconds beatTimeMSec(48);
    static const std::array<int32_t, 6> frequencies = { 43, 86, 129, 175, 218, 266 };

    time_point<steady_clock> startTime;
    time_point<steady_clock> lastTickTime;

    while (!_stopped)
    {
        std::this_thread::sleep_for(milliseconds(10));

        time_point<steady_clock> currentTime;
        auto tickLength = duration_cast<microseconds>(currentTime - lastTickTime);
        uint64_t sampleCount = std::floor(sampleRate / 1000000.0  * tickLength.count());
        std::vector<float> pcmData(sampleCount);

        for (uint64_t sample = 0; sample < sampleCount; sample++)
        {

        }

        projectm_pcm_add_float_2ch_data(_projectMInstance, pcmData.data(), pcmData.size());

        lastTickTime = currentTime;
    }
}

void FakeAudioGenerator::Stop()
{
    _stopped = true;
}

} // namespace project