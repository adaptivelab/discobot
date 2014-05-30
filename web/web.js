var express = require('express');
var path = require('path');
var SerialPort = require("serialport").SerialPort;

var web,
    serialPort,
    colourCodes;

function sendMode(mode) {
    serialPort.write(mode);
}

// Initialize everything
serialPort = new SerialPort("/dev/tty.usbserial-AD02CT03", {baudrate: 9600});
web = express();

web.get('/', function(req, res){
    console.log('/');
    res.send('Usage: /send?mode=[a-z]');
});


web.get('/send', function(req, res){
    var mode = req.query.mode;

    console.log('/send');

    if(/^[a-z]$/.test(mode)) {
        var message = 'Set mode to: `' + req.query.mode + '`';
        sendMode(req.query.mode);
        res.send(message);
        console.log(message);
    } else {
        res.send('Mode not recognised.');
    }
});


web.listen(41570);
