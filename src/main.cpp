#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <array>
//#include <windows.h>
#include <fstream>
#include <sstream>
#include "InputParser.h"
#include <boost/filesystem.hpp>
#include <typeinfo>

namespace boostfs = boost::filesystem;
using namespace std;

void createOnProjectFolder(boostfs::path srcFile, boostfs::path destinationFolder);
void loopTemplateFolder(const boostfs::path &templateDirectory, const boostfs::path &destinationFolder);
string readFileContents(const char *pathToFile);
void writeFileContents(const string &content, const boostfs::path &destinationFile);
void createProject(const string &projectFolder, const string &projectName, const string &type, const string &templateType, const string &binaryName);

void createProject(const string &projectFolder, const string &projectName, const string &type, const string &templateType, const string &binaryName) {

    boostfs::path destinationFolder(projectFolder);
    destinationFolder.append(projectName);

    if (boostfs::is_directory(destinationFolder) == false) {
        boostfs::create_directory(destinationFolder);
    }

    boostfs::path currentDirectory(boostfs::current_path());
    boostfs::path templateDirectory(boostfs::path(currentDirectory).append("resources/templates").append(type).append(templateType));

    loopTemplateFolder(templateDirectory, destinationFolder);
}

void loopTemplateFolder(const boostfs::path &templateDirectory, const boostfs::path &destinationFolder) {
    if (boostfs::is_directory(templateDirectory)) {
        for (auto &item : boostfs::directory_iterator(templateDirectory)) {
            if (boostfs::is_directory(item)) {
                boostfs::path tmpPath(destinationFolder);
                //cout << typeid(item.path().filename().string()).name() << endl;
                //cout << item.path().filename().string() << endl;
                //exit(1);
                tmpPath.append(item.path().filename().string());

                if (boostfs::is_directory(tmpPath) == false) {
                    boostfs::create_directory(tmpPath);
                }

                loopTemplateFolder(item.path(), tmpPath);
            } else {
                createOnProjectFolder(item.path(), destinationFolder);
            }
        }
    } else {
        cout << "No template folder: " << templateDirectory << endl;
    }
}

void createOnProjectFolder(boostfs::path srcFile, boostfs::path destinationFolder) {
    string content(readFileContents(srcFile.string().c_str()));
    boostfs::path destinationFile(destinationFolder);

    destinationFile.append(srcFile.stem().string());

    writeFileContents(content, destinationFile);
}

void writeFileContents(const string &content, const boostfs::path &destinationFile) {
    ofstream outputFile;
    outputFile.open(destinationFile.string());

    if (outputFile.is_open()) {
        outputFile << content;
        outputFile.close();
    }
}

string readFileContents(const char *pathToFile) {
    string fileContents;
    ifstream in(pathToFile);

    if (in) {
        ostringstream contents;
        contents << in.rdbuf();
        in.close();
        fileContents = contents.str();
    }

    return fileContents;
}

//make && build\pcreator.exe --projectFolder C:\Users\antoniocs\Projects\Personal\cpp\ProjectCreator\test --projectName TestProject
int main(int argc, char **argv) {
    InputParser input(argc, argv);

    if (argc > 1 && input.hasCmd("projectFolder") && input.hasCmd("projectName")) {
        string type = input.hasCmd("type") ? input.getCmdParams("type") : "cpp";
        string templateType = input.hasCmd("template") ? input.getCmdParams("template") : "default";

        createProject(input.getCmdParams("projectFolder"), input.getCmdParams("projectName"), type, templateType, "hello");
    } else {
        cout << "Missing parameters" << endl;
    }

    return 0;
}

