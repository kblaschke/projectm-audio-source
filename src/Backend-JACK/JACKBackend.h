#pragma once

#include "projectMAudioSource/Backend.h"

namespace projectMAudio {

class JACKBackend : public Backend
{
public:
    explicit JACKBackend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;
};

} // namespace projectMAudio
