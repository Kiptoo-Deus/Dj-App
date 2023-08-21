#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
    deviceScanner (deviceManager), settingsWindow ("Settings", juce::Colours::black, true),
    audioPlayerUI1(audioPlayerData1)
{
  
    setSize (1200, 1100);

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
    addAndMakeVisible(audioPlayerUI1);
    fileIsLoaded = audioPlayerData1.loadFile();
}

MainComponent::~MainComponent()
{
    deviceManager.removeAllChangeListeners();
    
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
   // auto outputChannels = deviceManager.getAudioDeviceSetup().outputChannels;
    //let's assume this is a stereo setup for each track
    audioPlayerData1.prepareToPlay(2,samplesPerBlockExpected,sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
   
    bufferToFill.clearActiveBufferRegion();
    if(fileIsLoaded && audioPlayerData1.getPlayState() == AudioPlayerState::Playing)
    audioPlayerData1.processAudio(bufferToFill);
}


void MainComponent::releaseResources()
{
   
}


void MainComponent::paint(juce::Graphics& g)
{

    g.fillAll(juce::Colours::darkgrey);

}

void MainComponent::resized() 
{

      auto pad = 10;
 
     settingsButton.setBounds(10, 10, 100, 50);
     audioPlayerUI1.setBounds(10, settingsButton.getBottom() + pad, 600,300);
}



