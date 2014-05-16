exports.appWithJade = ->
  express = require 'express'
  app = express()
        .use express.static(__dirname + '/public')
        .use (require 'morgan')() # logger
        .set 'view engine', 'jade'
        .set 'views', __dirname + '/views'

###
midi = require 'midi'
output = new midi.output()
console.log output.getPortName 1 # prints IAC Driver goat
output.openPort 1
output.sendMessage [176, 22, 1] # send some crazy midi
output.closePort()
###
