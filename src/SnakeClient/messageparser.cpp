#include "messageparser.h"

MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{
}

bool MessageParser::parseMessage(const QByteArray message, Contract::ServerCmd &cmd, QList<QByteArray> &params)
{
    QList<QByteArray> separated = message.split(Contract::breakChar());

    if (separated.length() < 1) return false;

    auto cmdCode = separated.first();
    separated.pop_front();

    bool isValid = false;
    auto c = &Contract::serverCmdCodes();
    for (auto mapIterator = c->begin(); mapIterator != c->end(); mapIterator++) {
        if (mapIterator->second == cmdCode) {
            cmd = mapIterator->first;
            isValid = true;
            break;
        }
    }
    if (!isValid) return false;

    params = separated;

    return true;
}

QByteArray MessageParser::buildMessage(const Contract::ClientCmd cmd,
                                       const qint16 clientId, const std::optional<QList<QByteArray>> &params)
{
    QByteArray message;
    message.append(Contract::clientCmdCodes().at(cmd))
        .append(Contract::breakChar())
        .append(QByteArray::number(clientId));

    if (params.has_value()) {
        for (const auto &param : *params) {
            message.append(Contract::breakChar())
                    .append(param);
        }
    }

    return message;
}
