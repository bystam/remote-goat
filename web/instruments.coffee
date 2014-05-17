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
    { id: 'BD', name: 'Base Drum', img: '/img/BD.jpg' },
    { id: 'SD', name: 'Snare Drum', img: '/img/BD.jpg' },
    { id: 'LT', name: 'Low Tom', img: '/img/BD.jpg' },
    { id: 'MT', name: 'Middle Tom', img: '/img/BD.jpg' },
    { id: 'HT', name: 'High Tom', img: '/img/BD.jpg' },
    { id: 'RS', name: 'Rim Shot', img: '/img/BD.jpg' },
    { id: 'CP', name: 'Clap', img: '/img/BD.jpg' },
    { id: 'CB', name: 'Cow Bell', img: '/img/BD.jpg' },
    { id: 'CY', name: 'Cymbal', img: '/img/BD.jpg' },
    { id: 'OH', name: 'Open Hi-Hat', img: '/img/BD.jpg' },
    { id: 'CH', name: 'Closed Hi-Hat', img: '/img/BD.jpg' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    