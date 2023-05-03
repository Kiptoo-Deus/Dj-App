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

    gainSlider.setRange(-60.0, 3.0,0.01);
    addAndMakeVisible(gainSlider);
}

void AudioPlayerUI::paint(juce::Graphics& g)
{
    

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);                            // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("AudioPlayerUI", getLocalBounds(),
        juce::Justification::centred, true);                  // draw some placeholder text
}

void AudioPlayerUI::resized()
{
    auto w = 100;
    auto h = 50;
    loadAudioButton.setBounds(10, 200, w, h);
    playAudioButton.setBounds(10, 260, w, h);
    stopAudioButton.setBounds(10, 320, w, h);
    gainSlider.setBounds(120,200,50,170);                   // slider

}
