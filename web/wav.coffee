exec = (require 'child_process').exec
path = require 'path'

exports.convertToWav = (oldPath, callback) ->
  ext = path.extname oldPath
  base = path.basename oldPath, ext
  goatDir = getGoatDir()
  newPath = path.resolve goatDir, (base + '.wav')

  command = "ffmpeg -i #{oldPath} #{newPath} -y"

  console.log command
  exec command, callback

getGoatDir = () ->
  home = process.env.HOME || process.env.HOMEPATH || process.env.USERPROFILE
  return path.resolve home, '.remote-goat'