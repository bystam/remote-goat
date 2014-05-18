fs = require 'node-fs'
path = require 'path'
wav = require './wav'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  [oldPath, newPath] = getRenamePaths req.files.audiofile, req.body.id

  fs.rename oldPath, newPath, (renameErr) ->
    if renameErr?
      res.json { err: 'RENAME TO WAV GICK FEL!!!!' }
      return console.log '#{renameErr}'

    console.log 'LJUD ACUALLY IS SAVED'
    wav.convertToWav newPath, (convertErr) ->
      if convertErr?
        res.json { err: 'CONVERT TO WAV GICK FEL!!!!' }
        return console.log '#{convertErr}'


      console.log 'WAV ACUALLY IS SAVED'
      fs.unlink newPath, (unlinkErr) ->
        if unlinkErr?
          res.json { err: 'UNLINK TO WAV GICK FEL!!!!' }
          return console.log '#{unlinkErr}'

        res.json { string: 'schysst sträng' }


console.log 'app is set up for sample uploading'

getRenamePaths = (audiofile, id) ->
  oldPath = audiofile.path
  dir = path.dirname(oldPath)
  ext = path.extname(oldPath)
  newName = id + ext
  newPath = path.resolve dir, newName

  return [oldPath, newPath]