var app = require('http').createServer(handler)
  , io  = require('socket.io').listen(app)
  , fs  = require('fs')
  , net = require('net')
  , url = require('url')

var LISTEN_PORT= 8000;
var GL_PORT    = 9000;
app.listen(LISTEN_PORT);

function handler (req, res) {
  var MIME = {
    ".bmp"  : "image\/bmp",
    ".css"  : "text\/css",
    ".gif"  : "image\/gif",
    ".htm"  : "text\/html",
    ".html" : "text\/html",
    ".ico"  : "image\/vnd.microsoft.icon",
    ".jpeg" : "image\/jpeg",
    ".jpg"  : "image\/jpeg",
    ".js"   : "text\/javascript",
    ".lzh"  : "application\/lha",
    ".png"  : "image\/png",
    ".zip"  : "application\/zip"
  };
 
  var path = url.parse(req.url).pathname;
  if(path == '/') path = '/app.html';
  var ext = path.match(/\.[A-Z0-9]+$/i);
  
  fs.readFile(__dirname + path,
  function (err, data) {
    var statusCode = 200, contentType = 'text/plain';
    if (err) {
	  statusCode = 500;
      res.writeHead(statusCode);
      return res.end('Error loading: ' + path);
    }

	statusCode = 200;
	if(MIME.hasOwnProperty(ext))
	  contentType = MIME[ext];
    res.writeHead(statusCode, {'Content-Type': contentType});
    res.end(data);
  });
}

io.sockets.on('connection', function (socket) {
  var glclient = net.connect({port:GL_PORT}, function(){
    socket.on('glManager', function (data) {
      glclient.write(data.toString()+"\n");
    });

    socket.on('disconnect', function() { 
      glclient.end();
    });
  });
});
