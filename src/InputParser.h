#ifndef INPUTPARSER_H
#define INPUTPARSER_H
//Based on - http://stackoverflow.com/a/868894/8715

#include <string>
#include <map>
#include <boost/algorithm/string.hpp>

class InputParser {
public:    
    InputParser(const InputParser &orig);
    virtual ~InputParser();

    InputParser(int &argc, char **argv);
    
    bool hasCmd(std::string cmd) const;
    std::string getCmdParams(std::string cmd) const;
    int getTotalCmds() const;
    std::map<std::string, std::string> getAllCommands() const;
private:
    InputParser();
    void parse(int &argc, char **argv);
    std::string getAllParamsAfter(int &argc, char **argv, int &start) const;

    std::map<std::string, std::string> cmds;
};

#endif /* INPUTPARSER_H */

