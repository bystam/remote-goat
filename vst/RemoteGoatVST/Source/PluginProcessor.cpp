/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <map>

class RepaintTimer : public juce::Timer
{
private:
	RemoteGoatVstAudioProcessor* _processor;

public:
	RepaintTimer(RemoteGoatVstAudioProcessor* processor) : _processor(processor)
	{
		this->startTimer(16);
	}

	virtual void timerCallback()
	{
		auto* ed = _processor->getActiveEditor();
		if (ed != nullptr) ed->repaint();
	}
};

class Sample
{
private:
	RemoteGoatVstAudioProcessor* _processor;
	String _name;
	AudioSampleBuffer _buffers[2];
	int _offsets[2];
	int _bufferIndex;
	Time _lastModification;

public:
	const char* EXT = ".wav";
	const char* WILDCARD = "*.wav";

	Sample()
	{
	}

	Sample(RemoteGoatVstAudioProcessor* processor, const String& name)
		: _processor(processor),
		_name(name),
		_bufferIndex(0),
		_lastModification(0)
	{
		memset(_offsets, 0, sizeof(_offsets));
	}

	// Read <path>/<_name><EXT> and store it in the backbuffer.
	void update(const String& path, WavAudioFormat& wavAudioFormat)
	{
		// Find audio file.
		String fileName(path);
		fileName = File::addTrailingSeparator(fileName);
		fileName += _name;
		fileName += EXT;
		File file(fileName);

		Time modification = file.getLastModificationTime();
		if (modification <= _lastModification)
			return;
		_lastModification = modification;
		_processor->writeTrace(String() << "Updating " << _name);

		// Read audio file. We only read the left channel, mono is good enough.
		FileInputStream* stream = file.createInputStream();
		AudioFormatReader* reader = wavAudioFormat.createReaderFor(stream, true);
		int newIndex = !_bufferIndex;
		AudioSampleBuffer* buffer = &(_buffers[newIndex]);
		buffer->setSize(1, reader->lengthInSamples);
		reader->read(buffer, 0, (int)reader->lengthInSamples, 0, true, false);

		// Done.
		swap();
	}

	// Read <n> samples from frontbuffer into <buffer>. Ish. TODO
	void read()
	{
		// TODO: Check if frontbuffer is empty.
	}

private:
	void swap()
	{
		_offsets[!_bufferIndex] = 0; // Start from beginning of backbuffer.
		_bufferIndex = !_bufferIndex; // Swap buffers atomically.
	}
};

class FilesystemTimer : public juce::Timer
{
private:
	RemoteGoatVstAudioProcessor* _processor;
	int _period;
	WavAudioFormat _wavAudioFormat;

public:
	FilesystemTimer(RemoteGoatVstAudioProcessor* processor) :
		_processor(processor),
		_period(200),
		_wavAudioFormat()
	{
		this->startTimer(_period);
	}

	virtual void timerCallback()
	{
		this->stopTimer();

		// Poll sample directory.
		String path = File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory)
			.getFullPathName();
		path = File::addTrailingSeparator(path);
		path += ".remote-goat";
		
		for (const String& sampleName : SAMPLE_NAMES)
		{
			_processor->getSample(sampleName).update(path, _wavAudioFormat);
		}

		this->startTimer(_period);
	}
};

//==============================================================================
RemoteGoatVstAudioProcessor::RemoteGoatVstAudioProcessor()
{
	writeTrace("Goat Trace!");

	_repaintTimer = new RepaintTimer(this);
	
	for (const String& sampleName : SAMPLE_NAMES)
	{
		_samples[sampleName] = Sample(this, sampleName);
	}

	_filesystemTimer = new FilesystemTimer(this);

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
	const double pi = std::cos(0) * 2;
	double sampleRate = this->getSampleRate();
	float* left = buffer.getWritePointer(0);
	float* right = buffer.getWritePointer(1);
	for (int i = 0; i < buffer.getNumSamples(); ++i)
	{
		//if (_play)
		//{
		//	double x = 2 * pi * 1 / (sampleRate / _frequency);
		//	left[i] = right[i] = sin(x * t);
		//}
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

Sample& RemoteGoatVstAudioProcessor::getSample(const String& sampleName)
{
	return _samples[sampleName];
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RemoteGoatVstAudioProcessor();
}
