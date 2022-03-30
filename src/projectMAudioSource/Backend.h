#pragma once

#include "projectMAudioSource/Device.h"

#include <libprojectM/projectM.h>

#include <memory>
#include <string>
#include <vector>

class projectM;

namespace projectMAudio {

/**
 * @brief Audio backend interface class
 *
 * All audio backends derive from this class.
 *
 * Each backend will internally capture audio samples from the given device and add it to the PCM data buffer
 * of the projectM instance the backend was initialized with.
 *
 * Audio capturing is always done in a background thread,
 *
 */
class Backend
{
public:

    using List = std::vector<std::string>;
    using Ptr = std::unique_ptr<Backend>;

    /**
     * @brief Default constructor. Initializes the backend.
     * @param projectMInstance Instance of the projectM that will receive the audio data.
     */
    Backend(projectm_handle projectMInstance);

    /**
     * @brief Destructor. Frees any allocated backend resources.
     */
    virtual ~Backend() = default;

    /**
     * @brief Returns a list of available audio backends.
     *
     * This list includes all available backends, no matter whether they actually provide a
     * usable audio device or not. The frontend application needs to probe backends in order
     * to select one that has working audio devices.
     *
     * @param includeFakeBackend Set to true to include the "Fake" backend.
     * @return A list of audio backends compiled into the library.
     */
    static List Enumerate(bool includeFakeBackend = false);

    /**
     * @brief Factory method to create a new backend instance using its name.
     * @param backendName The name of the backend as returned by Enumerate().
     * @param projectMInstance Instance of the projectM that will receive the audio data.
     * @return A pointer to the backend instance if successful, nullptr otherwise.
     */
    static Ptr Create(const std::string& backendName, projectm_handle projectMInstance);

    /**
     * @brief The name of the backend instance.
     * @return The name of the current backend instance.
     */
    virtual std::string Name() const = 0;

    /**
     * @brief Enumerates available audio devices.
     * @return A list of AudioDevice instances representing available audio source devices.
     */
    virtual Device::List AvailableAudioDevices() = 0;

    /**
     * @brief Starts capturing audio from the given device.
     * @param captureDevice The audio capture device to retrieve audio data from. Obtained via the AvailableAudioDevices() function.
     * @return True if capturing has started, false if there was an issue.
     */
    virtual bool StartCapture(Device::Ptr captureDevice) = 0;

    /**
     * @brief Stops any active audio capturing.
     *
     * Has no effect if no capturing is currently active.
     */
    virtual void StopCapture() = 0;

protected:

    projectm_handle _projectMInstance; //!< Instance of the projectM that will receive the audio data.

};

} // namespace projectMAudio
