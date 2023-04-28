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
//bool AudioPlayerData::loadFile()
//{
//    DBG("Load button clicked");
//
//    juce::File musicFile{ "C:\\lifted.mp3" };
//    jassert(musicFile.exists());
//
//    auto* r = audioFormatManager.createReaderFor(juce::File("C:\\lifted.mp3"));
//    std::unique_ptr<juce::AudioFormatReader>reader(r);
//    jassert(reader != nullptr);
//    auto numSamples = static_cast<int>(reader->lengthInSamples);
//
//    audioSourceBuffer.setSize(reader->numChannels, numSamples);
//    jassert(numSamples > 0 && reader->numChannels > 0);
//
//    //file loaded succesufully?
//   return reader->read(&audioSourceBuffer, 0, numSamples, 0, true, true);
//
//}
bool AudioPlayerData::loadFile()
{
    DBG("Load button clicked");

    juce::File musicFile{ "C:\\lifted.mp3" };
    jassert(musicFile.exists());

    auto* reader = audioFormatManager.createReaderFor(musicFile);
    if (reader == nullptr) {
        return false;
    }

    auto numSamples = static_cast<int>(reader->lengthInSamples);

    audioSourceBuffer.setSize(reader->numChannels, numSamples);
    jassert(numSamples > 0 && reader->numChannels > 0);

    reader->read(&audioSourceBuffer, 0, numSamples, 0, true, true);
    return true;
}


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

    
void AudioPlayerData::setGain(float newGain)
{
    auto numSample = audioSourceBuffer.getNumSamples();
    for (int ch = 0; ch < audioSourceBuffer.getNumChannels(); ch++)
        {
            audioSourceBuffer.applyGain(ch, 0, numSample, newGain);//modified this line
        };
}