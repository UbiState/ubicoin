// Copyright (c) 2020 Isaac
// Copyright (c) 2020 The Ubicoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UBICOIN_SUPPORT_CLEANSE_H
#define UBICOIN_SUPPORT_CLEANSE_H

#include <stdlib.h>

// Attempt to overwrite data in the specified memory span.
void memory_cleanse(void *ptr, size_t len);

#endif // UBICOIN_SUPPORT_CLEANSE_H
