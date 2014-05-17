exports.setupSocketIO = (server) ->
  socketio = require 'socket.io'
  io = socketio.listen server

  io.on 'connection', (socket) ->
    setupShakeIO socket

  console.log 'io is set up'

setupShakeIO = (socket) ->
  socket.on 'shake', (data) ->
    console.log 'we got a shake!'
  console.log 'socket is set up for shaking !!'
