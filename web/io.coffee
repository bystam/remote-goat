SocketIoFileUploader = require 'socketio-file-upload'

exports.setupIoForApp = (app) ->
  socketio = require 'socket.io'
  server = (require 'http').createServer app

  app.use SocketIoFileUploader.router
  io = socketio.listen server

  io.on 'connection', setupFileIOForConnection
    

setupFileIOForConnection = (socket) ->
  uploader = new SocketIoFileUploader()
  uploader.dir = '/public/uploads'
  uploader.listen socket

  uploader.on 'saved', (event) ->
    console.log event.file

  uploader.on 'error', (event) ->
    console.log 'error from uploader', event