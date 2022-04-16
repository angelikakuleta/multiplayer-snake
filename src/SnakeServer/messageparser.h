#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <QObject>

enum Command {
    ClientRegistered,
    StartGame
};

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
    bool parseMessage(const QByteArray message, Command &cmd, qint16 &sender, QList<QByteArray> &params);

    /**
     * @brief Builds a message based on the passed command and parameters
     * @param cmd command
     * @param params parameters
     * @return prepared message
     */
    QByteArray buildMessage(const Command cmd, const QList<QByteArray> &params);

private:
    /**
     * @brief Collection of commands and their codes
     */
    std::map<Command, char*> m_cmdCodes;
};

#endif // MESSAGEPARSER_H
