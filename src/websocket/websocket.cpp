// Copyright (c) 2017 Hdac Technology AG
// Distributed under the MIT/X11 software license, see the accompanying
// Hdac code distributed under the GPLv3 license, see COPYING file.


#include "websocket.h"

#include <fstream>
#include <iostream>
#include "json/json_spirit.h"
#include "json/json_spirit_stream_reader.h"
#include "json/json_spirit_writer_template.h"

#include "utils/util.h"

using namespace json_spirit;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

extern void TxToJSON(const CTransaction& tx, const uint256 hashBlock, Object& entry);
extern Object blockToJSON(const CBlock& block, const CBlockIndex* blockindex, bool txDetails = false, int verbose_level = 1);
extern std::string EncodeHexTx(const CTransaction& tx);

extern Object getNodeinfo();
extern Array getmempoolStatus();

typedef enum
{
    BLOCK_LVL_0,
    BLOCK_LVL_1,
    BLOCK_LVL_2,

    TX_LVL_0,
    TX_LVL_1,

    MEMPOOL_INFO,

    STATUS,
    
    DEBUG_LOG,

    MAX_EVENT
}ws_event_type;

std::vector<rpcCommandType> rpcCommands;


std::string runshell(const std::string cmd)
{
    std::string result;
    
    if(cmd.size() < 1)
    {
        throw runtime_error("command not found\n");
    }

    FILE *fp;
    int status;
    char line[1000000];

    fp = popen(cmd.c_str(), "r");

    while (fgets(line, 100, fp) != NULL)
    {
        result += line;
    }
    status = pclose(fp);

    return result;
}

// start the websocket server
void cWebsocket::run()
{    
    try{
        
        // Disabled logging settings
        #if 1
		wserver.clear_access_channels(websocketpp::log::alevel::all);
		wserver.clear_error_channels (websocketpp::log::alevel::all);
		#endif
		
        wserver.init_asio();
        wserver.set_reuse_addr(true);
        
        //set event handlers
        wserver.set_open_handler(bind(&cWebsocket::on_open,this,_1));
        wserver.set_close_handler(bind(&cWebsocket::on_close,this,_1));
        wserver.set_message_handler(bind(&cWebsocket::on_message,this,_1,_2));
        wserver.set_http_handler(bind(&cWebsocket::on_http,this,_1));
        
        wserver.listen(nPort);
        wserver.start_accept();

        //set_timer();
        
        wserver.run();
        
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}

void cWebsocket::stop()
{
	error_code ec;
	wserver.stop_listening(ec);
	if (ec) {
		// Failed to stop listening. Log reason using ec.message().
		return;
	}

    // Stop the endpoint.
	wserver.stop();

}

void cWebsocket::broadcast(string event, string msg)
{        
    //for every open connection
    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) {
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
        if(pConnection->isAllowed)
            wserver.send(*it, msg, websocketpp::frame::opcode::text);
    }
}

void cWebsocket::on_message(connection_hdl pHdl, cServer::message_ptr pMsg)
{    
    connection_ptr pConnection = wserver.get_con_from_hdl(pHdl);
    
    //parse json
    do
    {
		mValue sMsg;
		mObject mapMsg;
        read_string(pMsg->get_payload(), sMsg);

        if(sMsg.is_null())
        {
            LogPrintf("--------------payload is not JSON \n");
            break;
        }
        
        mapMsg = sMsg.get_obj();

        std::string strRpcUser = mapArgs["-rpcuser"];
        std::string strRpcPass = mapArgs["-rpcpassword"];
        std::string strauth = "{\"user\": \"" + strRpcUser + "\", \"pass\": \""+strRpcPass+"\"}";
    
        
		mValue authMsg;
		mObject mapConfig;
        read_string(strauth, authMsg);
        mapConfig = authMsg.get_obj();
        
        if (!pConnection->isAllowed)
        {
            if(mapMsg.count("user") == 1 && mapMsg.count("pass") == 1 && mapMsg["user"] == mapConfig["user"] && mapMsg["pass"] == mapConfig["pass"])
            {
                pConnection->isAllowed = true;
                pConnection->setSubList.clear();
                
                string strConn = "{\"AUTH\":{\"status\":\"1\", \"reson\":\"Authentication successful\"}}";
                wserver.send(pConnection, strConn, websocketpp::frame::opcode::text);
            }
            else
            {
                string strError = "{\"AUTH\":{\"status\":\"0\", \"reson\":\"incorrect user or password attempt - <<Closed Socket>>\"}}";
                wserver.send(pConnection, strError, websocketpp::frame::opcode::text);
                
                //disconnect
                websocketpp::close::status::value code(websocketpp::close::status::normal);
                wserver.close(pConnection, code, "");
            }
        }
        else if(pConnection->isAllowed)
        {            
            if(mapMsg.count("shell") == 1)
            {
                std::string result = runshell(mapMsg["shell"].get_str());

                Object obj;
                obj.push_back(Pair("shell", mapMsg["shell"].get_str()));
                obj.push_back(Pair("result", result));
                string msg = write_string(Value(obj), false);
                wserver.send(pConnection, msg, websocketpp::frame::opcode::text);
                return;
            }

            if(mapMsg.count("event") > 0)
            {
                mArray mapEvents = mapMsg["event"].get_array();

                for (unsigned int i=0; i<mapEvents.size(); i++)
                {
                    pConnection->setSubList.insert(mapEvents[i].get_str());
                }
                return;
            }

            if(mapMsg.count("method") > 0)
            {
                Value value;
                read_string(pMsg->get_payload(), value);
                
                //LogPrintf("----------%s\n",pMsg->get_payload());
                
                Object fobject, err;
                Value result;

                fobject.push_back(Pair("method", mapMsg["method"].get_str()));
                if(ctable.JsonParse(value, err))
                {
                    result = ctable.execute();
                }
                else
                {
                    result = Value(err);
                }
                fobject.push_back(Pair("result", result));
                
                string msg = write_string(Value(fobject), false);
                wserver.send(pConnection, msg, websocketpp::frame::opcode::text);
            }
            
        
        }

    }while(0);
    
}

