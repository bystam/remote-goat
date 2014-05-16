###
midi = require 'midi'
output = new midi.output()
console.log output.getPortName 1 # prints IAC Driver goat
output.openPort 1
output.sendMessage [176, 22, 1] # send some crazy midi
output.closePort()
###
