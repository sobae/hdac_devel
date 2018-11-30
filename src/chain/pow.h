// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Original code was distributed under the MIT/X11 software license.
// Copyright (c) 2014-2017 Coin Sciences Ltd
// MultiChain code distributed under the GPLv3 license, see COPYING file.

#ifndef BITCOIN_POW_H
#define BITCOIN_POW_H

#include <stdint.h>

class CBlockHeader;
class CBlockIndex;
class uint256;

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader *pblock);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, bool fNoErrorInLog = false);
//#ifdef FEATURE_HPAY_BLOCK_HASH_ALGORITHM
bool CheckProofOfWork(uint256 hash, unsigned int nBits, unsigned int nVersion, unsigned int nHeight, bool fNoErrorInLog = false);
//#endif/* FEATURE_HPAY_BLOCK_HASH_ALGORITHM */
uint256 GetBlockProof(const CBlockIndex& block);

#endif // BITCOIN_POW_H
