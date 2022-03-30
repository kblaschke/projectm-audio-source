#pragma once

#include <memory>
#include <string>
#include <vector>

namespace projectMAudio {

class Backend;

/**
 * @brief Represents an audio input device of the currently selected source.
 *
 * Each backend can create a subclass of this to store additional data, e.g. backend-specific IDs,
 * to map the public device name to the internal API and set more device information.
 *
 */
class Device
{
public:
    using Ptr = std::shared_ptr<Device>; //!< A pointer to a Device instance.
    using List = std::vector<Device::Ptr>; //!< A list of audio capture devices.

    /**
     * @brief Denotes the (best) sample format supported by this device.
     */
    enum class SampleFormat
    {
        Unknown, //!< Either non-determinable by the driver or not directly supported by projectM
        Float32, //!< 32-bit floating point samples
        Int16, //!< 16-bit signed integer samples
        UInt8 //!< 8-bit unsigned integer samples
    };

    /**
     * @brief Constructor. Creates a audio device.
     * @param name The display name of the audio capture device.
     * @param backend The backend that created this device instance.
     */
    explicit Device(std::string name, const Backend& backend);

    /**
     * @brief The display name of the audio capture device.
     *
     * This is the device name an application can show to the user in a selection dialog.
     *
     * @return The display name of the audio capture device.
     */
    virtual std::string Name() const;

    /**
     * @brief Checks if the device belongs to the given audio backend.
     *
     * Used by backends to check if a provided audio device originated from it.
     *
     * @param backend The backend to check against this instance.
     * @return True if the backend is the same that created this instance, false otherwise.
     */
    bool BelongsToBackend(const Backend& backend) const;

    /**
     * @brief The number of samples per second this device supports.
     *
     * The sample frequency is generally a value of 11025, 22050, 44100 or 48000.
     *
     * @return The number of samples per second this device supports or 0 if unknown.
     */
    uint32_t SupportedSampleFrequency() const;

    /**
     * @brief The best waveform sample format the device supports.
     * @return A value from the SampleFormat enum, can be SupportedSampleFormat::Unknown if it cannot be determined
     *         by the driver.
     */
    SampleFormat SupportedSampleFormat() const;

    /**
     * @brief The number of channels this device supports.
     *
     * In almost all cases, this will be 1 (mono) or 2 (stereo).
     *
     * @return The number of channels this device supports, or 0 if unknown.
     */
    uint8_t SupportedChannels() const;

protected:
    std::string _name; //!< The display name of the audio capture device.
    uint32_t _sampleFrequency{ 0 }; //!< The number of samples per second, e.g. 44100.
    SampleFormat _sampleFormat{ SampleFormat::Unknown }; //!< The best sample format suported by this device.
    uint8_t _channels{ 0 }; //!< The number of channels supported by this device.

private:
    const Backend& _backend; //!< A reference to the audio backend that has created this device instance.

};

} // namespace projectMAudio