void cWebsocket::set_timer() 
{
   // compile error.. ???
   //m_timer = wserver.set_timer(1000, bind(&cWebsocket::on_timer, this,_1));
}

void cWebsocket::on_timer(error_code const & ec) 
{
    #if 0
    if (ec) {
        // there was an error, stop server
        wserver.get_alog().write(websocketpp::log::alevel::app,
                "Timer Error: "+ec.message());
        return;
    }
    
    std::stringstream val;
    val << "count is " << m_count++;
    
    // Broadcast count to all connections
    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) {
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
        //check if user is authenticated and listens to given event
        if(pConnection->isAllowed)
            wserver.send(*it, val.str(), websocketpp::frame::opcode::text);
    }

    
    set_timer();
    #endif
}

void cWebsocket::on_http(connection_hdl pHdl) 
{
    // Upgrade our connection handle to a full connection_ptr
    connection_ptr pConnection = wserver.get_con_from_hdl(pHdl);

  #if 1
	if (1) {
			// 404 error
			std::stringstream ss;
		
			ss << "<!doctype html><html><head>"
			   << "<title>Error 404 (Resource not found)</title><body>"
			   << "<h1>Error 404</h1>"
			   << "</body></head></html>";
		
			pConnection->set_body(ss.str());
			pConnection->set_status(websocketpp::http::status_code::not_found);
			return;
		}

  #else
    std::ifstream file;
    std::string filename = pConnection->get_resource();
    std::string response;

    wserver.get_alog().write(websocketpp::log::alevel::app,
        "http request1: "+filename);

    if (filename == "/") {
        filename = m_docroot+"index.html";
    } else {
        filename = m_docroot+filename.substr(1);
    }
    
    wserver.get_alog().write(websocketpp::log::alevel::app,
        "http request2: "+filename);

    file.open(filename.c_str(), std::ios::in);
    if (!file) {
        // 404 error
        std::stringstream ss;
    
        ss << "<!doctype html><html><head>"
           << "<title>Error 404 (Resource not found)</title><body>"
           << "<h1>Error 404</h1>"
           << "<p>The requested URL " << filename << " was not found on this server.</p>"
           << "</body></head></html>";
    
        pConnection->set_body(ss.str());
        pConnection->set_status(websocketpp::http::status_code::not_found);
        return;
    }

    file.seekg(0, std::ios::end);
    response.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    response.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

    pConnection->set_body(response);
    pConnection->set_status(websocketpp::http::status_code::ok);
  #endif    
}


void cWebsocket::on_open(connection_hdl pHdl)
{
    //inserts connection from connection set
    setConnections_.insert(pHdl);
    connection_ptr pConnection = wserver.get_con_from_hdl(pHdl);
    
    pConnection->isAllowed = false;

    wsGetNodeInfo(pHdl);
}

void cWebsocket::on_close(connection_hdl pHdl) {        
    //removes connection from connection set
    setConnections_.erase(pHdl);
}


