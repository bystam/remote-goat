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

Sample::Sample(RemoteGoatVstAudioProcessor* processor, const String& name)
: _processor(processor),
_name(name),
_bufferIndex(0),
_lastModification(0),
_readyToSwap(false),
_alive(false)
{
	memset(_offsets, 0, sizeof(_offsets));
}

void Sample::update(const String& path, WavAudioFormat& wavAudioFormat)
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

	// Read audio file. We only read the left channel, mono is good enough.
	AudioFormatReader* reader = wavAudioFormat.createReaderFor(file.createInputStream(), true);
	if (reader == nullptr)
		return;
	_lastModification = modification;

	int64 start = reader->searchForLevel(0, reader->lengthInSamples, SAMPLE_START_THRESHOLD, 1.0, 0);
	if (start == -1)
		start = 0;
	int count = (int)(reader->lengthInSamples - start);

	_processor->writeTrace(String() << "Loading " << _name << " from disk (skip=" << start << ")");

	int newIndex = !_bufferIndex;
	AudioSampleBuffer* buffer = &(_buffers[newIndex]);
	buffer->setSize(1, count);

	reader->read(buffer, 0, count, start, true, false);

	delete reader;

	// Done.
	_readyToSwap = true;
}

void Sample::read(AudioSampleBuffer& output, int offset, int count, bool isNoteOn)
{
	if (isNoteOn)
	{
		_alive = true;
		if (_readyToSwap)
			swap();
		_offsets[_bufferIndex] = 0;
	}
	if (!_alive)
		return;
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

void Sample::noteOff()
{
	_alive = false;
	_offsets[_bufferIndex] = 0; // XXX: Race.
}

int64 Sample::getMsecSinceLoad() const
{
	return (Time::currentTimeMillis() - _lastModification.toMilliseconds());
}

int64 Sample::getMsecSinceNoteOn() const
{
	return 0;
}

void Sample::swap()
{
	int newIndex = !_bufferIndex;
	_bufferIndex = newIndex; // Swap buffers atomically.
	_readyToSwap = false;
}

class FilesystemTimer : public juce::Timer
{
private:
	RemoteGoatVstAudioProcessor* _processor;
	int _period;
	WavAudioFormat* _wavAudioFormat;

public:
	FilesystemTimer(RemoteGoatVstAudioProcessor* processor) :
		_processor(processor),
		_period(200),
		_wavAudioFormat(new WavAudioFormat)
	{
		this->startTimer(_period);
	}

	~FilesystemTimer()
	{
		if (_wavAudioFormat != nullptr)
			delete _wavAudioFormat;
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
			_processor->getSample(sampleName).update(path, *_wavAudioFormat);
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
	delete _filesystemTimer;
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

float RemoteGoatVstAudioProcessor::getParameter(int index)
{
	return 0.0f;
}

void RemoteGoatVstAudioProcessor::setParameter(int index, float newValue)
{
}

const String RemoteGoatVstAudioProcessor::getParameterName(int index)
{
	return String::empty;
}

const String RemoteGoatVstAudioProcessor::getParameterText(int index)
{
	return String::empty;
}

const String RemoteGoatVstAudioProcessor::getInputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

const String RemoteGoatVstAudioProcessor::getOutputChannelName(int channelIndex) const
{
	return String(channelIndex + 1);
}

bool RemoteGoatVstAudioProcessor::isInputChannelStereoPair(int index) const
{
	return true;
}

bool RemoteGoatVstAudioProcessor::isOutputChannelStereoPair(int index) const
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

void RemoteGoatVstAudioProcessor::setCurrentProgram(int index)
{
}

const String RemoteGoatVstAudioProcessor::getProgramName(int index)
{
	return String::empty;
}

void RemoteGoatVstAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void RemoteGoatVstAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
}

void RemoteGoatVstAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

void RemoteGoatVstAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	//if (!midiMessages.isEmpty())
	//{
	//	String trace;
	//	trace << "MIDI:";
	//	for (int i = 0; i < midiMessages.data.size(); ++i)
	//	{
	//		trace << String::formatted(" %02X", midiMessages.data[i]);
	//	}
	//	writeTrace(trace);
	//}

	// For each sample name,
	// a sorted collection of "note on" event sample positions.
	std::map<String, std::set<std::pair<int, bool>>> noteOnSets;

	MidiBuffer::Iterator it(midiMessages);
	MidiMessage midiMessage;
	int samplePosition;
	while (it.getNextEvent(midiMessage, samplePosition))
	{
		// Check note number, map to sample name.
		int note = midiMessage.getNoteNumber();
		auto itt = _noteNumberSampleNameMap.find(note);
		if (itt != _noteNumberSampleNameMap.end())
		{
			String sampleName = itt->second;

			if (midiMessage.isNoteOn())
				// Save note on sample position for sample.
				noteOnSets[sampleName].insert(std::make_pair(samplePosition, true));
			else if (midiMessage.isNoteOff())
				noteOnSets[sampleName].insert(std::make_pair(samplePosition, false));
		}
	}

	midiMessages.clear();

	buffer.clear(0, 0, buffer.getNumSamples());
	buffer.clear(1, 0, buffer.getNumSamples());

	for (auto& samplePair : _samples)
	{
		Sample& sample = samplePair.second;
		auto noteOnSetsIterator = noteOnSets.find(sample.getName());
		if (noteOnSetsIterator != noteOnSets.end())
		{
			const std::set<std::pair<int, bool>>& noteOns = noteOnSetsIterator->second;
			int offset = noteOns.begin()->first;
			sample.read(buffer, 0, offset, false);
			for (auto noteOnIterator = noteOns.begin(); noteOnIterator != noteOns.end(); ++noteOnIterator)
			{
				int noteOn = noteOnIterator->first;
				bool onOrOff = noteOnIterator->second;
				writeTrace(String() << "Triggered " << sample.getName() + " (" << (int)onOrOff << ")");
				auto nextNoteOnIterator = noteOnIterator;
				++nextNoteOnIterator;
				if (nextNoteOnIterator != noteOns.end())
				{
					int nextNoteOn = nextNoteOnIterator->first;
					int diff = nextNoteOn - noteOn;
					if (onOrOff)
						sample.read(buffer, offset, diff, true);
					else
						sample.noteOff();
					offset += diff;
				}
				else
				{
					if (onOrOff)
						sample.read(buffer, offset, buffer.getNumSamples() - offset, true);
					else
						sample.noteOff();
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
	return new RemoteGoatVstAudioProcessorEditor(this);
}

//==============================================================================
void RemoteGoatVstAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void RemoteGoatVstAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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
