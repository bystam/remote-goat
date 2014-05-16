exports.appAndServerWithJade = ->
  express = require 'express'
  http = (require 'http')

  app = express()
        .use express.static(__dirname + '/public')
        .use (require 'morgan')() # logger
        .set 'view engine', 'jade'
        .set 'views', __dirname + '/views'

  server = http.createServer app
  return [app, server]

