#include "messageparser.h"
#include <stdexcept>
#include <QDebug>

const char BREAK_CHAR = '#';
const char* CMD_CLIENET_ID = "CID";
const char* CMD_START_GAME = "SGM";

MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{
    m_cmdCodes[Command::ClientRegistered] = (char *)CMD_CLIENET_ID;
    m_cmdCodes[Command::StartGame] = (char *)CMD_START_GAME;
}

bool MessageParser::parseMessage(const QByteArray message, Command &cmd, qint16 &sender, QList<QByteArray> &params)
{
    QList<QByteArray> separated = message.split(BREAK_CHAR);

    if (separated.length() != 2) return false;

    auto cmdCode = separated.first().data();
    separated.pop_front();

    bool isValid = false;
    for (auto mapIterator = m_cmdCodes.begin(); mapIterator != m_cmdCodes.end(); mapIterator++) {
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

QByteArray MessageParser::buildMessage(const Command cmd, const QList<QByteArray> &params)
{
    QByteArray message;
    message.append(m_cmdCodes[cmd]);

    for (const auto &param : params) {
        message.append(BREAK_CHAR)
                .append(param);
    }

    return message;
}
