Used Websockettp (ver 0.8.1 )
---------------------
Official : [https://www.zaphoyd.com/websocketpp/](https://www.zaphoyd.com/websocketpp/)

Github   : [https://github.com/zaphoyd/websocketpp](https://github.com/zaphoyd/websocketpp)

---
### Supported Features

* Send/Response's format is JSON.
* Registration events
* Broadcast event
* Execution of the RPC command

---
1. Start daemon
- Set port number to be used by websocket
- runtime parameter is " -wsport=<port#> "
```
hdacd hdac -daemon -wsport=1009
```

---
2. Connection to daemon
- send username and password 
- refer to hdac.conf
```
JSON:  {"user":<rpcuser>,"pass":<rpcpassword>}
    {"user":"hdacrpc","pass":"GpdLqLp5129c91PcNrMTjA7h5yJTwSAHox7JYgBtA8Ke"}
```

--- 
3. Registration of Events
- new Block
- new Transacton
- Node status ( Sutdown, etc.. )

```
< Request JSON >
JSON: {"event",["BLOCK:<level>","TX:<level>","STATUS","DEBUGLOG"]}
    {"event",["BLOCK:1","TX:1","STATUS"]}
```
```
< Response JSON >
{"BLOCK":{"hash":"0000000000005210c5c849b674a236d0531ba48901eff4f760a7d621a095e8d8", ......}}
{"TX":{"txid":"0bb9bc1759dd13702f85ae027638c52e52ada18a8271b2f1301a1cc408a08d63"}}
{"STATUS:"Shutdown hdac daemon"}
```
```
< JSON value >
   BLOCK level:    (0-2)
   TX level:       (0-1)
   STATUS:         only shutdown ( the other is TBD... )
   DEBUGLOG :      TBD....
```

---
4. Execution RPC (cli command)
``` 
< request command >

JSON:  {"method":<command name>, "params":[<parameters>]}

   {"method":"getinfo"}
   {"method":"getaddressbalances", "params":["HQEjzWAwZ463QSpxfxU26yYHQR3vAHpak3"]}
```
```
< response >

JSON: {"method":<command name>, "result":<result object>}

   {"method":"getinfo","result":{"version":"1.08.0","protocolversion":20000,"chainname":"hdac",.....}}
```

---
5. Node js Example ( client.js )
```
var port =  1119;

var WebSocket = require("ws");
var ws = new WebSocket("ws://192.168.70.12:" + port);

ws.onopen = function(event) {

  ws.send(JSON.stringify({"user":"hdacrpc","pass":"GpdLqLp5129c91PcNrMTjA7h5yJTwSAHox7JYgBtA8Ke"}));
  ws.send(JSON.stringify({"event":["BLOCK:1","TX:1"]}));
  //ws.send(JSON.stringify({"method":"getinfo"}));

}

ws.onmessage = function(event){
    var rcvmsg = event.data;
    var result = JSON.parse(rcvmsg);

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
```

