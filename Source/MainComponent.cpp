#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
    deviceScanner (deviceManager), settingsWindow ("Settings", juce::Colours::black, true)
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


    audioFormatManager.registerBasicFormats();
    loadAudioButton.setButtonText("Load");
    addAndMakeVisible(loadAudioButton);
     
    loadAudioButton.onClick = [&]()
    {   
        DBG("Load button clicked");

        juce::File musicFile{"Users\JOEL\Downloads\Music\Audio Demos_5th Sweep Pad.mp3"};
        jassert(musicFile.exists());

        auto* r = audioFormatManager.createReaderFor(juce::File("Users\JOEL\Downloads\Music\Audio Demos_5th Sweep Pad.mp3"));
        auto reader = std::make_unique<juce::AudioFormatReader*>(r);
        jassert(reader != nullptr);
        
        
        //load button when clicked will locate file 
    };

    deviceManager.addChangeListener(&deviceScanner);

    settingsButton.setButtonText("Settings");
    settingsButton.setToggleable(false);

    settingsButton.onClick = [&]()
    {
        juce::DialogWindow::LaunchOptions windowOptions;
        windowOptions.dialogTitle = "Settings";
        windowOptions.useNativeTitleBar = true;
        windowOptions.content.setOwned(new juce::AudioDeviceSelectorComponent(deviceManager, 2, 8, 2, 8, true, true, false, false));
        windowOptions.content->setSize(800, 600);
        windowOptions.launchAsync();
    };

    addAndMakeVisible(settingsButton);

}

MainComponent::~MainComponent()
{
    deviceManager.removeAllChangeListeners();
    
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
    settingsButton.setBounds(10,10,200,100);
    loadAudioButton.setBounds(10,200,200,100);
}

