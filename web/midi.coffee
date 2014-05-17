
midi = require 'midi'
help = require 'midi-help'
output = new midi.output()
# // Count the available output ports.
output.getPortCount()

# // Get the name of a specified output port.
console.log output.getPortName 1

# // Open the first available output port.
output.openPort 1



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
# midi = require 'midi'
# help = require 'midi-help'

# output = new midi.output()

# # // Count the available output ports.
# output.getPortCount()

# # // Get the name of a specified output port.
# console.log output.getPortName 1

# # // Open the first available output port.
# output.openPort 1

# # // Send a MIDI message.
# # output.sendMessage [176,22,1]
# output.sendMessage help.noteOn(60,127)

# # // Close the port when done.
# output.closePort() 