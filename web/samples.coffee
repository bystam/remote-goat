fs = require 'node-fs'
multiparty = require 'multiparty'

exports.setupAppForSamples = (app) ->
  app.post '/sample', uploadSample


uploadSample = (req, res) ->
  form = new multiparty.Form()

  form.parse req, (err, fields, files) ->
    console.log fields

  res.json { status: 'file received' }

console.log 'app is set up for sample uploading'