#include "messageparser.h"

const char BREAK_CHAR = '#';
const char* CMD_CLIENET_ID = "CID";
const char* CMD_START_GAME = "SGM";

MessageParser::MessageParser(QObject *parent)
    : QObject{parent}
{
    m_cmdCodes[Command::ClientRegistered] = (char *)CMD_CLIENET_ID;
    m_cmdCodes[Command::StartGame] = (char *)CMD_START_GAME;
}

bool MessageParser::parseMessage(const QByteArray message, Command &cmd, QList<QByteArray> &params)
{
    QList<QByteArray> separated = message.split(BREAK_CHAR);

    if (separated.length() < 1) return false;

    auto cmdCode = separated.first();
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

    params = separated;

    return true;
}

QByteArray MessageParser::buildMessage(const Command cmd,
                                       const qint16 clientId, const std::optional<QList<QByteArray>> &params)
{
    QByteArray message;
    message.append(m_cmdCodes[cmd])
        .append(BREAK_CHAR)
        .append(QByteArray::number(clientId));

    if (params.has_value()) {
        for (const auto &param : *params) {
            message.append(BREAK_CHAR)
                    .append(param);
        }
    }

    return message;
}
