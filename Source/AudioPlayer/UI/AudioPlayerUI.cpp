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

    
    juce::Font f{ 25.0f,juce::Font::FontStyleFlags::bold };

    songNameLabel.setFont(f);
    songNameLabel.setText("No song loaded", juce::NotificationType::dontSendNotification);
    songNameLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(songNameLabel);


    artistNameLabel.setFont(f);
    artistNameLabel.setText("No Artist", juce::NotificationType::dontSendNotification);
    artistNameLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(artistNameLabel);
    
}

void AudioPlayerUI::paint(juce::Graphics& g)
{
    
    g.fillAll(juce::Colours::black); //background color
    g.setColour(juce::Colours::white);
    juce::Rectangle<float> discArea{ 375.0f,static_cast<float> (artistNameLabel.getBottom()) + 10.0f,200.0f,200.0f};
    g.drawEllipse(discArea, 10.0f);
}

void AudioPlayerUI::resized()
{

    auto w = 100;
    auto h = 50;
    auto pad = 10;
    auto x = 5;
    auto y = getHeight() - (h + pad);
    auto labelWidth = 500;
    auto labelHeight = 30;

    loadAudioButton.setBounds(5, y, w, h);
    playAudioButton.setBounds(loadAudioButton.getRight() + pad, y, w, h);
    stopAudioButton.setBounds(playAudioButton.getRight() + pad,y,w,h);
    gainSlider.setBounds(x, 70,50, 150);                   // slider
    songNameLabel.setBounds(x, 5, labelWidth, labelHeight);
    artistNameLabel.setBounds(x, songNameLabel.getBottom(), labelWidth, labelHeight);
}
