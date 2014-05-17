
exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  midi = require 'midi'
  help = require 'midi-help'
  output = new midi.output()
  # // Count the available output ports.
  output.getPortCount()
  
  # // Get the name of a specified output port.
  console.log output.getPortName 1
  
  # // Open the first available output port.
  output.openPort 1

  queue = new InstrumentsQueue()
  app.get '/instruments', (req, res) ->
  	res.json queue.nextInstrument()


  app.get '/instruments/midi', (req, res) ->  
    # // Send a MIDI message.
    output.sendMessage help.noteOn(60,127)
    # // Close the port when done.
    # output.closePort()
    # res.json queue.nextInstrument()

  app.get '/instruments/midi1', (req, res) ->  
    # // Send a MIDI message.
    output.sendMessage help.noteOff(60,127)
    # // Close the port when done.
    # output.closePort()
    # res.json queue.nextInstrument()

class InstrumentsQueue
  INSTRUMENTS = [
    { id: 'BD', name: 'Base Drum' },
    { id: 'SD', name: 'Snare Drum' },
    { id: 'LT', name: 'Low Tom' },
    { id: 'MT', name: 'Middle Tom' },
    { id: 'HT', name: 'High Tom' },
    { id: 'RS', name: 'Rim Shot' },
    { id: 'CP', name: 'Clap' },
    { id: 'CB', name: 'Cow Bell' },
    { id: 'CY', name: 'Cymbal' },
    { id: 'OH', name: 'Open Hi-Hat' },
    { id: 'CH', name: 'Closed Hi-Hat' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    