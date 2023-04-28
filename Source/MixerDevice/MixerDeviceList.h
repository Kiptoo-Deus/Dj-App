/*
  ==============================================================================

    MixerDeviceList.h
    Created: 6 Apr 2023 1:50:44pm
    Author:  JOEL

  ==============================================================================
*/

#pragma once

#include "MixerDevice.h"


/* Holds our list of mixers */
struct MixerDeviceList
{
    MixerDeviceList()
    {
        deviceSetups.push_back(pioneerDJMS9);
    }

    std::vector<MixerDevice> deviceSetups;
    MixerDevice pioneerDJMS9{ "DJM-S9", "Pioneer DJ DJM-S9", 48000.0, 64, 7, 31, 4, 8 };
};
