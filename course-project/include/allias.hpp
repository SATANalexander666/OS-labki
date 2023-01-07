#ifndef ALLIAS_HPP
#define ALLIAS_HPP

#include <string>

namespace utl 
{
    const std::string TERMINATOR = "TERMINATOR";
    const std::string CLIENT = "CLIENT";
    const std::string SERVER = "SERVER";

    const int MIN_PORT = 5554;
}

namespace game
{
    const std::string KILL = "KILL";
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
}

namespace room
{
    const std::string PATH_TO_ROOM = "/home/axr/prog/study/OS/main/course-project/executables/room";
    const std::string PATH_TO_DB = "/home/axr/prog/study/OS/main/course-project/db/sample.txt";
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

