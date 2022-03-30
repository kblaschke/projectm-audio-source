#include "JACKBackend.h"

namespace projectMAudio {

JACKBackend::JACKBackend(projectm_handle projectMInstance)
    : Backend(projectMInstance)
{
}

Device::List JACKBackend::AvailableAudioDevices()
{
    return projectMAudio::Device::List();
}

} // namespace projectMAudio
