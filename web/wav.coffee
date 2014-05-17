exec = (require 'child_process').exec
path = require 'path'

exports.convertToWav = (oldPath, callback) ->
  ext = path.extname oldPath
  base = path.basename oldPath, ext
  goatDir = getGoatDir()
  newPath = path.resolve goatDir, (base + '.wav')

  command = "ffmpeg -i #{oldPath} #{newPath}"

  console.log command
  exec command, callback

getGoatDir = () ->
  envVar = process.platform is 'win32' ? 'USERPROFILE' : 'HOME'
  home = process.env[envVar] 
  return path.resolve home '.remote-goat'