#pragma once

#include <memory>
#include <string>
#include <vector>

namespace projectMAudio {

class Backend;

/*!
 * \brief Represents an audio input device of the currently selected source.
 *
 * Each backend can create a subclass of this to store additional data, e.g. backend-specific IDs,
 * to map the public device name to the internal API.
 */
class Device
{
public:
    using Ptr = std::shared_ptr<Device>; //!< A pointer to a Device isntance.
    using List = std::vector<Device::Ptr>; //!< A list of audio capture devices.

    /**
     * @brief Constructor. Creates a audio device.
     * @param name The display name of the audio capture device.
     * @param backend The backend isntance that created this instance.
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

protected:
    std::string _name; //!< The display name of the audio capture device.

private:
    const Backend& _backend; //!< A reference to the audio backend that has created this device instance.

};

} // namespace projectMAudio
