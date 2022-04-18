#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>
#include <contract.h>

/**
 * @brief The message parser
 */
class MessageParser : public QObject
{
    Q_OBJECT
public:
    explicit MessageParser(QObject *parent = nullptr);

    /**
     * @brief Extracts from a message the values corresponding to a specified names
     * @param message message to parse
     * @param [out] cmd command
     * @param [out] sender client ID
     * @param [out] params parameters
     * @return true if message was parsed successfully, false otherwise
     */
    bool parseMessage(const QByteArray message, Contract::ClientCmd &cmd, qint16 &sender, QList<QByteArray> &params);

    /**
     * @brief Builds a message based on the passed command and parameters
     * @param cmd command
     * @param params parameters
     * @return prepared message
     */
    QByteArray buildMessage(const Contract::ServerCmd, const QList<QByteArray> &params);
};

#endif // MESSAGEPARSER_H
