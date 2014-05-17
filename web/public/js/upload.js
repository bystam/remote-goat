$(function () {
  console.log('local socket is up?');
  var socket = io.connect('http://localhost');
  console.log('socket');
  socket.emit ('shake', {});
});