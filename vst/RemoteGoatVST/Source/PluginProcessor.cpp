/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <map>
#include <set>

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
	bool _readyToSwap;

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

	const String& getName() const
	{
		return _name;
	}

	// Read <path>/<_name><EXT> and store it in the backbuffer.
	void update(const String& path, WavAudioFormat& wavAudioFormat)
	{
		// Don't load a subsequent sample if a new sample is already loaded (but not yet played).
		if (_readyToSwap)
			return;

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
		_readyToSwap = true;
	}

	// Read <n> samples from frontbuffer into <buffer>.
	void read(AudioSampleBuffer& output, int offset, int count, bool isNoteOn)
	{
		if (isNoteOn)
		{
			if (_readyToSwap)
				swap();
			_offsets[_bufferIndex] = 0;
		}
		AudioSampleBuffer* buffer = &(_buffers[_bufferIndex]);
		if (buffer->getNumChannels() == 0)
			return;
		const float* data = buffer->getReadPointer(0);
		data += _offsets[_bufferIndex];
		count = std::min(count, (int)(buffer->getNumSamples() - _offsets[_bufferIndex]));
		output.addFrom(0, offset, data, count);
		output.addFrom(1, offset, data, count);
		_offsets[_bufferIndex] += count;
	}

private:
	void swap()
	{
		int newIndex = !_bufferIndex;
		_bufferIndex = newIndex; // Swap buffers atomically.
		_readyToSwap = false;
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

	for (int i = 0; i < SAMPLE_NAMES_COUNT; ++i)
		_noteNumberSampleNameMap[i] = SAMPLE_NAMES[i];
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
	}

	// For each sample name,
	// a sorted collection of "note on" event sample positions.
	std::map<String, std::set<int>> noteOnSets;

	MidiBuffer::Iterator it(midiMessages);
	MidiMessage midiMessage;
	int samplePosition;
	while (it.getNextEvent(midiMessage, samplePosition))
	{
		if (midiMessage.isNoteOn())
		{
			// Check note number, map to sample name.
			// Save note on sample position for sample.
			int note = midiMessage.getNoteNumber();
			auto itt = _noteNumberSampleNameMap.find(note);
			if (itt != _noteNumberSampleNameMap.end())
			{
				String sampleName = itt->second;
				noteOnSets[sampleName].insert(samplePosition);
			}
		}
	}

	midiMessages.clear();

	buffer.clear(0, 0, buffer.getNumSamples());
	buffer.clear(1, 0, buffer.getNumSamples());

	for (auto& samplePair : _samples)
	{
		Sample& sample = samplePair.second;
		auto it = noteOnSets.find(sample.getName());
		if (it != noteOnSets.end())
		{
			std::set<int>& noteOns = it->second;
			int offset = *noteOns.begin();
			sample.read(buffer, 0, offset, false);
			for (auto itt = noteOns.begin(); itt != noteOns.end(); ++itt)
			{
				int noteOn = *itt;
				auto ittt = itt;
				++ittt;
				if (ittt != noteOns.end())
				{
					int noteOnNext = *ittt;
					int diff = noteOnNext - noteOn;
					sample.read(buffer, offset, diff, true);
					offset += diff;
				}
				else
				{
					sample.read(buffer, offset, buffer.getNumSamples() - offset, true);
				}
			}
		}
		else
		{
			sample.read(buffer, 0, buffer.getNumSamples(), false);
		}
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
