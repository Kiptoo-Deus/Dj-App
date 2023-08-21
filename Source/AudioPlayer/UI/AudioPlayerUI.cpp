/*
  ==============================================================================

    AudioPlayerUI.cpp
    Created: 26 Apr 2023 10:38:20am
    Author:  JOEL

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioPlayerUI.h"
#include "../../State/AudioPlayerState.h"

//==============================================================================
AudioPlayerUI::AudioPlayerUI(AudioPlayerData& p): audioPlayerData(p)
{
    loadAudioButton.setButtonText("Load");
    playAudioButton.setButtonText("Play");
    stopAudioButton.setButtonText("Stop");
    addAndMakeVisible(loadAudioButton);
    addAndMakeVisible(playAudioButton);
    addAndMakeVisible(stopAudioButton);

    loadAudioButton.onClick = [&]()
    {
        audioPlayerData.loadFile();
    };

    playAudioButton.onClick = [&]()
    {
        audioPlayerData.setPlaySate (AudioPlayerState::Playing) ;
    };

    stopAudioButton.onClick = [&]()
    {
        audioPlayerData.setPlaySate ( AudioPlayerState::Stopped) ;
    };

    gainSlider.setRange(-60.0, 0.0f,0.01);
    gainSlider.setValue(0.0f);

    gainSlider.onValueChange = [&]()
    {   
        auto gainValue = juce::Decibels::decibelsToGain(gainSlider.getValue());
        audioPlayerData.setDecibelValue(gainSlider.getValue());
    };

    addAndMakeVisible(gainSlider);
}

void AudioPlayerUI::paint(juce::Graphics& g)
{
    
    g.fillAll(juce::Colours::black); //background color
}

void AudioPlayerUI::resized()
{
    auto w = 100;
    auto h = 50;
    auto pad = 10;
    loadAudioButton.setBounds(5, 5, w, h);
    playAudioButton.setBounds(loadAudioButton.getRight() + pad, 5, w, h);
    stopAudioButton.setBounds(playAudioButton.getRight() + pad,5,w,h);
    gainSlider.setBounds(0, loadAudioButton.getBottom() + pad, 50, 150);                   // slider

}
