// Copyright (c) 2017 Hdac Technology AG
// Hdac code distributed under the GPLv3 license, see COPYING file.

#include "rpc/rpcprotocol.h"
#include "ws_rpchandle.h"

#include "utils/util.h"

using namespace json_spirit;

static const rpcCommandType rpccommand[] =
{
    { "getinfo",                &getinfo },
    { "stop",                   &stop},
    { "pause",                  &pausecmd, },
    { "resume",                 &resumecmd },
    { "clearmempool",           &clearmempool },
    { "setlastblock",           &setlastblock },
    { "getblockchainparams",    &getblockchainparams }, 
    { "getruntimeparams",       &getruntimeparams }, 
    { "setruntimeparam",        &setruntimeparam }, 

    { "getnetworkinfo",         &getnetworkinfo },
    { "addnode",                &addnode },
    { "getaddednodeinfo",       &getaddednodeinfo },
    { "getconnectioncount",     &getconnectioncount },
    { "getnettotals",           &getnettotals },
    { "getpeerinfo",            &getpeerinfo },
    { "getchainblockheight",    &getchainblockheight },

    { "getblockchaininfo",      &getblockchaininfo },
    { "getbestblockhash",       &getbestblockhash },
    { "getblockcount",          &getblockcount },
    { "getblock",               &getblock },
    { "getblockhash",           &getblockhash },
    { "getchaintips",           &getchaintips },
    { "getdifficulty",          &getdifficulty },
    { "getmempoolinfo",         &getmempoolinfo },
    { "getrawmempool",          &getrawmempool },
    { "getorphantx",            &getorphantx },
    { "gettxout",               &gettxout },
    { "gettxoutsetinfo",        &gettxoutsetinfo },
    { "verifychain",            &verifychain },
    { "invalidateblock",        &invalidateblock},
    { "reconsiderblock",        &reconsiderblock },
    { "listassets",             &listassets },
    { "listpermissions",        &listpermissions },
    { "liststreams",            &liststreams },
    { "listupgrades",           &listupgrades },
    { "listblocks",             &listblocks },
    
    { "getblocktemplate",       &getblocktemplate },
    { "getmininginfo",          &getmininginfo },
    { "getnetworkhashps",       &getnetworkhashps },
    { "prioritisetransaction",  &prioritisetransaction },
    { "submitblock",            &submitblock },
    { "getblockwindowsize",     &getblockwindowsize },

    { "getgenerate",            &getgenerate },
    { "gethashespersec",        &gethashespersec },
    { "setgenerate",            &setgenerate },

    { "appendrawtransaction",   &appendrawtransaction },
    { "createrawtransaction",   &createrawtransaction },
    { "decoderawtransaction",   &decoderawtransaction },
    { "decodescript",           &decodescript },
    { "getrawtransaction",      &getrawtransaction },
    { "sendrawtransaction",     &sendrawtransaction },
    { "signrawtransaction",     &signrawtransaction },
    { "appendrawchange",        &appendrawchange },
    { "appendrawmetadata",      &appendrawmetadata },
    { "appendrawdata",          &appendrawmetadata },

    { "createkeypairs",         &createkeypairs },
    { "createmultisig",         &createmultisig },
    { "validateaddress",        &validateaddress },
    { "verifymessage",          &verifymessage },
    { "estimatefee",            &estimatefee },
    { "estimatepriority",       &estimatepriority },

    { "invalidateblock",        &invalidateblock },
    { "reconsiderblock",        &reconsiderblock },
    { "setmocktime",            &setmocktime },

    { "addmultisigaddress",     &addmultisigaddress },
    { "backupwallet",           &backupwallet },
    { "dumpprivkey",            &dumpprivkey },
    { "dumpwallet",             &dumpwallet },
    { "encryptwallet",          &encryptwallet },
    { "getaccountaddress",      &getaccountaddress },
    { "getaccount",             &getaccount },
    { "getaddressesbyaccount",  &getaddressesbyaccount },
    { "getbalance",             &getbalance },
    { "getnewaddress",          &getnewaddress },
    { "getrawchangeaddress",    &getrawchangeaddress },
    { "getreceivedbyaccount",   &getreceivedbyaccount },
    { "getreceivedbyaddress",   &getreceivedbyaddress },
    { "gettransaction",         &gettransaction },
    { "getunconfirmedbalance",  &getunconfirmedbalance },
    { "getwalletinfo",          &getwalletinfo },
    { "importprivkey",          &importprivkey },
    { "importwallet",           &importwallet },
    { "importaddress",          &importaddress },
    { "keypoolrefill",          &keypoolrefill },
    { "listaccounts",           &listaccounts },
    { "listaddressgroupings",   &listaddressgroupings },
    { "listlockunspent",        &listlockunspent },
    { "listreceivedbyaccount",  &listreceivedbyaccount },
    { "listreceivedbyaddress",  &listreceivedbyaddress },
    { "listsinceblock",         &listsinceblock },
    { "listtransactions",       &listtransactions },
    { "listunspent",            &listunspent },
    { "lockunspent",            &lockunspent },
    { "move",                   &movecmd },
    { "sendfrom",               &sendfrom },
    { "sendfromaccount",        &sendfrom },
    { "sendmany",               &sendmany },
    { "sendtoaddress",          &sendtoaddress },
    { "send",                   &sendtoaddress },
    { "getaddresses",           &getaddresses },
    { "combineunspent",         &combineunspent },
    { "grant",                  &grantcmd },
    { "revoke",                 &revokecmd },
    { "issue",                  &issuecmd },
    { "issuemore",              &issuemorecmd },
    { "getassetbalances",       &getassetbalances },
    { "gettotalbalances",       &gettotalbalances },
    { "sendassettoaddress",     &sendassettoaddress },
    { "sendasset",              &sendassettoaddress },
    { "preparelockunspent",     &preparelockunspent },
    { "createrawexchange",      &createrawexchange },
    { "appendrawexchange",      &appendrawexchange },
    { "completerawexchange",    &completerawexchange },
    { "decoderawexchange",      &decoderawexchange },
    
    { "grantfrom",              &grantfromcmd },
    { "approvefrom",            &approvefrom },
    { "revokefrom",             &revokefromcmd },
    { "issuefrom",              &issuefromcmd },
    { "issuemorefrom",          &issuemorefromcmd },
    { "preparelockunspentfrom", &preparelockunspentfrom },
    { "sendassetfrom",          &sendassetfrom },
    { "sendfromaddress",        &sendfromaddress },
    { "sendfrom",               &sendfromaddress },
    { "getmultibalances",       &getmultibalances },
    { "getaddressbalances",     &getaddressbalances },
    { "disablerawtransaction",  &disablerawtransaction },
    { "sendwithmetadata",       &sendwithmetadata },
    { "sendwithdata",           &sendwithmetadata },
    { "sendwithmetadatafrom",   &sendwithmetadatafrom },
    { "sendwithdatafrom",       &sendwithmetadatafrom },
    { "grantwithmetadata",      &grantwithmetadata },
    { "grantwithdata",          &grantwithmetadata },
    { "grantwithmetadatafrom",  &grantwithmetadatafrom },
    { "grantwithdatafrom",      &grantwithmetadatafrom },
    { "createrawsendfrom",      &createrawsendfrom },
    
    { "listaddresses",          &listaddresses },
    { "listwallettransactions", &listwallettransactions },
    { "listaddresstransactions",&listaddresstransactions },
    { "getwallettransaction",   &getwallettransaction },
    { "getaddresstransaction",  &getaddresstransaction },
    { "resendwallettransactions",&resendwallettransactions },
    
    { "create",                 &createcmd },
    { "createfrom",             &createfromcmd },
    { "publish",                &publish },
    { "publishfrom",            &publishfrom },
    { "subscribe",              &subscribe },
    { "unsubscribe",            &unsubscribe },
    { "listassettransactions",  &listassettransactions },
    { "getassettransaction",    &getassettransaction },
    { "getstreamitem",          &getstreamitem },
    { "liststreamitems",        &liststreamitems },
    { "liststreamkeyitems",     &liststreamkeyitems },
    { "liststreampublisheritems",&liststreampublisheritems },
    { "liststreamkeys",         &liststreamkeys },
    { "liststreampublishers",   &liststreampublishers },
    { "gettxoutdata",           &gettxoutdata },
    { "liststreamblockitems",   &liststreamblockitems },
    
    { "setaccount",             &setaccount },
    { "settxfee",               &settxfee },
    { "signmessage",            &signmessage },
    { "walletlock",             &walletlock },
    { "walletpassphrasechange", &walletpassphrasechange },
    { "walletpassphrase",       &walletpassphrase },
};


