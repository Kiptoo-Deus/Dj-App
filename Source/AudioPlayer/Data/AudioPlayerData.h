/*
  ==============================================================================

    AudioPlayerData.h
    Created: 26 Apr 2023 10:35:49am
    Author:  JOEL

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../State/AudioPlayerState.h"

class AudioPlayerData
{
public:
    AudioPlayerData();
    bool loadFile();
    void processAudio(const juce::AudioSourceChannelInfo& bufferToFill);
    void setDecibelValue(float value);
    AudioPlayerState getPlayState() const { return playState; }

    void setPlaySate(AudioPlayerState newState) { playState = newState; }
private:
  
private:
    juce::AudioFormatManager audioFormatManager;
    juce::AudioBuffer<float>audioSourceBuffer;
    int readPosition{ 0 }; 
    bool fileIsLoaded{ false };
    AudioPlayerState playState{ AudioPlayerState::Stopped };
  
};


