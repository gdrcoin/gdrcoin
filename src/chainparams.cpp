// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Gdrcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Ottokar zu den drei Schlüsseln."; // Gdrcoin: Ottokar zu den drei Schlüsseln.
    const CScript genesisOutputScript = CScript() << ParseHex("047531e2974414503c9f5f3af84dacec9d073d265087ac6329e2224d0e0430cdc1bc3330ff9616d9117e13e50bdbafa574e97f917fee964afe65a3a6c2759b4077") << OP_CHECKSIG; // Gdrcoin: 047531e2974414503c9f5f3af84dacec9d073d265087ac6329e2224d0e0430cdc1bc3330ff9616d9117e13e50bdbafa574e97f917fee964afe65a3a6c2759b4077
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000; // Gdrcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 1;                  // Gdrcoin: 1
        consensus.BIP34Hash = uint256S("0x790cfc5472ee8a7030270ecbb5ce9c2bcdffe26f0ff4cab25538517703daec75"); // Gdrcoin: 0x790cfc5472ee8a7030270ecbb5ce9c2bcdffe26f0ff4cab25538517703daec75
        consensus.BIP65Height = 3; // Gdrcoin: 3
        consensus.BIP66Height = 2; // Gdrcoin: 2
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Gdrcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Gdrcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Gdrcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // Gdrcoin: 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // Gdrcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // Gdrcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // Gdrcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // Gdrcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // Gdrcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Gdrcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3"); // Gdrcoin: 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3 at height 0

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xd9; // Gdrcoin: 0xd9
        pchMessageStart[1] = 0xb4; // Gdrcoin: 0xb4
        pchMessageStart[2] = 0xbe; // Gdrcoin: 0xbe
        pchMessageStart[3] = 0xfe; // Gdrcoin: 0xfe
        nDefaultPort = 1989; // Gdrcoin: 1989
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN); // Gdrcoin: 1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")); // Gdrcoin: 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
        assert(genesis.hashMerkleRoot == uint256S("0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e")); // Gdrcoin: 0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("dnsseed1.gdrcoin.org", true); // Gdrcoin: dnsseed1.gdrcoin.org
        vSeeds.emplace_back("dnsseed2.gdrcoin.org", false);// Gdrcoin: dnsseed2.gdrcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50); // Gdrcoin: 50 (M)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5); // Gdrcoin: 5
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,178); // Gdrcoin: 178
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // Gdrcoin: 0x04, 0x88, 0xB2, 0x1E (xpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // Gdrcoin: 0x04, 0x88, 0xAD, 0xE4 (xpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")}, // Gdrcoin: 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3 (height 0).    // Gdrcoin: 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
            1514764799, // * UNIX timestamp of last known number of transactions                                  // Gdrcoin: 1514764799
                     1, // * total number of transactions between genesis and that timestamp                      // Gdrcoin: 1
                        //   (the tx=... number in the SetBestChain debug.log lines)
                     1  // * estimated number of transactions per second after that timestamp                     // Gdrcoin: 1
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000; // Gdrcoin: 210000 is a dummy variable here
        consensus.BIP34Height = 0; // Gdrcoin: 0
        consensus.BIP34Hash = uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3"); // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
        consensus.BIP65Height = 999999; // Gdrcoin TODO: Update
        consensus.BIP66Height = 888888; // Gdrcoin TODO: Update
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Gdrcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Gdrcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Gdrcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // Gdrcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // Gdrcoin: nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1498713060; // Gdrcoin: Thursday, 29. June 2017 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1530249060; // Gdrcoin: Friday, 29. June 2018 05:11:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530249060; // Gdrcoin: Friday, 29. June 2018 05:11:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1561785060; // Gdrcoin: Saturday, 29. June 2019 05:11:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Gdrcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3"); // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3

        pchMessageStart[0] = 0x11; // Gdrcoin: 0x11
        pchMessageStart[1] = 0x0b; // Gdrcoin: 0x0b
        pchMessageStart[2] = 0x09; // Gdrcoin: 0x09
        pchMessageStart[3] = 0x05; // Gdrcoin: 0x05
        nDefaultPort = 11989; // Gdrcoin: 11989
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN); // Gdrcoin TODO: Update, for now 1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")); // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
        assert(genesis.hashMerkleRoot == uint256S("0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e")); // Gdrcoin TODO: Update, for now 0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("testnet-dnsseed1.gdrcoin.org", true); // Gdrcoin: testnet-dnsseed1.gdrcoin.org
        vSeeds.emplace_back("testnet-dnsseed2.gdrcoin.org", false);// Gdrcoin: testnet-dnsseed2.gdrcoin.org

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // Gdrcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // Gdrcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // Gdrcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // Gdrcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // Gdrcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")}, // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
            }
        };

        chainTxData = ChainTxData{
            // Gdrcoin TODO: Update, for now data as of block 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3 (height 0)
            1514764799,
            1,
            1
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150; // Gdrcoin: 150 is a dummy variable here
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // Gdrcoin TODO: Update, for now BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // Gdrcoin TODO: Update, for now BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // Gdrcoin: 0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
        consensus.nPowTargetTimespan = 120960; // Gdrcoin: (14 * 24 * 60 * 60)/10 = 1/10 of two weeks
        consensus.nPowTargetSpacing = 60; // Gdrcoin: one minute
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // Gdrcoin: 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Gdrcoin: Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000"); // Gdrcoin: 0x0000000000000000000000000000000000000000000000000000000000000000

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3"); // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3 at height 0

        pchMessageStart[0] = 0xbf; // Gdrcoin: 0xbf
        pchMessageStart[1] = 0xfa; // Gdrcoin: 0xfa
        pchMessageStart[2] = 0xb5; // Gdrcoin: 0xb5
        pchMessageStart[3] = 0x05; // Gdrcoin: 0x05
        nDefaultPort = 21989; // Gdrcoin: 21989
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN); // Gdrcoin TODO: Update, for now 1514764799, 1812464, 0x1e0ffff0, 1, 50 * COIN
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")); // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
        assert(genesis.hashMerkleRoot == uint256S("0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e")); // Gdrcoin TODO: Update, for now 0x8100c05284c21d44d3090d43b09153319c1c89286171d28ceae4fcc4fbc47f2e

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
                {0, uint256S("0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3")}, // Gdrcoin TODO: Update, for now 0x887d61dc1f6c0b62008e37f25df630d70919e706ee414c0f06227a2eaebf32f3
            }
        };

        chainTxData = ChainTxData{
            1514764799, // Gdrcoin TODO: Update, for now 1514764799
            1, // Gdrcoin TODO: Update, for now 1
            1 // Gdrcoin TODO: Update, for now 1
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // Gdrcoin: 111 (m or n)
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // Gdrcoin: 196
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // Gdrcoin: 239
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // Gdrcoin: 0x04, 0x35, 0x87, 0xCF (tpub)
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // Gdrcoin: 0x04, 0x35, 0x83, 0x94 (tpriv)
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
