fs = require 'node-fs'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  console.log req.body
  console.log req.files
  newPath = './upload'
  res.json { status: 'file received' }
  fs.writeFile newPath, req.body.file, (err) ->
    console.log 'file upload error #{err}'

console.log 'app is set up for sample uploading'