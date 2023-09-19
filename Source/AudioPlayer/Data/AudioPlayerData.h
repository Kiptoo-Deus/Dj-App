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

class AudioPlayerData: public juce::ChangeBroadcaster
{
public:
    AudioPlayerData();
    bool loadFile();
    void prepareToPlay(int numChannels, int samplesPerBlockExpected, double sampleRate);
    void processAudio(const juce::AudioSourceChannelInfo& bufferToFill);
    void setDecibelValue(float value);
    AudioPlayerState getPlayState() const { return playState; }

    void setPlayState(AudioPlayerState newState) { playState = newState; }
    juce::String getArtistName()const { return artistName; }
    juce::String getTrackName()const { return trackName; }
    juce::String getTrackLength()const { return trackLength; }


  
  
private:
    void loadMetadata(juce::AudioFormatReader& reader);
    juce::AudioFormatManager audioFormatManager;

    //Holds "entire track"
    juce::AudioBuffer<float>audiosourceBuffer;
    //Holds "mutable temp data before being passed to main buffer"
    juce::AudioBuffer<float> playerBuffer;
    int readPosition{ 0 };
    bool fileIsLoaded{ false };
    float rawGain{ 1.0f };
    AudioPlayerState playState{ AudioPlayerState::Stopped };

    juce::String artistName{ "" };
    juce::String trackName{ "" };
    juce::String trackLength{ "" };
  
};


