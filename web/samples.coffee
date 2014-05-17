fs = require 'node-fs'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  for key, value of req
    console.log "#{key} = #{value}"
  return
  fs.readFile req.files.displayImage.path, (err, data) ->
    if err
      return console.log 'file read error #{err}'

    newPath = './upload'
    res.json { status: 'file received' }
    fs.writeFile newPath, data, (err) ->
      console.log 'file upload error #{err}'

console.log 'app is set up for sample uploading'