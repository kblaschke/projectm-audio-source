#include "FakeCaptureThread.h"

#include <libprojectM/projectM.h>

#include <thread>

namespace projectMAudio {

FakeCaptureThread::FakeCaptureThread(projectm_handle projectMInstance)
    : _projectMInstance(projectMInstance)
{
}

void FakeCaptureThread::GenerateFakeAudio()
{
    int i;
    short pcm_data[2][512];

    _stopped = false;

    while (!_stopped)
    {
        for (i = 0; i < 512; i++)
        {
            short neg = i % 2 == 0 ? 1 : -1;

            pcm_data[0][i] = neg * static_cast<short>((static_cast<float>(_random()) /
                                                       (static_cast<float>(std::default_random_engine::max())) *
                                                       (pow(2, 14))));
            pcm_data[1][i] = neg * static_cast<short>((static_cast<float>(_random()) /
                                                       (static_cast<float>(std::default_random_engine::max())) *
                                                       (pow(2, 14))));

        }

        projectm_pcm_add_16bit_2ch_512(_projectMInstance, pcm_data);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void FakeCaptureThread::Stop()
{
    _stopped = true;
}

} // namespace project