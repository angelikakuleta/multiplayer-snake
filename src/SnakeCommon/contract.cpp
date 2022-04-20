#include "contract.h"

const char BREAK_CHAR = '#';
const char END_CHAR = '$';

const char* CMD_CREATE_ROOM = "CRM";
const char* CMD_JOIN_ROOM = "JRM";
const char* CMD_LEAVE_ROOM = "LRM";
const char* CMD_READY_TO_PLAY = "RTP";
const char* CMD_START_GAME = "SGM";
const char* CMD_CHANGE_DIRECTION = "CDR";

const char* CMD_CLIENET_ID_REG = "CID";
const char* CMD_CREATE_ROOM_RESP = "CRR";
const char* CMD_CREATE_ROOM_ERR = "CRE";
const char* CMD_JOIN_ROOM_RESP = "JRR";
const char* CMD_JOIN_ROOM_ERR = "JRE";
const char* CMD_ROOM_LIST_UPD = "RMU";
const char* CMD_READY_LIST_UPD = "RLU";
const char* CMD_GAME_TICK = "GMT";
const char* CMD_GAME_WINNER = "GMW";

Contract::Contract()
{
}

const char Contract::s_breakChar = BREAK_CHAR;

const char Contract::s_endChar = END_CHAR;

const map<Contract::ClientCmd, const char*> Contract::s_clientCmdCodes = {
    { ClientCmd::CreateRoom, CMD_CREATE_ROOM },
    { ClientCmd::JoinRoom, CMD_JOIN_ROOM },
    { ClientCmd::LeaveRoom, CMD_LEAVE_ROOM },
    { ClientCmd::ReadyToPlay, CMD_READY_TO_PLAY },
    { ClientCmd::StartGame, CMD_START_GAME },
    { ClientCmd::ChangeDirection, CMD_CHANGE_DIRECTION }
};

const map<Contract::ServerCmd, const char*> Contract::s_serverCmdCodes = {
    { ServerCmd::ClientIdRegistered, CMD_CLIENET_ID_REG },
    { ServerCmd::CreateRoomResponse, CMD_CREATE_ROOM_RESP },
    { ServerCmd::CreateRoomErrResponse, CMD_CREATE_ROOM_ERR },
    { ServerCmd::JoinRoomResponse, CMD_JOIN_ROOM_RESP },
    { ServerCmd::JoinRoomErrResponse, CMD_JOIN_ROOM_ERR },
    { ServerCmd::RoomListUpdated, CMD_ROOM_LIST_UPD },
    { ServerCmd::ReadyListUpdated, CMD_READY_LIST_UPD },
    { ServerCmd::GameTick, CMD_GAME_TICK },
    { ServerCmd::GameWinner, CMD_GAME_WINNER },
};
