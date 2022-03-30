#include "SDL2Backend.h"

#include "SDL2AudioDevice.h"

#include <SDL2/SDL_audio.h>

namespace projectMAudio {

SDL2Backend::SDL2Backend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}


Device::List SDL2Backend::AvailableAudioDevices()
{
    Device::List audioDevices;
    SDL_AudioSpec desiredAudioSpec{
        .freq = 44100,
        .format = AUDIO_F32,
        .channels = 1,
        .samples = static_cast<uint16_t>(projectm_pcm_get_max_samples()),
        .callback = nullptr,
        .userdata = nullptr
    };

    // Iterate through available drivers, in SDL "best" order.
    int audioDriverCount = SDL_GetNumAudioDrivers();
    for (int driverIndex = 0; driverIndex < audioDriverCount; ++driverIndex)
    {
        std::string audioDriverName(SDL_GetAudioDriver(driverIndex));

        if (SDL_AudioInit(audioDriverName.c_str()) != 0)
        {
            continue;
        }

        int audioDeviceCount = SDL_GetNumAudioDevices(true);
        for (int deviceIndex = 0; deviceIndex < audioDeviceCount; ++deviceIndex)
        {
            std::string audioDeviceName(SDL_GetAudioDeviceName(deviceIndex, true));

            SDL_AudioSpec supportedSpec;
            auto audioDeviceId = SDL_OpenAudioDevice(audioDeviceName.c_str(), true, &desiredAudioSpec,
                                                     &supportedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);

            if (audioDeviceId > 1)
            {
                SDL_CloseAudioDevice(audioDeviceId);

                audioDevices.push_back(
                    std::make_shared<SDL2AudioDevice>(*this, supportedSpec, audioDriverName, audioDeviceName));
            }
        }

        SDL_AudioQuit();
    }

    return audioDevices;
}

std::string SDL2Backend::Name() const
{
    return "SDL2";
}

bool SDL2Backend::StartCapture(Device::Ptr captureDevice)
{
    if (!captureDevice->BelongsToBackend(*this))
    {
        return false;
    }

    auto audioDevice = std::dynamic_pointer_cast<SDL2AudioDevice>(captureDevice);
    if (!audioDevice)
    {
        return false;
    }

    if (_capture
        && _capture->AudioDriverName() == audioDevice->AudioDriverName()
        && _capture->AudioDeviceName() == audioDevice->AudioDeviceName()
        && _capture->IsOpen())
    {
        // Just resume capturing on already open device.
        _capture->Start();
        return true;
    }

    _capture = std::make_unique<SDL2Capture>(_projectMInstance, audioDevice->AudioDriverName(),
                                             audioDevice->AudioDeviceName());

    if (_capture->OpenAudioDevice() && _capture->Start())
    {
        return true;
    }

    _capture.reset();
    return false;
}

void SDL2Backend::StopCapture()
{
    if (_capture)
    {
        _capture->Stop();
    }
}

} // namespace projectM
