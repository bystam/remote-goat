fs = require 'node-fs'
path = require 'path'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  [oldPath, newFile] = getRenamePaths (req.files.audiofile)

  fs.rename oldPath, newPath, (err) ->
    if err?
      return console.log '#{err}'
    console.log 'IMAGE ACUALLY IS SAVED'

console.log 'app is set up for sample uploading'

getRenamePaths = (audiofile) ->
  oldPath = req.files.audiofile.path
  dir = path.dirname(oldPath)
  ext = path.extname(oldPath)
  basename = path.basename(oldPath, ext)
  newName = basename + ext
  newPath = path.resolve dir, newName

  return [oldPath, newPath]