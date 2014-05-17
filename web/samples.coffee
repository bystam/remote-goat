fs = require 'node-fs'
path = require 'path'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  [oldPath, newPath] = getRenamePaths req.files.audiofile, req.body.id

  fs.rename oldPath, newPath, (err) ->
    if err?
      return console.log '#{err}'
    console.log 'LJUD ACUALLY IS SAVED'

console.log 'app is set up for sample uploading'

getRenamePaths = (audiofile, id) ->
  oldPath = audiofile.path
  dir = path.dirname(oldPath)
  ext = path.extname(oldPath)
  newName = id + ext
  newPath = path.resolve dir, newName

  return [oldPath, newPath]