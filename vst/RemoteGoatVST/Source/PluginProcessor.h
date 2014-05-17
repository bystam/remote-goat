/*
  ==============================================================================

  This file was auto-generated!

  It contains the basic startup code for a Juce application.

  ==============================================================================
  */

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <list>
#include <mutex>
#include <map>

class RepaintTimer;
class Sample;
class FilesystemTimer;

#define SAMPLE_NAMES_COUNT 11
char* const SAMPLE_NAMES[SAMPLE_NAMES_COUNT] =
{ "BD", "CB", "CH", "CP", "CY", "HT", "LT", "MT", "OH", "RS", "SD" };

//==============================================================================
/**
*/
class RemoteGoatVstAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	RemoteGoatVstAudioProcessor();
	~RemoteGoatVstAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;

	//==============================================================================
	const String getName() const;

	int getNumParameters();

	float getParameter(int index);
	void setParameter(int index, float newValue);

	const String getParameterName(int index);
	const String getParameterText(int index);

	const String getInputChannelName(int channelIndex) const;
	const String getOutputChannelName(int channelIndex) const;
	bool isInputChannelStereoPair(int index) const;
	bool isOutputChannelStereoPair(int index) const;

	bool acceptsMidi() const;
	bool producesMidi() const;
	bool silenceInProducesSilenceOut() const;
	double getTailLengthSeconds() const;

	//==============================================================================
	int getNumPrograms();
	int getCurrentProgram();
	void setCurrentProgram(int index);
	const String getProgramName(int index);
	void changeProgramName(int index, const String& newName);

	//==============================================================================
	void getStateInformation(MemoryBlock& destData);
	void setStateInformation(const void* data, int sizeInBytes);

	//==============================================================================
	const String getHelloWorld() const;
	std::list<String> getTrace();
	const int getTraceCountMaximum() const;
	void writeTrace(const String& line);

	Sample& getSample(const String& sampleName);
private:
	std::mutex _traceMutex;
	std::list<String> _trace;
	const int _traceCount = 10;
	RepaintTimer* _repaintTimer;

	std::map<String, Sample> _samples;
	FilesystemTimer* _filesystemTimer;
	std::map<int, String> _noteNumberSampleNameMap;

private:
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RemoteGoatVstAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
