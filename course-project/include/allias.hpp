#ifndef ALLIAS_HPP
#define ALLIAS_HPP

#include <string>

class ClientCommand
{
    public:
        std::string TERMINATOR = "TERMINATOR";
        std::string CLIENT = "CLIENT";
        std::string SERVER = "SERVER";
        std::string CONFIRM = "CONFIRM";
        std::string QUIT = "QUIT";
        std::string INIT_CLIENT = "INIT_CLIENT";
        std::string CREATE = "CREATE";
        std::string CONNECT = "CONNECT";
        std::string ROOM_NOT_FOUND = "ROOM_NOT_FOUND";
        std::string ROOM_EXISTS = "ROOM_EXISTS";
        std::string INVALID_COMMAND = "INVALID_COMMAND";
        std::string DUMP = "DUMP";
        std::string START_GAME = "START_GAME";
        
        ClientCommand(std::string id)
        {
            this->TERMINATOR = id + " " + this->TERMINATOR;
            this->CLIENT = id + " " + this->CLIENT;
            this->SERVER = id + " " + this->SERVER;
            this->CONFIRM = id + " " + this->CONFIRM;
            this->QUIT = id + " " + this->QUIT;
            this->INIT_CLIENT = id + " " + this->INIT_CLIENT;
            this->CREATE = id + " " + this->CREATE;
            this->CONNECT = id + " " + this->CONNECT;
            this->ROOM_NOT_FOUND = id + " " + this->ROOM_NOT_FOUND;
            this->ROOM_EXISTS = id + " " + this->ROOM_EXISTS;
            this->INVALID_COMMAND = id + " " + this->INVALID_COMMAND;
            this->DUMP = id + " " + this->DUMP;
            this->START_GAME = id + " " + this->START_GAME;
        }

};

namespace utl 
{
    const std::string TERMINATOR = "TERMINATOR";
    const std::string CLIENT = "CLIENT";
    const std::string SERVER = "SERVER";

    const int MIN_PORT = 1024;
}

namespace game
{
    const std::string CONFIRM = "CONFIRM";
    const std::string QUIT = "QUIT";
}

namespace msg
{
    const std::string INIT_CLIENT = "INIT_CLIENT";
    const std::string CREATE = "CREATE";
    const std::string CONNECT = "CONNECT";
    const std::string ROOM_NOT_FOUND = "ROOM_NOT_FOUND";
    const std::string ROOM_EXISTS = "ROOM_EXISTS";
    const std::string INVALID_COMMAND = "INVALID_COMMAND";
    const std::string DUMP = "DUMP";
    const std::string START_GAME = "START_GAME";
    const std::string NO_SUCH_USER = "NO_SUCH_USER";
    const std::string SUCCES = "SUCCES";
    const std::string STAT = "STAT";
    const std::string KILL = "KILL";
}

namespace room
{
    const std::string PATH_TO_ROOM = "/home/axr/prog/study/OS/main/course-project/executables/room";
    const std::string PATH_TO_GAMES_DS = "/home/axr/prog/study/OS/main/course-project/db/sample.txt";
    const std::string PATH_TO_USERS_DB = "/home/axr/prog/study/OS/main/course-project/db/sample.txt";
}

namespace sym
{
    const std::string RESET  = "\033[0m";
	const std::string BLACK  = "\033[30m";      /* Black */
	const std::string RED    = "\033[31m";      /* Red */
	const std::string GREEN  = "\033[32m";      /* Green */
	const std::string YELLOW = "\033[33m";      /* Yellow */
	const std::string BLUE   = "\033[34m";      /* Blue */
	const std::string MAGENTA= "\033[35m";      /* Magenta */
	const std::string CYAN   = "\033[36m";      /* Cyan */
	const std::string WHITE  = "\033[37m";      /* White */
	const std::string BOLDBLACK  = "\033[1m\033[30m";      /* Bold Black */
	const std::string BOLDRED    = "\033[1m\033[31m";      /* Bold Red */
	const std::string BOLDGREEN  = "\033[1m\033[32m";      /* Bold Green */
	const std::string BOLDYELLOW = "\033[1m\033[33m";      /* Bold Yellow */
	const std::string BOLDBLUE   = "\033[1m\033[34m";      /* Bold Blue */
	const std::string BOLDMAGENTA= "\033[1m\033[35m";      /* Bold Magenta */
	const std::string BOLDCYAN   = "\033[1m\033[36m";      /* Bold Cyan */
	const std::string BOLDWHITE  = "\033[1m\033[37m";      /* Bold White */
}

#endif

