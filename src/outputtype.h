// Copyright (c) 2020 Isaac
// Copyright (c) 2020 The Ubicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UBICOIN_OUTPUTTYPE_H
#define UBICOIN_OUTPUTTYPE_H

#include <keystore.h>
#include <script/standard.h>

#include <string>
#include <vector>

enum class OutputType {
    LEGACY,
    P2SH_SEGWIT,
    BECH32,

    /**
     * Special output type for change outputs only. Automatically choose type
     * based on address type setting and the types other of non-change outputs
     * (see -changetype option documentation and implementation in
     * CWallet::TransactionChangeType for details).
     */
    CHANGE_AUTO,
};

bool ParseOutputType(const std::string& str, OutputType& output_type);
const std::string& FormatOutputType(OutputType type);

/**
 * Get a destination of the requested type (if possible) to the specified key.
 * The caller must make sure LearnRelatedScripts has been called beforehand.
 */
CTxDestination GetDestinationForKey(const CPubKey& key, OutputType);

/** Get all destinations (potentially) supported by the wallet for the given key. */
std::vector<CTxDestination> GetAllDestinationsForKey(const CPubKey& key);

/**
 * Get a destination of the requested type (if possible) to the specified script.
 * This function will automatically add the script (and any other
 * necessary scripts) to the keystore.
 */
CTxDestination AddAndGetDestinationForScript(CKeyStore& keystore, const CScript& script, OutputType);

#endif // UBICOIN_OUTPUTTYPE_H

