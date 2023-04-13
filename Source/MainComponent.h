#pragma once

#include <JuceHeader.h>
#include "MixerDeviceScanner.h"










//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    MixerDeviceScanner deviceScanner;
    juce::AudioFormatManager audioFormatManager;
    juce::TextButton loadAudioButton {"Load"};

    //UI
    juce::TextButton settingsButton{ "Settings" };
    juce::DialogWindow settingsWindow;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
