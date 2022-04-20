#ifndef SNAKECOMMON_H
#define SNAKECOMMON_H

#include "SnakeCommon_global.h"
#include <map>

using namespace std;

class SNAKECOMMON_EXPORT Contract
{
public:
    Contract();

    enum ClientCmd {
        CreateRoom,
        JoinRoom,
        LeaveRoom,
        ReadyToPlay,
        StartGame,
        ChangeDirection
    };

    enum ServerCmd {
        ClientIdRegistered,
        CreateRoomResponse,
        CreateRoomErrResponse,
        JoinRoomResponse,
        JoinRoomErrResponse,
        RoomListUpdated,
        ReadyListUpdated,
        GameTick,
        GameWinner
    };


    static char breakChar() { return s_breakChar; }
    static char endChar() { return s_endChar; }
    static const map<ClientCmd, const char *> &clientCmdCodes() {return s_clientCmdCodes; }
    static const map<ServerCmd, const char *> &serverCmdCodes() { return s_serverCmdCodes; }

private:
    /**
     * @brief Character used to separate parts of message
     */
    static const char s_breakChar;

    /**
     * @brief Character used to mark the end of a message
     */
    static const char s_endChar;

    /**
     * @brief Collection of client commands with their codes
     */
    static const map<ClientCmd, const char*> s_clientCmdCodes;

    /**
     * @brief Collection of server commands with their codes
     */
    static const map<ServerCmd, const char*> s_serverCmdCodes;
};

#endif // SNAKECOMMON_H
