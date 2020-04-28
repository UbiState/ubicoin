// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>

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
    const char* pszTimestamp = "Ubitcoin From Community For Community 28/April/2020";
    const CScript genesisOutputScript = CScript() << ParseHex("04644a8e2f8e98d24a63069231c42a58bb914b179e997eb19234530db5badc9868d56d1a91836de36da7d62d1d00c914444c9afb0130bbbda030a0ef711b0d3aa1") << OP_CHECKSIG;
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
        consensus.nSubsidyHalvingInterval = 420000;
        consensus.BIP16Height = 0; // 87afb798a3ad9378fcd56123c81fb31cfd9a8df4719b9774d71730c16315a092 - October 1, 2012
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // bab3041e8977e0dc3eeff63fe707b92bde1dd449d8efafb248c27c8264cc311a
        consensus.BIP66Height = 0; // 7aceee012833fa8952f8835d8b1b3ae233cd6ab08fdb27a771d2bd7bdc491894
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); 
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 6048; // 75% of 8064
        consensus.nMinerConfirmationWindow = 8064; // nPowTargetTimespan / nPowTargetSpacing * 4
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1485561600; // January 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1517356801; // January 31st, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000001488d32719b8eb30150");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa601455787cb65ffc325dda4751a99cf01d1567799ec4b04f45bb05f9ef0cbde"); //1503191

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x6d;
        pchMessageStart[1] = 0x3b;
        pchMessageStart[2] = 0x2e;
        pchMessageStart[3] = 0x42;
        nDefaultPort = 9777;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1588084115, 410514, 0x1e0ffff0, 1, 25 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x1091a551f6813084364034c779c2589c7415cb9fda991e5feb565515c9642d87"));
        assert(genesis.hashMerkleRoot == uint256S("0x77419dc53a4b55b66f3caea691e617c352d6c70eb73e876029570b34d20ae4f0"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        //vSeeds.emplace_back("explorer.rtid-platform.web.id");
        //vSeeds.emplace_back("seed.rtid-platform.web.id");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,69);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "ubit";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 a601455787cb65ffc325dda4751a99cf01d1567799ec4b04f45bb05f9ef0cbde
            /* nTime    */ 0,// 1538637641,
            /* nTxCount */ 0,// 28086163,
            /* dTxRate  */ 0,// 0.334
        };

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 420000;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on testnet
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.BIP66Height = 0; // 8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000203cafcb7de493");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x438b7e1c86f58b4e62e8cf2d0f9f256e3dddaebc5d1cc568e633a38e0db6c025"); //787085

        pchMessageStart[0] = 0xe7;
        pchMessageStart[1] = 0x2c;
        pchMessageStart[2] = 0x9c;
        pchMessageStart[3] = 0x75;
        nDefaultPort = 19777;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1588084268, 880185, 0x1e0ffff0, 1, 25 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xc060b370ba33ebf48368c8e1d1aabc58656eeb75c9662c67975c121b8983a372"));
        assert(genesis.hashMerkleRoot == uint256S("0x77419dc53a4b55b66f3caea691e617c352d6c70eb73e876029570b34d20ae4f0"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        //vSeeds.emplace_back("seedtest1.rtid-platform.web.id");
        //vSeeds.emplace_back("seedtest2.rtid-platform.web.id");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,130);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tbit";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            // Data from rpc: getchaintxstats 4096 438b7e1c86f58b4e62e8cf2d0f9f256e3dddaebc5d1cc568e633a38e0db6c025
            /* nTime    */ 0,//1538637952,
            /* nTxCount */ 0,//1845705,
            /* dTxRate  */ 0,//1.907
        };

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x81;
        pchMessageStart[1] = 0xd1;
        pchMessageStart[2] = 0x59;
        pchMessageStart[3] = 0x4b;
        nDefaultPort = 19888;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1588084711, 627771, 0x1e0ffff0, 1, 25 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0899b3a1c5819adac8c2cb9fc3a442845ffc281bd2962ebc41de93bb79ae0473"));
        assert(genesis.hashMerkleRoot == uint256S("0x77419dc53a4b55b66f3caea691e617c352d6c70eb73e876029570b34d20ae4f0"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; 

        checkpointData = {
            {
                {0, uint256S("0899b3a1c5819adac8c2cb9fc3a442845ffc281bd2962ebc41de93bb79ae0473")},
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1,58);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rbit";

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
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
