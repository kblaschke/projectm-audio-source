#include "WASAPIBackend.h"

namespace projectMAudio {

WASAPIBackend::WASAPIBackend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

Device::List WASAPIBackend::AvailableAudioDevices()
{
    return projectMAudio::Device::List();
}

} // namespace projectMAudio
