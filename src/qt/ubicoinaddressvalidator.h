// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UBICOIN_QT_UBICOINADDRESSVALIDATOR_H
#define UBICOIN_QT_UBICOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class UbicoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UbicoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Ubicoin address widget validator, checks for a valid ubicoin address.
 */
class UbicoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UbicoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // UBICOIN_QT_UBICOINADDRESSVALIDATOR_H
