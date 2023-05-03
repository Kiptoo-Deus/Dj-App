/*
  ==============================================================================

    AudioPlayerData.cpp
    Created: 26 Apr 2023 10:35:49am
    Author:  JOEL

  ==============================================================================
*/
#include "AudioPlayerData.h"


AudioPlayerData::AudioPlayerData()
{
    audioFormatManager.registerBasicFormats();
}
bool AudioPlayerData::loadFile()
{
    DBG("Load button clicked");

    juce::File musicFile{ "C:\\lifted.mp3" };
    jassert(musicFile.exists());

    auto* r = audioFormatManager.createReaderFor(juce::File("C:\\lifted.mp3"));
    std::unique_ptr<juce::AudioFormatReader>reader(r);
    jassert(reader != nullptr);
    auto numSamples = static_cast<int>(reader->lengthInSamples);

    audioSourceBuffer.setSize(reader->numChannels, numSamples);
    jassert(numSamples > 0 && reader->numChannels > 0);

    //file loaded succesufully?
    reader->read(&audioSourceBuffer, 0, numSamples, 0, true, true);
    return true;

}
//bool AudioPlayerData::loadFile()
//{
//    DBG("Load button clicked");
//
//    juce::File musicFile{ "C:\\lifted.mp3" };
//    jassert(musicFile.exists());
//
//    
//
//    auto* reader = audioFormatManager.createReaderFor(musicFile);      <<<<--------code responsible for Jassert error 
//    if (reader == nullptr) {
//        jassertfalse;
//        return false;
//    }
//   
//    
//    auto numSamples = static_cast<int>(reader->lengthInSamples);
//
//    audioSourceBuffer.setSize(reader->numChannels, numSamples);
//    jassert(numSamples > 0 && reader->numChannels > 0);
//
//    reader->read(&audioSourceBuffer, 0, numSamples, 0, true, true);
//    return true;
//}


void AudioPlayerData::processAudio(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* buffer = bufferToFill.buffer;

    //copy buffer size number of samples ofaudio source buffer to main buffer
    jassert(buffer->getNumChannels() == audioSourceBuffer.getNumChannels());
    for (int ch = 0; ch < buffer->getNumChannels(); ch++)
    {
        buffer->copyFrom(ch, 0, audioSourceBuffer, ch, readPosition, buffer->getNumSamples());
    }
    readPosition += buffer->getNumSamples();

}

    
void AudioPlayerData::setDecibelValue(float value)
{
    auto numSample = audioSourceBuffer.getNumSamples();  
    auto rawGain = juce::Decibels::decibelsToGain(value);

   /* std::cout << rawGain << std::endl;*/
    for (int ch = 0; ch < audioSourceBuffer.getNumChannels(); ch++)
        {
            audioSourceBuffer.applyGain(ch, 0, numSample, rawGain);//modified this line
        };
}