exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  queue = new InstrumentsQueue()
  app.get '/instruments', (req, res) ->
  	res.json queue.nextInstrument()


class InstrumentsQueue
  INSTRUMENTS = [
    { id: 'BD', name: 'Base Drum', img: 'img/BD.jpg', color: '#A70267' },
    { id: 'SD', name: 'Snare Drum', img: 'img/SD.jpg', color: '#F10C49' },
    { id: 'LT', name: 'Low Tom', img: 'img/BD.jpg', color: '#FB6B41' },
    { id: 'MT', name: 'Middle Tom', img: 'img/BD.jpg', color: '#F6D86B' },
    { id: 'HT', name: 'High Tom', img: 'img/BD.jpg', color: '#339194' },
    { id: 'RS', name: 'Rim Shot', img: 'img/BD.jpg', color: '#58FD98' },
    { id: 'CP', name: 'Clap', img: 'img/BD.jpg', color: '#0EF3B6' },
    { id: 'CB', name: 'Cow Bell', img: 'img/BD.jpg', color: '#0494BE' },
    { id: 'CY', name: 'Cymbal', img: 'img/BD.jpg', color: '#092794' },
    { id: 'OH', name: 'Open Hi-Hat', img: 'img/BD.jpg', color: '#CC6E6B' },
    { id: 'CH', name: 'Closed Hi-Hat', img: 'img/BD.jpg', color: '#BBBBBB' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    