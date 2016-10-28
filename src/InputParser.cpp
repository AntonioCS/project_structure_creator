
#include "InputParser.h"

InputParser::InputParser() {
}

InputParser::InputParser(int &argc, char **argv) {
    this->parse(argc, argv);
}

InputParser::InputParser(const InputParser& orig) {

}

InputParser::~InputParser() {
}

bool InputParser::hasCmd(std::string cmd) const {
    return (this->cmds.count(cmd) == 1);
}

std::string InputParser::getCmdParams(std::string cmd) const {
    return this->cmds.at(cmd);
}

int InputParser::getTotalCmds() const {
    return this->cmds.size();
}

std::map<std::string, std::string> InputParser::getAllCommands() const {
    return this->cmds;
}

// ----------------------------------- Private --------------------------------------------
// ----------------------------------- Private --------------------------------------------
// ----------------------------------- Private --------------------------------------------

void InputParser::parse(int &argc, char **argv) {
    std::string cmd;
    std::string args;

    for (int i = 0; i < argc; i++) {
        //interpret as command if prefixed with -
        if (argv[i][0] == '-') {
            //in case of command with --
            int erase_len = (argv[i][1] == '-' ? 2 : 1);
            
            cmd = argv[i];
            cmd.erase(0, erase_len);
            
            args = this->getAllParamsAfter(argc, argv, ++i);
            boost::trim(args);
            
            this->cmds[cmd] = args;
        }
    }
}

std::string InputParser::getAllParamsAfter(int &argc, char **argv, int &start) const {
    std::string args;

    for (int i = start; i < argc; i++) {        
        if (argv[i][0] != '-') {
            args.append(argv[i]).append(" ");
        }
        
        break;
    }
    
    return args;
}