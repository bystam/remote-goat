[app, server] = (require './app').appAndServerWithJade()
(require './instruments').setupAppForInstruments app
(require './samples').setupAppForSamples app
(require './io').setupSocketIO server

app.get '/', (req, res) ->
  res.render 'index', {}
 

server.listen 80, ->
  console.log 'started listending on port 80'
