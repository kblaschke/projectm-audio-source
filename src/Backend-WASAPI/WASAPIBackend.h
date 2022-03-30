#pragma once

#include "projectMAudioSource/Backend.h"

namespace projectMAudio {

class WASAPIBackend : public Backend
{
public:
    explicit WASAPIBackend(projectm_handle projectMInstance);

    Device::List AvailableAudioDevices() override;
};

} // namespace projectMAudio
