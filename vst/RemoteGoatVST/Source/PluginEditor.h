/*
  ==============================================================================

  This file was auto-generated by the Introjucer!

  It contains the basic startup code for a Juce application.

  ==============================================================================
  */

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class RemoteGoatVstAudioProcessorEditor : public AudioProcessorEditor
{
public:
	RemoteGoatVstAudioProcessorEditor(RemoteGoatVstAudioProcessor* ownerFilter);
	~RemoteGoatVstAudioProcessorEditor();

	//==============================================================================
	// This is just a standard Juce paint method...
	void paint(Graphics& g);

	//==============================================================================
protected:
	RemoteGoatVstAudioProcessor* getAudioProcessorTyped() const;
};


#endif  // PLUGINEDITOR_H_INCLUDED
