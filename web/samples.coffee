fs = require 'node-fs'
path = require 'path'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  oldPath = req.files.audiofile.path
  dir = path.dirname(oldPath)
  newPath = path.resolve dir, (req.body.id + '.jpg')
  
  fs.rename oldPath, newPath, (err) ->
    if err?
      return console.log '#{err}'
    console.log 'IMAGE ACUALLY IS SAVED'

console.log 'app is set up for sample uploading'