ffmpeg = require 'fluent-ffmpeg'

proc = new ffmpeg({ source: newPath, nolog: true})
		.saveToFile 'BD.wav', (retcode, error) ->
			console.log 'Lolfi golfi'