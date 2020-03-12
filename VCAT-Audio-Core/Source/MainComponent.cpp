/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "VCAT-OSC-Core.h"

//==============================================================================
MainComponent::MainComponent()
{
    m_logger.setText("Received OSC Messages will appear here");
    m_logger.setMultiLine(true);
    m_logger.setReadOnly(true);
    
    addAndMakeVisible(m_logger);
    
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    
    
    
    VCAT::OSCNodePtr setupNode  = std::make_shared<VCAT::OSCNode>("/setup",[](const OSCMessage& msg ){
            
        DBG("Setup Received");
        
        
        bool valid = false;
        String error="NOTKNOWN";
        
        
        
        String ip = VCAT::obtainString(msg, 0);
        int port = VCAT::obtainInt(msg, 1);
        
        //maybe show something on screen with warning...
        VCAT::OSCCore::getInstance()->setupSender(ip, port);
        
        valid = VCAT::OSCCore::getInstance()->setup();
    
        VCAT::OSCCore::getInstance()->finished("/setup",valid ,error);
        
        
        
    });
        
    
    
    VCAT::OSCCore::getInstance()->registerNode(setupNode);
    
    
    
    VCAT::OSCCore::getInstance()->setLogCallback([this](const OSCMessage& msg){
        logOSCMessage(msg);
    });
    
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    
    VCAT::OSCCore::deleteInstance();
    
}



void MainComponent::logLine(String msg){
    MessageManagerLock lock();
    String text = m_logger.getTextValue().toString();
    text +=  String("\n") + msg;
    m_logger.setText(text);
    m_logger.setScrollToShowCursor(true);
    m_logger.setCaretVisible(true);
    
    m_logger.setCaretPosition(m_logger.getText().length() - 1);
    
}
void MainComponent::logOSCMessage(const OSCMessage& msg){
    
    logLine( VCAT::obtainMessageAsString(msg)  );
    
    
}










//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    auto size = getLocalBounds();
    
    m_logger.setBounds(size.removeFromBottom(size.getHeight()*0.5).reduced(5));
    
    
}
