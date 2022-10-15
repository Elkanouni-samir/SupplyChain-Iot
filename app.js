const express = require('express')
const app = express()
const server = require('http').createServer(app);
const WebSocket = require('ws');
var mongo = require('mongodb').MongoClient;

mongo.connect("mongodb://localhost:27017/", function(err, db) {
  if (err) throw err;

  dbo = db.db("esp32");
  collection = dbo.collection("time"); 	});

const wss = new WebSocket.Server({server:server});

wss.on('connection', function connection(ws) {
	console.log('A new client connected!')
	ws.send('Welcome New client!');

	ws.on('message', function message(data) {
		  console.log('received: %s', data);
		  ws.send('Got ur msg, its: ' + data);
		  let text = data.toString();
		  if(data!="Connceted"){
			  dbo.collection("time").insertOne(({ time: text, ok: 10 }), function(err, res) {
			  		if (err) throw err;
			        console.log("1 document inserted");	
			  });
		  }
	});

});

server.listen(3000,()=> console.log('listening on port :3000'))