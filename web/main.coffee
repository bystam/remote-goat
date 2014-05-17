[app, server] = (require './app').appAndServerWithJade()
(require './instruments').setupAppForInstruments app
(require './samples').setupAppForSamples app

app.get '/', (req, res) ->
  res.render 'index', {}

var output = new midi.output()

# // Count the available output ports.
output.getPortCount()

# // Get the name of a specified output port.
output.getPortName 0

# // Open the first available output port.
output.openPort 0

# // Send a MIDI message.
output.sendMessage [176,22,1]

# // Close the port when done.
output.closePort()  

server.listen 80, ->
  console.log 'started listending on port 80'
