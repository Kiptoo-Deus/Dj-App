/*
  ==============================================================================

    AudioPlayerData.cpp
    Created: 26 Apr 2023 10:35:49am
    Author:  JOEL

  ==============================================================================
*/
#include "AudioPlayerData.h"
#include <JuceHeader.h>
#include "../../State/AudioPlayerState.h"


AudioPlayerData::AudioPlayerData()
{
    audioFormatManager.registerBasicFormats();
}
bool AudioPlayerData::loadFile()
{
    DBG("Load button clicked");

    juce::FileChooser myChooser(juce::FileChooser("Please select the track you want to play...",
                                                  juce::File::getSpecialLocation (juce::File::userMusicDirectory),
                                                  "*.wav; *.mp3"));
 

    if (myChooser.browseForFileToOpen())
    {
        juce::File musicFile (myChooser.getResult());

        auto* r = audioFormatManager.createReaderFor(musicFile);
        std::unique_ptr<juce::AudioFormatReader>reader(r);
        jassert(reader != nullptr);
        auto numSamples = static_cast<int>(reader->lengthInSamples);

        audiosourceBuffer.setSize(reader->numChannels, numSamples);
        jassert(numSamples > 0 && reader->numChannels > 0);

        //file loaded succesfully?
        reader->read(&audiosourceBuffer, 0, numSamples, 0, true, true);
        return true;
    }
    
    return false;
}
void AudioPlayerData::prepareToPlay(int numChannels,int samplesPerBlock, double sampleRate)
{
    playerBuffer.setSize(numChannels, samplesPerBlock);
}

void AudioPlayerData::processAudio(const juce::AudioSourceChannelInfo& bufferToFill)
{
        auto* buffer = bufferToFill.buffer;

        

        playerBuffer.clear();

        // you haven't called prepare toplay
        jassert(playerBuffer.getNumSamples() > 0 && playerBuffer.getNumChannels() == buffer->getNumChannels());
        jassert(playerBuffer.getNumChannels() == buffer->getNumChannels());
    
    for (int ch = 0; ch < buffer->getNumChannels(); ch++)
    {
        playerBuffer.copyFrom(ch, 0, audiosourceBuffer, ch, readPosition, playerBuffer.getNumSamples());
        playerBuffer.applyGain(ch, 0, playerBuffer.getNumSamples(), rawGain);

        //Addsamples to main Buffer
        buffer->addFrom(ch, 0, playerBuffer, ch, 0, buffer->getNumSamples());
    }
    readPosition += buffer->getNumSamples();

}

   void AudioPlayerData::setDecibelValue(float value)
{
   
     rawGain = juce::Decibels::decibelsToGain(value);
  
}
