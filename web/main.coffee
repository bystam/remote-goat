app = (require './app').appWithJade()
(require './io').setupIoForApp app

app
.get '/', (req, res) ->
  res.render('index', {})

app.listen 5000, ->
  console.log 'started listending on port 5000'