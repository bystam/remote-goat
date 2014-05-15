express = require 'express'
app = express()

app.use((require 'morgan')()) # logger

app.get '/', (req, res) ->
  res.send('Hello HTTP!');

# start server
port = 5000;
server = app.listen port, ->
  console.log "Listening on port: #{port}"
