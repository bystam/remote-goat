fs = require 'node-fs'
path = require 'path'
wav = require './wav'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  [oldPath, newPath] = getRenamePaths req.files.audiofile, req.body.id

  fs.rename oldPath, newPath, (renameErr) ->
    if renameErr?
      return console.log '#{renameErr}'
    console.log 'LJUD ACUALLY IS SAVED'
    wav.convertToWav newPath, (convertErr) ->
      if convertErr?
        console.log JSON.stringify convertErr
      fs.unlink newPath, (unlinkErr) ->
        if unlinkErr?
          console.log 'unlink file failed'


console.log 'app is set up for sample uploading'

getRenamePaths = (audiofile, id) ->
  oldPath = audiofile.path
  dir = path.dirname(oldPath)
  ext = path.extname(oldPath)
  newName = id + ext
  newPath = path.resolve dir, newName

  return [oldPath, newPath]