var express = require('express');
var http = require('http');

var app = express();
var path = require('path');

var server = http.createServer(app);
server.listen(3000);

var io = require('socket.io').listen(server);
console.log('socket server run!!');

require('events').EventEmitter.prototype._maxListeners = 500;

var bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended : true}));

var serialPort = require('serialport');
var com10 = new serialPort('COM8',{
  baudRate : 19200,
  dataBits : 8,
  parity : 'none',
  stopBits : 1,
  flowControl : false
})
com10.on('open', function(){
  console.log('open serial communication');
})

io.sockets.on('connection',function(socket){
  com10.on('data',function(data){
    //val = data;
    console.log("data:"+data);
    //console.log("type:"+data.toString());
    socket.emit('toclient',data.toString());
  });
});



app.set('views',path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use(express.static(path.join(__dirname, 'public')));

app.get('/',function(req, res){
  res.status(200).render('map.ejs');
})

app.post('/form_receiver', function(req,res){
  var lat = req.body.lat;
  var lng = req.body.lng;
  var arr = [];
  for(i=0; i<9; i++){
    arr.push(lat.charAt(i));

  }
  for(j=0; j<10; j++){

    arr.push(lng.charAt(j));
  }
  console.log("latitude: "+lat.substr(0,9));
  console.log("longitude: "+lng.substr(0,10));
  //for(k=0; k<arr.length; k++){
    //com10.write(arr[k]);
  //}
  var k=0;
  var com = setInterval(function(){
   com10.write(arr[k]);
   k++;
   if(k==19){
     clearInterval(com);
   }
 },140);
  //com10.write(lat.substr(0,9)+lng.substr(0,10));
})
//app.post('/form_receiver2', function(req,res){
//  console.log("longitude: ",req.body.lng);
//  com10.write("l"+req.body.lng+" ");
//})

app.post('/key_receiver', function(req,res){
  console.log("key: ",req.body.opt);
  com10.write(req.body.opt);
})

app.post('/p_value', function(req,res){
  var arr2 = [];
  var pvalue = req.body.pval;
  var l, h;

  for(l=0; l<pvalue.length; l++){
    arr2.push(pvalue.charAt(l));
  }
  h=0;
  console.log("p_value: "+req.body.pval);
  var pp = setInterval(function(){
    com10.write(arr2[h]);
    h++;
    if(h==pvalue.length){
      clearInterval(pp);
    }
  },500);
  //setTimeout(function(){
  //  com10.write(pvalue);
//  },1000);

})
