#include "projectMAudioSource/Device.h"

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

} // namespace projectMAudio
