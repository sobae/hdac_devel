var port =  1119;
var fs = require('fs');

var WebSocket = require("ws");
var ws = new WebSocket("ws://192.168.70.235:" + port);

ws.onopen = function(event) {

  fs.open('./testlog.txt', 'w', function(err, fd){
      if(err)throw err;
      fdesc = fd;
  });

  ws.send(JSON.stringify({"user":"hdacrpc","pass":"hdac1234"}));
  ws.send(JSON.stringify({"event":["BLOCK:1","TX:1"]}));
  ws.send(JSON.stringify({"method":"getinfo"}));
  
}

var outfile = fs.createWriteStream('./testlog.txt', {flags: 'a+'});

ws.onmessage = function(event){
    var rcvmsg = event.data;
    var result = JSON.parse(rcvmsg);

    outfile.write("*********************************************************************\n");
    outfile.write("           <<  JSON all message  >>\n");
    outfile.write("*********************************************************************\n");
    outfile.write("json parse : \n");
    outfile.write("raw string : \n");
    outfile.write(rcvmsg + "\n");
    outfile.write("*********************************************************************\n\n");

    
    if(result.INFO){
        console.log("<NODE info>");
        console.log(result.INFO);
        console.log("--------------------------------------------\n\n");
    }
    else if(result.AUTH){
        console.log("<Authenticaion result>");
        console.log(result.AUTH);
        console.log("--------------------------------------------\n\n");
    }
    else if(result.BLOCK){
        blockfunc(result.BLOCK);
    }
    else if(result.TX){
        txfunc(result.TX);
    }
    else if(result.method)
    {
        rpcfunc(result);
    }
}

var blockfunc = function(blockinfo){
    var msg = blockinfo;
    console.log("< BLOCK INFO >"); 
    console.log(msg.height);
    console.log(msg.hash);
    console.log("--------------------------------------------\n\n");
}

var txfunc = function(txinfo){
    var msg = txinfo;
    console.log("< Tx INFO >");
    console.log(msg.txid);
    console.log("--------------------------------------------\n\n");
}

var rpcfunc = function(data){
    var msg = data;
    console.log("< RPC method execution result >");
    console.log("method name : "+ data.method);
    if(data.result.code){
       console.log("Error : " + data.result);
    }
    else{
        console.log(data.result);
    }
    console.log("--------------------------------------------\n\n");
}
