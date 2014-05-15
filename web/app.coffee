express = require 'express'
app = express()

app.use((require 'morgan')()) # logger

app.get '/', (req, res) ->
  res.send('Hello HTTP!');

# start server
port = 5000;
server = app.listen port, ->
  console.log "Listening on port: #{port}"


###
midi = require 'midi'
output = new midi.output()
console.log output.getPortName 1 # prints IAC Driver goat
output.openPort 1
output.sendMessage [176, 22, 1] # send some crazy midi
output.closePort()
###
