remote-goat
===========

Collaborative beatboxing

Audio samples are recorded in the Android app, sent to the web server, stored in the file system (in ~/.remote-goat), loaded by the VST (running on the same server machine) and played when the corresponding MIDI note is sent to the VST (note numbers 0 to 10).

## Setup

### Android

### Web

### VST

1. Install VST Audio Plug-Ins SDK (http://www.steinberg.net/en/company/developer.html)
2. Install JUCE (http://www.juce.com)
3. Build the Introjucer (JUCE extras folder)
4. Run the Introjucer and open the RemoteGoatVST project
5. Build the VST using your preferred build system
6. Get RemoteGoatVST.dll from the Builds folder and load it into a DAW of your choice
