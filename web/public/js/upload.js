$(function () {
  var socket = io.connect('http://localhost');
  socket.emit ('shake', {});

  if (window.DeviceMotionEvent) {
    $('#acc').text('motion is supported');
    window.addEventListener('devicemotion', function(event) {
      var acc = event.acceleration;
      $('#x').text(acc.x);
      $('#y').text(acc.y);
      $('#z').text(acc.z);
    });
  } else {
    $('#acc').text('acc is supported');
  }
});