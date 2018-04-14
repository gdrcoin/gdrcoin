// Copyright (c) 2011-2014 The Gdrcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GDRCOIN_QT_GDRCOINADDRESSVALIDATOR_H
#define GDRCOIN_QT_GDRCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class GdrcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GdrcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Gdrcoin address widget validator, checks for a valid gdrcoin address.
 */
class GdrcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GdrcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // GDRCOIN_QT_GDRCOINADDRESSVALIDATOR_H
