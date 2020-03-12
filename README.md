# VCAT-Audio
![Artifact Builder](https://github.com/spearse/VCAT-Audio/workflows/Artifact%20Builder/badge.svg?branch=master)

VCAT-Audio is the core audio backend for the VCAT project by Tom Garner and Stephen Pearse at the University of Portsmouth.


## OSC Specification

All of the core functionality of the engine can be triggered or controlled via *Open Sound Control*. Note, if you want to load a MIDI file, this must be hosted on the same device that the engine is running on. 
All of these commands will return a message with a success state. As such, to use the system you must first register your own IP address and port before using these commands.


Command | OSC Path | Expected Arguments | Implemented | Response | Notes
--------|----------|--------------------|-------------|----------|---------
Setup | /setup | ip-address (string) port-number (int)| [ ] | Standard | This needs to be called before the system will run.
Play/Stop Selected MIDI File | /play | state (int/boolean) | [ ]| Standard|
Load Midi File | /loadmidi | filename (string) | [ ]| Standard | Loads a file into the library system ready for playback.
QueryMidi | /querymidi | | [ ] | /availablemidi ...names(strings) | [ ] | Returns the names of the loaded MIDI files.
Set Selected MIDI | /selectmidi | midi/filename(string) | [ ] | Sets the selected MIDI file for playback.



### OSC Responses

Each command will return a standard response using the path **/response** unless explicitly stated above.  This response will provide an *integer* representing whether the command was successful, the *name* of the command it is responding to (as a string) followed by another string containing an error/wargning message.  If there was no error this string will be null.


