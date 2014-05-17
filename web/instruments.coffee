exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  queue = new InstrumentsQueue()
  app.get '/instruments', (req, res) ->
  	res.json queue.nextInstrument()


class InstrumentsQueue
  INSTRUMENTS = [
    { id: 'BD', name: 'Base Drum', img: 'img/bass.png', color: '#A70267' },
    { id: 'SD', name: 'Snare Drum', img: 'img/snare.png', color: '#F10C49' },
    { id: 'LT', name: 'Low Tom', img: 'img/tom.png', color: '#FB6B41' },
    { id: 'MT', name: 'Middle Tom', img: 'img/tom.png', color: '#F6D86B' },
    { id: 'HT', name: 'High Tom', img: 'img/tom.png', color: '#339194' },
    { id: 'RS', name: 'Rim Shot', img: 'img/snare.png', color: '#58FD98' },
    { id: 'CP', name: 'Clap', img: 'img/clap.png', color: '#0EF3B6' },
    { id: 'CB', name: 'Cow Bell', img: 'img/cowbell.png', color: '#0494BE' },
    { id: 'CY', name: 'Cymbal', img: 'img/cymbal.png', color: '#092794' },
    { id: 'OH', name: 'Open Hi-Hat', img: 'img/hihat.png', color: '#CC6E6B' },
    { id: 'CH', name: 'Closed Hi-Hat', img: 'img/hihat.png', color: '#BBBBBB' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    