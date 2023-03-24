#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
   audiodeviceSelector (deviceManager, 2,2,2,2,true,true,false,false)
{
  
    setSize (800, 600);

    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
       
        setAudioChannels (2, 2);
    }
    addAndMakeVisible(audiodeviceSelector);

}

MainComponent::~MainComponent()
{
    
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
   
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
   
}


void MainComponent::paint(juce::Graphics& g)
{

    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    audiodeviceSelector.setBounds(getBounds());
}