void cWebsocket::wsBroadcastTx(const CTransaction& tx, int64_t time)
{
    Object pObject;
    ws_event_type evt = MAX_EVENT;

    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) 
    {
        evt = MAX_EVENT;
        pObject.clear();
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
				
        if(pConnection->isAllowed)
        {
            if(pConnection->setSubList.count("TX:0"))
            {
                evt = TX_LVL_0;
            }
            else if(pConnection->setSubList.count("TX:1"))
            {
                evt = TX_LVL_1;
            }

            if(evt >= TX_LVL_0 && evt <= TX_LVL_1)
            {
                Object obj;
                obj.clear();
                if (evt == TX_LVL_1) // detail info.
                {
                    TxToJSON(tx, uint256(0), obj);
                    obj.push_back(Pair("time", time));
                    obj.push_back(Pair("hex", EncodeHexTx(tx)));
                    pObject.push_back(Pair("TX", obj));
                }
                else // short info.
                {
                    obj.push_back(Pair("txid", tx.GetHash().ToString()));
                    obj.push_back(Pair("time", time));
                    pObject.push_back(Pair("TX", obj));
                }
                
                string msg = write_string(Value(pObject), false);
                wserver.send(*it, msg, websocketpp::frame::opcode::text);
            }
        }
    }
    
}

void cWebsocket::wsBroadcastBlock(const CBlock& block, const CBlockIndex *pblockindex)
{
    Object pObject;
    ws_event_type evt = MAX_EVENT;

    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) 
    {
        evt = MAX_EVENT;
        pObject.clear();
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
        
        if(pConnection->isAllowed)
        {
            if(pConnection->setSubList.count("BLOCK:0"))
            {
                evt = BLOCK_LVL_0;
            }
            else if(pConnection->setSubList.count("BLOCK:1"))
            {
                evt = BLOCK_LVL_1;
            }
            else if(pConnection->setSubList.count("BLOCK:2"))
            {
                evt = BLOCK_LVL_2;
            }

            if(evt <= BLOCK_LVL_2)
            {
                Object obj;
                obj.clear();
                if(evt == BLOCK_LVL_0)
                {
                    obj.push_back(Pair("height", pblockindex->nHeight));
                    obj.push_back(Pair("hash", block.GetHash().ToString()));
                    pObject.push_back(Pair("BLOCK", obj));
                }
                else
                {
                    obj = blockToJSON(block, 
                                      pblockindex, 
                                      (evt == BLOCK_LVL_2) ? true:false, 
                                      (evt == BLOCK_LVL_2) ? 4:1);

                    pObject.push_back(Pair("BLOCK", obj));
                }
                string msg = write_string(Value(pObject), false);
                wserver.send(*it, msg, websocketpp::frame::opcode::text);
            }
        }
    }
}

void cWebsocket::wsBroadcastMempool()
{
    Object pObject;
    ws_event_type evt = MAX_EVENT;

    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) 
    {
        evt = MAX_EVENT;
        pObject.clear();
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
				
        if(pConnection->isAllowed)
        {
            if(pConnection->setSubList.count("MEMPOOL"))
            {
                evt = MEMPOOL_INFO;
            }

            if(evt == MEMPOOL_INFO)
            {
                Object pObject;
                Array a;
                a = getmempoolStatus();
                pObject.push_back(Pair("MEMPOOL", a));

                string msg = write_string(Value(pObject), false);
                wserver.send(*it, msg, websocketpp::frame::opcode::text);
            }
        }
    }
    
}

void cWebsocket::wsBroadcastDebugLog(string strlog)
{
    Object pObject;
    ws_event_type evt = MAX_EVENT;

    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) 
    {
        evt = MAX_EVENT;
        pObject.clear();
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
        
        if(pConnection->isAllowed)
        {
            if(pConnection->setSubList.count("DEBUGLOG"))
            {
                evt = DEBUG_LOG;
            }
            
            if(evt == DEBUG_LOG)
            {
                pObject.push_back(Pair("DEBUGLOG", strlog));
                string msg = write_string(Value(pObject), false);
                wserver.send(*it, msg, websocketpp::frame::opcode::text);
            }
        }
    }
}

void cWebsocket::wsBroadcastStatus(string strStatus)
{
    Object pObject;
    ws_event_type evt = MAX_EVENT;

    for(set<connection_hdl>::iterator it = setConnections_.begin(); it != setConnections_.end(); ++it) 
    {
        evt = MAX_EVENT;
        pObject.clear();
        connection_ptr pConnection = wserver.get_con_from_hdl(*it);
        
        if(pConnection->isAllowed)
        {
            if(pConnection->setSubList.count("STATUS"))
            {
                evt = STATUS;
            }
            
            if(evt == STATUS)
            {
                pObject.push_back(Pair("STATUS", strStatus));
                string msg = write_string(Value(pObject), false);
                wserver.send(*it, msg, websocketpp::frame::opcode::text);
            }
        }
    }
}

void cWebsocket::wsGetNodeInfo(connection_hdl pHdl)
{
    Object pObject, subObject;

    subObject = getNodeinfo();
    pObject.push_back(Pair("INFO", subObject));
    
    string msg = write_string(Value(pObject), false);
    wserver.send(pHdl, msg, websocketpp::frame::opcode::text);
}

void WebsocketServer(cWebsocket* wss)
{
    wss->run();
}




