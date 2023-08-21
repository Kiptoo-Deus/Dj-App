/*
  ==============================================================================

    AudioPlayerUI.h
    Created: 26 Apr 2023 10:38:20am
    Author:  JOEL

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"../Data/AudioPlayerData.h"
#include "../../State/AudioPlayerState.h"

//==============================================================================
/*
*/
class AudioPlayerUI  : public juce::Component
{
public:
    AudioPlayerUI(AudioPlayerData& p);
    /*~AudioPlayerUI() override;*///<<<<<Line to note incase UI breaks

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AudioPlayerData& audioPlayerData;
    juce::TextButton loadAudioButton{ "Load" };
    juce::TextButton playAudioButton{ "Play" };
    juce::TextButton stopAudioButton{ "Stop" };

    juce::Slider gainSlider{ juce::Slider::SliderStyle::LinearVertical, juce::Slider::TextBoxBelow };
    juce::Label songNameLabel{ "Song Name" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerUI)
};

