exec = (require 'child_process').exec
path = require 'path'

exports.convertToWav = (oldPath, callback) ->
  ext = path.extname oldPath
  base = path.basename oldPath, ext
  dir = path.dirname oldPath
  wavPath = path.resolve dir, (base + '.wav')

  command = "ffmpeg -i #{oldPath} -ar 44100 #{wavPath} -y"

  console.log command
  exec command, (err) ->
  	if err?
  		return console.log JSON.stringify(err)

  	goatDir = getGoatDir()
  	newPath = path.resolve goatDir, (base + '.wav')
  	command = "sox #{wavPath} #{newPath} silence 1 0.1 10%"
  	console.log command
  	exec command, callback
  	


getGoatDir = () ->
  home = process.env.HOME || process.env.HOMEPATH || process.env.USERPROFILE
  return path.resolve home, '.remote-goat'