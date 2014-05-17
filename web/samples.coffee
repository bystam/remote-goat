fs = require 'node-fs'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  console.log req.files
  fs.readFile req.files.displayImage.path, (err, data) ->
    if err
      return console.log 'file read error #{err}'

    newPath = './upload'
    res.json { status: 'file received' }
    fs.writeFile newPath, data, (err) ->
      console.log 'file upload error #{err}'

console.log 'app is set up for sample uploading'