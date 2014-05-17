/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
RemoteGoatVstAudioProcessor::RemoteGoatVstAudioProcessor()
{
}

RemoteGoatVstAudioProcessor::~RemoteGoatVstAudioProcessor()
{
}

//==============================================================================
const String RemoteGoatVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int RemoteGoatVstAudioProcessor::getNumParameters()
{
    return 0;
}

float RemoteGoatVstAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void RemoteGoatVstAudioProcessor::setParameter (int index, float newValue)
{
}

const String RemoteGoatVstAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String RemoteGoatVstAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String RemoteGoatVstAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String RemoteGoatVstAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool RemoteGoatVstAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool RemoteGoatVstAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool RemoteGoatVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RemoteGoatVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RemoteGoatVstAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double RemoteGoatVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RemoteGoatVstAudioProcessor::getNumPrograms()
{
    return 0;
}

int RemoteGoatVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RemoteGoatVstAudioProcessor::setCurrentProgram (int index)
{
}

const String RemoteGoatVstAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void RemoteGoatVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RemoteGoatVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void RemoteGoatVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void RemoteGoatVstAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool RemoteGoatVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RemoteGoatVstAudioProcessor::createEditor()
{
    return new RemoteGoatVstAudioProcessorEditor (this);
}

//==============================================================================
void RemoteGoatVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RemoteGoatVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RemoteGoatVstAudioProcessor();
}