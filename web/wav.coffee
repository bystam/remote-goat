exec = (require 'child_process').exec
path = require 'path'

exports.convertToWav = (oldPath, callback) ->
  dir = path.dirname oldPath
  ext = path.extname oldPath
  base = path.basename oldPath, ext
  newPath = path.resolve dir, (base + '.wav')

  command = "ffmpeg -i #{oldPath} #{newPath}"

  console.log command
  exec command, callback
