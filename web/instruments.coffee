instruments = ["BD", "SD", "LT", "MT", "HT", "RS", "CP", "CB", "CY", "OH", "CH"]
i = -1

exports.setupAppForInstruments = (app) ->
  console.log 'app is now set up for instruments :D'

  app.get '/instruments', (req, res) ->
  	if i is instruments.length - 1
  		i = -1
  	res.json({ instrID: instruments[++i]})