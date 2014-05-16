SocketIoFileUploader = require 'socketio-file-upload'

exports.setupIo = (app, server) ->
  socketio = require 'socket.io'

  app.use SocketIoFileUploader.router
  io = socketio.listen server

  io.on 'connection', setupFileIOForConnection
    

setupFileIOForConnection = (socket) ->
  uploader = new SocketIoFileUploader()
  uploader.dir = './.uploads'
  uploader.listen socket

  uploader.on 'saved', (event) ->
    console.log event.file

  uploader.on 'error', (event) ->
    console.log 'error from uploader', event