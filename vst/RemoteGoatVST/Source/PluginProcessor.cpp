/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

class RepaintTimer : public juce::Timer
{
private:
	RemoteGoatVstAudioProcessor* processor;

public:
	RepaintTimer(RemoteGoatVstAudioProcessor* processor) : processor(processor)
	{
		this->startTimer(16);
	}

	virtual void timerCallback()
	{
		auto* ed = processor->getActiveEditor();
		if (ed != nullptr) ed->repaint();
	}
};

//==============================================================================
RemoteGoatVstAudioProcessor::RemoteGoatVstAudioProcessor()
{
	writeTrace("Goat Trace!");
	_repaintTimer = new RepaintTimer(this);
	_play = false;
}

RemoteGoatVstAudioProcessor::~RemoteGoatVstAudioProcessor()
{
	delete _repaintTimer;
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
	if (!midiMessages.isEmpty())
	{
		String trace;
		trace << "MIDI:";
		for (int i = 0; i < midiMessages.data.size(); ++i)
		{
			trace << String::formatted(" %02X", midiMessages.data[i]);
		}
		writeTrace(trace);

		MidiBuffer::Iterator it(midiMessages);
		MidiMessage midiMessage;
		int samplePosition;
		while (it.getNextEvent(midiMessage, samplePosition))
		{
			if (midiMessage.isNoteOn())
			{
				_play = true;
				_lastNote = midiMessage.getNoteNumber();
				_frequency = midiMessage.getMidiNoteInHertz(_lastNote);
			}
			else if (midiMessage.isNoteOff()
				&& midiMessage.getNoteNumber() == _lastNote)
			{
				_play = false;
			}
		}

		midiMessages.clear();
	}

	buffer.clear(0, 0, buffer.getNumSamples());
	buffer.clear(1, 0, buffer.getNumSamples());

	static long long t = 0;
	static double pi = std::cos(0) * 2;
	double sampleRate = this->getSampleRate();
	float* left = buffer.getWritePointer(0);
	float* right = buffer.getWritePointer(1);
	double x = 2 * pi * 1 / (sampleRate / _frequency);
	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		if (_play)
			left[i] = right[i] = sin(x * t);
		++t;
	}

}

//==============================================================================
bool RemoteGoatVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RemoteGoatVstAudioProcessor::createEditor()
{
	writeTrace("Create editor");
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
const String RemoteGoatVstAudioProcessor::getHelloWorld() const
{
	return "Hello Goat!";
}

std::list<String> RemoteGoatVstAudioProcessor::getTrace()
{
	_traceMutex.lock();
	std::list<String> traceCopy(_trace);
	_traceMutex.unlock();
	return traceCopy;
}

const int RemoteGoatVstAudioProcessor::getTraceCountMaximum() const
{
	return _traceCount;
}

void RemoteGoatVstAudioProcessor::writeTrace(const String& line)
{
	auto time = Time::getCurrentTime();
	String traceLine;
	traceLine << "[" << time.toString(false, true, true, true)
		<< ":" << time.getMilliseconds()
		<< "] " << line;

	_traceMutex.lock();
	{
		_trace.push_back(traceLine);

		if (_trace.size() > getTraceCountMaximum())
			_trace.pop_front();
	}
	_traceMutex.unlock();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RemoteGoatVstAudioProcessor();
}
