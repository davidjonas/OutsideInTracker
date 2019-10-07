//=============== SocketIO Server ============
// var server = require('http').createServer(),
//     socketio = require('socket.io'),
//     io = socketio.listen(server);
//
// server.listen(2222);
// console.log("Websocket server listening on port 2222");
//
// io.sockets.on('connection', function onConnection( socket ){
//   console.log("Client connected!");
// });
//
// function wsSendBlobs(blobs){
//   io.emit("blobs", blobs);
// }

//================ OSC Receiver ==============
var osc = require("osc");

var getIPAddresses = function () {
    var os = require("os"),
        interfaces = os.networkInterfaces(),
        ipAddresses = [];

    for (var deviceName in interfaces) {
        var addresses = interfaces[deviceName];
        for (var i = 0; i < addresses.length; i++) {
            var addressInfo = addresses[i];
            if (addressInfo.family === "IPv4" && !addressInfo.internal) {
                ipAddresses.push(addressInfo.address);
            }
        }
    }

    return ipAddresses;
};

var udpPort = new osc.UDPPort({
    localAddress: "0.0.0.0",
    localPort: 1111
});

udpPort.on("ready", function () {
    var ipAddresses = getIPAddresses();

    console.log("Listening for OSC over UDP.");
    ipAddresses.forEach(function (address) {
        console.log(" Host:", address + ", Port:", udpPort.options.localPort);
    });
});

udpPort.on("message", function (oscMessage) {
    if(oscMessage.address === "/blobs")
    {
      sendBlobs(oscMessage.args[0]);
    }
});

udpPort.on("error", function (err) {
    console.log(err);
});

udpPort.open();
