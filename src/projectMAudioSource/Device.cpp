#include "projectMAudioSource/Device.h"

#include <utility>

namespace projectMAudio {

Device::Device(std::string name, const Backend& backend)
    : _name(std::move(name))
    , _backend(backend)
{
}

std::string Device::Name() const
{
    return _name;
}

bool Device::BelongsToBackend(const Backend& backend) const
{
    return &_backend == &backend;
}

uint32_t Device::SupportedSampleFrequency() const
{
    return _sampleFrequency;
}

Device::SampleFormat Device::SupportedSampleFormat() const
{
    return _sampleFormat;
}

uint8_t Device::SupportedChannels() const
{
    return _channels;
}

} // namespace projectMAudio
