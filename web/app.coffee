exports.appAndServerWithJade = ->
  express = require 'express'
  http = require 'http'
  bodyparser = require 'body-parser'
  connect = require 'connect'
  multer = require 'multer'

  app = express()
        .use express.static(__dirname + '/public')
        .use (require 'morgan')() # logger
        .use bodyparser()
        .use multer({ dest: './uploads/'})
        #.use connect.methodOverride()
        .set 'view engine', 'jade'
        .set 'views', __dirname + '/views'

  server = http.createServer app
  return [app, server]