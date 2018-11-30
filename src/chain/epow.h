// Copyright (c) 2017 Hdac Technology AG
// Hdac code distributed under the GPLv3 license, see COPYING file.
/*============================================================================================
   History
   
   2018/01/00	renamed the included file
============================================================================================*/

#ifndef HDAC_EPOW_H
#define HDAC_EPOW_H

#include "hdac/hdac.h"
#include "cust/custhdac.h"

#include <stdint.h>


class CNode;
class CBlock;
class CPubKey;

/** Verify the block window policy against the miner of the received block */
bool VerifyBlockWindow(const CBlock& block, CNode* pfrom);
/** Check the size of block window with an address of a miner */
bool CheckBlockWindow(std::string strMiner);
/** Check the size of block window with a public key of a miner */
bool CheckBlockWindow(CPubKey pkey);
/** Check whether the current state is a mining blackout or not */
bool IsMiningBlackout();

/** Obtain the node factor by inquiring to a specific block depth */
int GetNodeFactor(int depth);
int GetNodeFactor(int depth, int nStartDepth);
/** Get the current block window size */
int GetBlockWindowSize();
int GetBlockWindowSize(int nStartDepth);
/** Find the mining depth of a specific miner */
int GetMiningDepth(const std::string strAddr);
/** Get information about the current block window size, node factor and so on */
void GetCurrentBlockWindowInfo(int& wz, int& nf, int& bh);
/** Get the recent mining continuity of a specific miner */
int GetMiningContinuity(const std::string strAddr);

#ifdef FEATURE_HPAY_EPOW_VER_2
int CalculateWindowSize(int nDepth=120);
int GetMiningContinuity(const std::string strAddr, int Depth);
int GetMiningCount(int depth, const std::string strAddr, int* time=NULL, bool verbose=false);
#endif/* FEATURE_HPAY_EPOW_VER_2 */

/** Get address from public key */
std::string GetMinerAddress(CPubKey pkey);
/** Extract coinbase address from block */
std::string GetCoinbaseAddress(const CBlock& block);

#ifdef FEATURE_HPAY_EPOW_MINER_ADDRESS
std::string GetBlockMinerAddress(const CBlock &block);
#endif/* FEATURE_HPAY_EPOW_MINER_ADDRESS */

/** Query the active blockchain and summarize the block information */
void PrintRecentBlockInfo(int depth=480);
void PrintBlockInfo(CNode* pfrom, CBlock* pblock);


//bool IsAganistEPow(CNode* pfrom, CBlock* pblock);
bool CheckePoWRule(std::string strMinerAddress, int nStartDepth=0);

bool IsEnabledEpowV2(int nheight);

extern bool	BLOCKWINDOW_TOUCHED;

#endif // HDAC_EPOW_H
