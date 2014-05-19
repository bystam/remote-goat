remote-goat
===========

Collaborative beatboxing

Audio samples are recorded in the Android app, sent to the web server, stored in the file system (in ~/.remote-goat), loaded by the VST (running on the same server machine) and played when the corresponding MIDI note is sent to the VST (note numbers 0 to 10).

## Setup

### Android

### Web

1. Install node.js (http://nodejs.org/)
2. using npm, install coffee-script globally (npm install -g coffee-script)
3. install ffmpeg (http://www.ffmpeg.org/ or brew install ffmpeg)
4. install sox (http://sox.sourceforge.net/ or brew install sox)
5. ensure ffmpeg and sox is in your path
3. Navigate to remote-goat/web
4. start server (npm start)
5. uploaded sound files from the android app will be stored in HOME/.remote-goat

### VST

1. Install VST Audio Plug-Ins SDK (http://www.steinberg.net/en/company/developer.html)
2. Install JUCE (http://www.juce.com)
3. Build the Introjucer (JUCE extras folder)
4. Run the Introjucer and open the RemoteGoatVST project
5. Build the VST using your preferred build system
6. Get RemoteGoatVST.dll from the Builds folder and load it into a DAW of your choice
