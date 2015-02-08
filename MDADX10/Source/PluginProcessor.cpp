#include "PluginProcessor.h"

MDADX10AudioProcessor::MDADX10AudioProcessor()
{
}

//==============================================================================
const String MDADX10AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String MDADX10AudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String MDADX10AudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool MDADX10AudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool MDADX10AudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool MDADX10AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MDADX10AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MDADX10AudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double MDADX10AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MDADX10AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MDADX10AudioProcessor::getCurrentProgram()
{
    return 0;
}

void MDADX10AudioProcessor::setCurrentProgram (int index)
{
}

const String MDADX10AudioProcessor::getProgramName (int index)
{
    return String();
}

void MDADX10AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MDADX10AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void MDADX10AudioProcessor::releaseResources()
{
}

void MDADX10AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

}

//==============================================================================
bool MDADX10AudioProcessor::hasEditor() const
{
    return false;
}

AudioProcessorEditor* MDADX10AudioProcessor::createEditor()
{
    return nullptr;
}

//==============================================================================
void MDADX10AudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void MDADX10AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MDADX10AudioProcessor();
}