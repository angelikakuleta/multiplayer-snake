#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <contract.h>

class MessageParser : public QObject
{
    Q_OBJECT
public:
    explicit MessageParser(QObject *parent = nullptr);

    /**
     * @brief Extracts from a message the values corresponding to a specified names
     * @param message message to parse
     * @param [out] cmd command
     * @param [out] params parameters
     * @return true if message was parsed successfully, false otherwise
     */
    bool parseMessage(const QByteArray message, Contract::ServerCmd &cmd, QList<QByteArray> &params);

    /**
     * @brief Builds a message based on the passed command and parameter
     * @param cmd command
     * @param clientId client ID
     * @param params parameters
     * @return prepared message
     */
    QByteArray buildMessage(const Contract::ClientCmd cmd, const qint16 clientId,
                            const std::optional<QList<QByteArray>> &params);
};

#endif // MESSAGEPARSER_H
