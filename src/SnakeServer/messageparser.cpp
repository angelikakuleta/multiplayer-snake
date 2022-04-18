#include "messageparser.h"
#include <stdexcept>
#include <QDebug>

MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{
}

bool MessageParser::parseMessage(const QByteArray message, Contract::ClientCmd &cmd, qint16 &sender, QList<QByteArray> &params)
{
    QList<QByteArray> separated = message.split(Contract::breakChar());

    if (separated.length() < 2) return false;

    auto cmdCode = separated.first();
    separated.pop_front();

    bool isValid = false;
    auto c = &Contract::clientCmdCodes();
    for (auto mapIterator = c->begin(); mapIterator != c->end(); mapIterator++) {
        if (mapIterator->second == cmdCode) {
            cmd = mapIterator->first;
            isValid = true;
            break;
        }
    }
    if (!isValid) return false;

    sender = separated.first().toInt(&isValid);
    if (!isValid) return false;

    separated.pop_front();
    params = separated;

    return true;
}

QByteArray MessageParser::buildMessage(const Contract::ServerCmd cmd, const QList<QByteArray> &params)
{
    QByteArray message;
    message.append(Contract::serverCmdCodes().at(cmd));

    for (const auto &param : params) {
        message.append(Contract::breakChar())
                .append(param);
    }

    return message;
}

