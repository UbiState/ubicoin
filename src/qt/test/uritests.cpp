// Copyright (c) 2009-2020 The Bitcoin Core developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/test/uritests.h>

#include <qt/guiutil.h>
#include <qt/walletmodel.h>

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("ubicoin:SbsFGHLbdwkUwkxcT7ywnDz6FjNhYT8aBE?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
