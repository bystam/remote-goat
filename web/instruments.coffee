instruments = ["BD", "SD", "LT", "MT", "HT", "RS", "CP", "CB", "CY", "OH", "CH"]
i = -1

exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  app.get '/instruments', (req, res) ->
  	res.json({ instrID: instruments[i = (i++%instruments.length)]})
