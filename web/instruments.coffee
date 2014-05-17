
exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  queue = new InstrumentsQueue()
  app.get '/instruments', (req, res) ->
  	res.json queue.nextInstrument()


class InstrumentsQueue
  INSTRUMENTS = [
    { id: 'BD', name: 'Base Drum' },
    { id: 'SD', name: 'Snare Drum' },
    { id: 'LT', name: 'Low Tom' },
    { id: 'MT', name: 'Middle Tom' },
    { id: 'HT', name: 'High Tom' },
    { id: 'RS', name: 'Rim Shot' },
    { id: 'CP', name: 'Clap' },
    { id: 'CB', name: 'Cow Bell' },
    { id: 'CY', name: 'Cymbal' },
    { id: 'OH', name: 'Open Hi-Hat' },
    { id: 'CH', name: 'Closed Hi-Hat' }
  ]

  i: -1

  nextInstrument: () ->
    @i = 0 if ++@i is INSTRUMENTS.length
    return INSTRUMENTS[@i]
    