void CWsRPCTable::initTable()
{
    unsigned int vcidx;
    for (unsigned int i = 0; i < sizeof(rpccommand)/sizeof(rpccommand[0]); i++)
    {
        const rpcCommandType *cmdptr;

        cmdptr = &rpccommand[i];
        mapCommands[cmdptr->name] = cmdptr;
    }
}

bool CWsRPCTable::JsonParse(const json_spirit::Value& value, json_spirit::Object& error)
{
    // Parse request
    if (value.type() != obj_type)
    {
        error = JSONRPCError(RPC_INVALID_REQUEST, "Invalid Request object");
        return false;
    }
        
    const Object& vObject = value.get_obj();

    // Parse method
    Value method = find_value(vObject, "method");
    if (method.type() == null_type)
    {
        error = JSONRPCError(RPC_INVALID_REQUEST, "Missing method");
        return false;
    }
    if (method.type() != str_type)
    {
        error = JSONRPCError(RPC_INVALID_REQUEST, "Method must be a string");
        return false;
    }

    strMethod = method.get_str();
        
    // Parse params
    Value params = find_value(vObject, "params");
    if (params.type() == array_type)
        mParams = params.get_array();
    else if (params.type() == null_type)
        mParams = Array();
    else
    {
        error = JSONRPCError(RPC_INVALID_REQUEST, "Params must be an array");
        return false;
    }

    return true;
}

json_spirit::Value CWsRPCTable::execute()
{
    Value result;
    const rpcCommandType* cmdptr;

    std::map<std::string, const rpcCommandType*>::iterator it = mapCommands.find(strMethod);
    if (it == mapCommands.end())
    {
        return JSONRPCError(RPC_METHOD_NOT_FOUND, "Method not found");
    }

    cmdptr = it->second;
   
    try
    {
        result = cmdptr->func(mParams, false);

    }
    catch (json_spirit::Object obj)
    {
        return obj;
    }  
    catch (...)
    {
        std::string msg = "exception thrown in command handling";
        return JSONRPCError(RPC_MISC_ERROR, msg);
    }   

    return result;
}

