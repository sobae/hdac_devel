// Copyright (c) 2017 Hdac Technology AG
// Distributed under the MIT/X11 software license, see the accompanying
// Hdac code distributed under the GPLv3 license, see COPYING file.

#ifndef __WEBSOCKET_H
#define __WEBSOCKET_H

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "primitives/transaction.h"
#include "primitives/block.h"
#include "chain/chain.h"

#include "ws_rpchandle.h"

using namespace std;
using websocketpp::connection_hdl;

//define connection data
struct ConnectionData
{
    set<string> setSubList;
    bool isAllowed;
};

//configure websocketpp
struct socketConfig : public websocketpp::config::asio {
    //defauts
    typedef websocketpp::config::asio core;

    typedef core::concurrency_type concurrency_type;
    typedef core::request_type request_type;
    typedef core::response_type response_type;
    typedef core::message_type message_type;
    typedef core::con_msg_manager_type con_msg_manager_type;
    typedef core::endpoint_msg_manager_type endpoint_msg_manager_type;
    typedef core::alog_type alog_type;
    typedef core::elog_type elog_type;
    typedef core::rng_type rng_type;
    typedef core::transport_type transport_type;
    typedef core::endpoint_base endpoint_base;

    //set connection data
    typedef ConnectionData connection_base;
};

typedef websocketpp::server<socketConfig> cServer;
typedef cServer::connection_ptr connection_ptr;
typedef cServer::timer_ptr timer_ptr;
typedef websocketpp::lib::error_code error_code;

class cWebsocket
{
public:
    
    cWebsocket(uint16_t port)
    {
        nPort = port;
        //m_docroot = "$HOME";
        //m_count = 0;
    }

    cWebsocket(uint16_t port, string docroot)
    {
        nPort = port;
        //m_docroot = docroot;
        //m_count = 0;
        
    }

    void run();
    void stop();

    void broadcast(string event, string msg);
    
    //event handlers
    void on_message(connection_hdl pHdl, cServer::message_ptr pMsg);
    void on_http(connection_hdl pHdl);
    
    void on_open(connection_hdl pHdl);
    void on_close(connection_hdl pHdl);

    void set_timer();
    void on_timer(error_code const & ec);

    void wsBroadcastBlock(const CBlock& block, const CBlockIndex *pblockindex);
    void wsBroadcastTx(const CTransaction& tx, int64_t time);
    void wsBroadcastStatus(string strStatus);
    void wsBroadcastDebugLog(string strlog);
    void wsBroadcastMempool();
    
    void wsGetNodeInfo(connection_hdl pHdl);
    
private:
    set<connection_hdl> setConnections_;
    cServer wserver;

    timer_ptr m_timer;

    //string m_docroot;
    //uint64_t m_count;
    
    uint16_t nPort;

    CWsRPCTable ctable;
};

void WebsocketServer(cWebsocket* wss);


#endif/* __WEBSOCKET_H */
