#pragma once

#include <libprojectM/projectM.h>

#include <SDL2/SDL_audio.h>

#include <array>
#include <cstdint>
#include <string>

namespace projectMAudio {

/**
 * @brief Class responsible for capturing audio data from SDL2 in the background.
 */
class SDL2Capture
{
public:
    /**
     * @brief Constructor. Creates the SDL2Capture instance.
     * @param projectMInstance The projectM instance that will receive the audio data.
     * @param audioDriverName The SDL2 audio driver to use.
     * @param audioDeviceName The SDL2 audio device to use.
     */
    explicit SDL2Capture(projectm_handle projectMInstance, std::string audioDriverName, std::string audioDeviceName);

    /**
     * @brief Destructor. Stop capturing and closes the audio device.
     */
    ~SDL2Capture();

    /**
     * @brief Opens the configured audio device for capturing.
     * @return True if the device was opened successfully and capturing can start, false if an error occurred.
     */
    bool OpenAudioDevice();

    /**
     * @brief Stops capturing and closes the audio device.
     *
     * To only stop/pause capturing, use the Stop() method.
     */
    void CloseAudioDevice();

    /**
     * @brief Starts or resumes audio capturing.
     * @return True if capturing has started, false if no audio device is open.
     */
    bool Start() const;

    /**
     * @brief Stop or pauses audio capturing, but keeps the audio device open.
     */
    void Stop() const;

    /**
     * @brief Returns the SDL audio driver name used to create this instance.
     * @return The SDL audio driver name used to create this instance.
     */
    std::string AudioDriverName() const;

    /**
     * @brief Returns the SDL audio device name used to create this instance.
     * @return The SDL audio device name used to create this instance.
     */
    std::string AudioDeviceName() const;

    /**
     * @brief Returns whether the current audio device has been opened.
     *
     * This only checks if the device is open, not if it is currently capturing data.
     * Use IsCapturing() to query this.
     *
     * @return True if the SDL audio device is currently open, false if not.
     */
    bool IsOpen() const;

protected:
    /**
     * @brief Callback method used by SDL2 to send incoming audio data.
     * @param userData A pointer to an SDL2Capture instance.
     * @param stream Audio data as a simple byte stream.
     * @param len The number of bytes in the audio data stream.
     */
    static void AudioDataCallback(void* userData, uint8_t* stream, int len);

    /**
     * @brief Member method to process the audio data received from SDL2.
     * @param stream Audio data as a simple byte stream.
     * @param len The number of bytes in the audio data stream.
     */
    void AudioDataCallback(uint8_t* stream, int len) const;

    projectm_handle _projectMInstance; //!< The projectM instance that will receive the audio data.
    std::string _audioDriverName; //!<  The SDL2 audio driver to use.
    std::string _audioDeviceName; //!< The SDL2 audio device to use.

    SDL_AudioDeviceID _audioDeviceID{ 0 }; //!< SDL ID of the opened audio device.
    SDL_AudioSpec _audioDeviceSpec{ 0 }; //!< The SDL audio device spec structure for the opened audio device.
};

} // namespace projectMAudio

