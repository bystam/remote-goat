[app, server] = (require './app').appAndServerWithJade()
# (require './io').setupIo app, server

app
.get '/', (req, res) ->
  res.render('index', {})

server.listen 5000, ->
  console.log 'started listending on port 5000'
