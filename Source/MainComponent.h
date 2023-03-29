#pragma once

#include <JuceHeader.h>



class DeviceScanner : public juce::ChangeListener {



public:

    DeviceScanner(juce::AudioDeviceManager& m):deviceManager(m){}

    void changeListenerCallback(juce::ChangeBroadcaster* source) override
    {

        const auto& deviceTypes = deviceManager.getAvailableDeviceTypes();
        for (auto& type : deviceTypes)
        {
            type->scanForDevices();
            for (const auto& deviceName : type->getDeviceNames())
            {
                if (deviceName == mixer)
                {
                    std::cout << "Success" << std::endl;
                    
                    juce::AudioDeviceManager::AudioDeviceSetup newDeviceSettings;
                    
                    juce::BigInteger inputChannels;
                    juce::BigInteger outputChannels;

                    inputChannels.setRange(0, 4, true);
                    outputChannels.setRange(0, 8, true);


                    newDeviceSettings.inputDeviceName = mixer;
                    newDeviceSettings.outputDeviceName = mixer;
                    newDeviceSettings.sampleRate = 48000.0;
                    newDeviceSettings.bufferSize = 64;
                    newDeviceSettings.inputChannels = inputChannels;
                    newDeviceSettings.outputChannels = outputChannels;

                    deviceManager.initialise(4, 8, nullptr, true);
                    deviceManager.setAudioDeviceSetup(newDeviceSettings, true);
                    

                }
        }
            
          }

    }
private:
    juce::String mixer{ "DJM-S9" };
    juce::AudioDeviceManager& deviceManager;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    bool isConnectedDeviceOnList();
    DeviceScanner deviceScanner;

    //UI
    juce::AudioDeviceSelectorComponent audiodeviceSelector;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
