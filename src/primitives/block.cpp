// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Gdrcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"

#include "hash.h"
#include "crypto/hashblock.h" // Gdrcoin: Trappist
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "crypto/common.h"

uint256 CBlockHeader::GetHash() const
{
    return SerializeHash(*this);
}

// Gdrcoin: Trappist
uint256 CBlockHeader::GetPowHash() const
{
    return HashTrappist10(BEGIN(nVersion), END(nNonce), GetBlockTime()); // Gdrcoin: Trappist
}

std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
