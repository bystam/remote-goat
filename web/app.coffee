exports.appAndServerWithJade = ->
  express = require 'express'
  http = require 'http'
  bodyparser = require 'body-parser'
  midi = require 'midi'
  connect = require 'connect'

  app = express()
        .use express.static(__dirname + '/public')
        .use (require 'morgan')() # logger
        .use bodyparser()
        .use connect.methodOverride()
        .set 'view engine', 'jade'
        .set 'views', __dirname + '/views'

  server = http.createServer app
  return [app, server]