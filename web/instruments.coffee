exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  queue = new InstrumentsQueue()
  app.get '/instruments', (req, res) ->
  	res.json queue.nextInstrument()


class InstrumentsQueue
  INSTRUMENTS = [
    { id: 'BD', name: 'Base Drum', img: 'img/BD.jpg' },
    { id: 'SD', name: 'Snare Drum', img: 'img/BD.jpg' },
    { id: 'LT', name: 'Low Tom', img: 'img/BD.jpg' },
    { id: 'MT', name: 'Middle Tom', img: 'img/BD.jpg' },
    { id: 'HT', name: 'High Tom', img: 'img/BD.jpg' },
    { id: 'RS', name: 'Rim Shot', img: 'img/BD.jpg' },
    { id: 'CP', name: 'Clap', img: 'img/BD.jpg' },
    { id: 'CB', name: 'Cow Bell', img: 'img/BD.jpg' },
    { id: 'CY', name: 'Cymbal', img: 'img/BD.jpg' },
    { id: 'OH', name: 'Open Hi-Hat', img: 'img/BD.jpg' },
    { id: 'CH', name: 'Closed Hi-Hat', img: 'img/BD.jpg' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    