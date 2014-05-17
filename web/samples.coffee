fs = require 'node-fs'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  fs.readFile req.files.displayImage.path, (err, data) ->
    newPath = './upload'
    fs.writeFile newPath, data, (err) ->
      console.log 'file upload error #{err}'

console.log 'app is set up for sample uploading'