#pragma once

#include <JuceHeader.h>
#include "MixerDevice/MixerDeviceScanner.h"//DATA
#include "AudioPlayer/Data/AudioPlayerData.h"
#include "AudioPlayer/UI/AudioPlayerUI.h"//UI


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
   MixerDeviceScanner deviceScanner;//scans our list for usb devices connected
    
    //UI
    juce::TextButton settingsButton{ "Settings" };
    juce::DialogWindow settingsWindow;
    
    //Player UI is controlling Data
    AudioPlayerData audioPlayerData1;
    AudioPlayerUI audioPlayerUI1;
    
    bool fileIsLoaded{ false }; 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
