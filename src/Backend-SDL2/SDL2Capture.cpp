#include "SDL2Capture.h"

#include <libprojectM/projectM.h>

namespace projectMAudio {

SDL2Capture::SDL2Capture(projectm_handle projectMInstance, std::string audioDriverName, std::string audioDeviceName)
    : _projectMInstance(projectMInstance)
    , _audioDriverName(std::move(audioDriverName))
    , _audioDeviceName(std::move(audioDeviceName))
{
}

SDL2Capture::~SDL2Capture()
{
    CloseAudioDevice();
}

bool SDL2Capture::OpenAudioDevice()
{
    SDL_AudioSpec desiredAudioSpec{
        .freq = 48000,
        .format = AUDIO_F32,
        .channels = 2,
        .samples = static_cast<uint16_t>(projectm_pcm_get_max_samples()),
        .callback = &SDL2Capture::AudioDataCallback,
        .userdata = this
    };

    if (SDL_AudioInit(_audioDriverName.c_str()) != 0)
    {
        return false;
    }

    _audioDeviceID = SDL_OpenAudioDevice(_audioDeviceName.c_str(), true, &desiredAudioSpec,
                                         &_audioDeviceSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (_audioDeviceID < 2)
    {
        return false;
    }

    return true;
}

void SDL2Capture::CloseAudioDevice()
{
    if (_audioDeviceID > 0)
    {
        Stop();

        SDL_CloseAudioDevice(_audioDeviceID);
        SDL_AudioQuit();
        _audioDeviceID = 0;
    }
}

bool SDL2Capture::Start() const
{
    if (_audioDeviceID < 2)
    {
        return false;
    }

    SDL_PauseAudioDevice(_audioDeviceID, false);

    return true;
}

void SDL2Capture::Stop() const
{
    if (_audioDeviceID >= 2)
    {
        SDL_PauseAudioDevice(_audioDeviceID, true);
    }
}

void SDL2Capture::AudioDataCallback(void* userData, uint8_t* stream, int len)
{
    auto instance = static_cast<SDL2Capture*>(userData);
    instance->AudioDataCallback(stream, len);
}

void SDL2Capture::AudioDataCallback(uint8_t* stream, int len) const
{
    if (_audioDeviceSpec.channels > 2)
    {
        return;
    }

    switch (_audioDeviceSpec.format)
    {
        case AUDIO_F32:
            if (_audioDeviceSpec.channels == 1)
            {
                projectm_pcm_add_float_1ch_data(_projectMInstance, reinterpret_cast<float*>(stream),
                                                len / sizeof(float));
            }
            else if (_audioDeviceSpec.channels == 2)
            {
                projectm_pcm_add_float_2ch_data(_projectMInstance, reinterpret_cast<float*>(stream),
                                                len / sizeof(float));
            }
            break;

        case AUDIO_S16:
            projectm_pcm_add_16bit_2ch_data(_projectMInstance, reinterpret_cast<short*>(stream),
                                            len / sizeof(short) / _audioDeviceSpec.channels);
            break;

        case AUDIO_U8:
        {
            // No pointer-accepting function available for 8-bit samples, so need to copy them into an array.
            int blockSize = 512 * _audioDeviceSpec.channels;

            for (int block = 0; block < len / blockSize; block++)
            {
                unsigned char pcmData[2][512];
                for (int sample = 0; sample < 512; sample++)
                {
                    if (_audioDeviceSpec.channels == 1)
                    {
                        pcmData[0][sample] = pcmData[1][sample] = stream[block * 512 + sample];
                    }
                    else
                    {
                        pcmData[0][sample] = stream[block * 1024 + sample * 2];
                        pcmData[1][sample] = stream[block * 1024 + sample * 2 + 1];
                    }

                    projectm_pcm_add_8bit_2ch_512(_projectMInstance, pcmData);
                }
            }
        }
            break;

        default:
            // No output currently for unsupported formats.
            // ToDo: Convert any other format to a supported format (e.g. AUDIO_S16) with SDL_AudioStream
            return;
    }

}

std::string SDL2Capture::AudioDriverName() const
{
    return _audioDriverName;
}

std::string SDL2Capture::AudioDeviceName() const
{
    return _audioDeviceName;
}

bool SDL2Capture::IsOpen() const
{
    return _audioDeviceID > 1;
}

} // namespace projectMAudio

