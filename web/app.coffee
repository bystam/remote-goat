exports.appWithJade = ->
  express = require 'express'

  app = express()
        .use express.static(__dirname + '/public')
        .use (require 'morgan')() # logger
        .set 'view engine', 'jade'
        .set 'views', __dirname + '/views'

  return app

