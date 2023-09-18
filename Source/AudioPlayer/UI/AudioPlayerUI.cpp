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
        audioPlayerData.setPlayState (AudioPlayerState::Playing) ;
    };

    stopAudioButton.onClick = [&]()
    {
        audioPlayerData.setPlayState ( AudioPlayerState::Stopped) ;
    };

    gainSlider.setRange(-60.0, 0.0f,0.01);
    gainSlider.setValue(0.0f);

    gainSlider.onValueChange = [&]()
    {   
        auto gainValue = juce::Decibels::decibelsToGain(gainSlider.getValue());
        audioPlayerData.setDecibelValue(gainSlider.getValue());
    };

    addAndMakeVisible(gainSlider);

    
    juce::Font f{ 25.0f,juce::Font::FontStyleFlags::plain };

    trackNameLabel.setFont(f);
    trackNameLabel.setText("No song loaded", juce::NotificationType::dontSendNotification);
    trackNameLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(trackNameLabel);


    artistNameLabel.setFont(f);
    artistNameLabel.setText("No Artist", juce::NotificationType::dontSendNotification);
    artistNameLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(artistNameLabel);

    trackLengthLabel.setFont(juce::Font(24.0,juce::Font::FontStyleFlags::plain));
    trackLengthLabel.setText("00:00.0", juce::NotificationType::dontSendNotification);
    //songLengthLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::white);
    addAndMakeVisible(trackLengthLabel);
    
}

void AudioPlayerUI::paint(juce::Graphics& g)
{
    
    g.fillAll(juce::Colours::black); //background color
    g.setColour(juce::Colours::white);
    juce::Rectangle<float> discArea{ 375.0f,static_cast<float> (artistNameLabel.getBottom()) + 25.0f,180.0f,180.0f};
    auto discCenter = discArea.getCentre();
    auto diameter{ 20 };
    auto radius{diameter /2 };

    g.drawEllipse(discArea, 10.0f);
    g.fillEllipse(discCenter.getX() - radius, discCenter.getY() - radius, diameter, diameter);
    g.drawLine(float(discCenter.getX()), float (discCenter.getY()), discArea.getX() + (discArea.getWidth()/2.0f), discArea.getY(), 10.0f);//draws the line in the circle
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
    trackNameLabel.setBounds(x, 5, labelWidth, labelHeight);
    artistNameLabel.setBounds(x, trackNameLabel.getBottom(), labelWidth, labelHeight);
    trackLengthLabel.setBounds(275,artistNameLabel.getBottom() + 30, labelWidth/4, labelHeight);
}

void AudioPlayerUI::changeListenerCallback (juce:: ChangeBroadcaster* source)
{
    trackNameLabel.setText( audioPlayerData.getTrackName(), juce::dontSendNotification);
}