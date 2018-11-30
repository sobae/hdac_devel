// Copyright (c) 2017 Hdac Technology AG
// Hdac code distributed under the GPLv3 license, see COPYING file.

#ifndef WS_RPCHANDLE_H
#define WS_RPCHANDLE_H

#include <list>
#include <map>
#include <stdint.h>
#include <string>

#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_utils.h"
#include "json/json_spirit_writer_template.h"


extern json_spirit::Value stop(const json_spirit::Array& params, bool fHelp); 
extern json_spirit::Value getconnectioncount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getpeerinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getchainblockheight(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value ping(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value addnode(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaddednodeinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getnettotals(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value dumpprivkey(const json_spirit::Array& params, bool fHelp); 
extern json_spirit::Value importprivkey(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value importaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value dumpwallet(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value importwallet(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value getgenerate(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value setgenerate(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getnetworkhashps(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gethashespersec(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getmininginfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value prioritisetransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblocktemplate(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value submitblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value estimatefee(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value estimatepriority(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value getnewaddress(const json_spirit::Array& params, bool fHelp); 
extern json_spirit::Value getaccountaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getrawchangeaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value setaccount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaccount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaddressesbyaccount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendtoaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createkeypairs(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaddresses(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value combineunspent(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value grantcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value revokecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value issuecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value issuemorecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listassets(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listpermissions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getassetbalances(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gettotalbalances(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendassettoaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblockchainparams(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getruntimeparams(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value setruntimeparam(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value preparelockunspent(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createrawexchange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value appendrawexchange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value completerawexchange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value decoderawexchange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value appendrawmetadata(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value approvefrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value grantfromcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value revokefromcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value issuefromcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value issuemorefromcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendassetfrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value preparelockunspentfrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendfromaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createrawsendfrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getmultibalances(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaddressbalances(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value disablerawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendwithmetadata(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendwithmetadatafrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value grantwithmetadata(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value grantwithmetadatafrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listwallettransactions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listaddresstransactions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getwallettransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getaddresstransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value appendrawchange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value pausecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value resumecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value clearmempool(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value setlastblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value resendwallettransactions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listaddresses(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreams(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listupgrades(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createfromcmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value publish(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value publishfrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value subscribe(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value unsubscribe(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listassettransactions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getassettransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getstreamitem(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreamitems(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreamkeyitems(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreampublisheritems(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreamkeys(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreampublishers(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gettxoutdata(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listblocks(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value liststreamblockitems(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value signmessage(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value verifymessage(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getreceivedbyaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getreceivedbyaccount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getbalance(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getunconfirmedbalance(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value movecmd(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendfrom(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendmany(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value addmultisigaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createmultisig(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listreceivedbyaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listreceivedbyaccount(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listtransactions(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listaddressgroupings(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listaccounts(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listsinceblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gettransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value backupwallet(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value keypoolrefill(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value walletpassphrase(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value walletpassphrasechange(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value walletlock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value encryptwallet(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value validateaddress(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getwalletinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblockchaininfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getnetworkinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value setmocktime(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value getrawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listunspent(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value lockunspent(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value listlockunspent(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value appendrawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value createrawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value decoderawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value decodescript(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value signrawtransaction(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value sendrawtransaction(const json_spirit::Array& params, bool fHelp);

extern json_spirit::Value getblockcount(const json_spirit::Array& params, bool fHelp); 
extern json_spirit::Value getbestblockhash(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getdifficulty(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value settxfee(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getmempoolinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getrawmempool(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getorphantx(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblockhash(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gettxoutsetinfo(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value gettxout(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value verifychain(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getchaintips(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value invalidateblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value reconsiderblock(const json_spirit::Array& params, bool fHelp);
extern json_spirit::Value getblockwindowsize(const json_spirit::Array& params, bool fHelp);


typedef json_spirit::Value(*rpcFuncType)(const json_spirit::Array& params, bool fHelp);


typedef struct
{
    std::string name;
    rpcFuncType func;
}rpcCommandType;


class CWsRPCTable
{
    std::string strMethod;
    json_spirit::Array mParams;

private:
    std::map<std::string, const rpcCommandType*> mapCommands;

public:
    CWsRPCTable()
    {
        initTable();
    }

    void initTable();
    json_spirit::Value execute();
    bool JsonParse(const json_spirit::Value& value, json_spirit::Object& error);
};

#endif/* WS_RPCHANDLE_H */
