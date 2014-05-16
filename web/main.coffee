app = (require './app').appWithJade()

app.get '/', (req, res) ->
  res.render('index', {})
.listen 5000, ->
  console.log 'started listending on port 5000'