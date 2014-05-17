[app, server] = (require './app').appAndServerWithJade()
(require './instruments').setupAppForInstruments app
(require './samples').setupAppForSamples app

app.get '/', (req, res) ->
  res.render 'index', {}

server.listen 5000, ->
  console.log 'started listending on port 5000'
