const express = require('express')
const app = express()
const server = require('http').createServer(app);
const WebSocket = require('ws');

const wss = new WebSocket.Server({server:server});

wss.on('connection', function connection(ws) {
	console.log('A new client connected!')
	ws.send('Welcome New client!');
	ws.on('message', function message(data) {
	  console.log('received: %s', data);
	  ws.send('Got ur msg, its: '+ message);
	});
});

app.get('/',(req,res) => res.send('Hello World!'))

server.listen(3000,()=> console.log('listening on port :3000'))