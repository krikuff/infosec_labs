#include <encryptor/general_functions.h>

#include <fstream>
#include <iostream>

#include <config.h>

namespace {

const string DefaultInputFileName  = "input.txt";
const string DefaultOutputFileName = "output.txt";
const string DefaultConfigFileName = "config.txt";

} // namespace anonymous

string ReadFileContents(string const& filename)
{
    ifstream file(filename);
    if( !file.good() )
    {
        throw runtime_error("Couldn't open file " + filename);
    }

    string contents;
    string line;
    while( getline(file, line) )
    {
        contents += line + '\n';
    }
    contents.pop_back();
    return contents;
}

void WriteToFile(std::string const& data, std::string const& filename)
{
    ofstream file(filename);
    if( !file.good() )
    {
        throw runtime_error("Couldn't open file " + filename);
    }

    file << data;
}

// Определение поддерживаемых аргументов командной строки
OptionsDescriptionMap GetOptionsDescription()
{
    return {
        {"-h", {"show this help and exit" }},
        {"-i", {"set input file  (default is \"" + DefaultInputFileName  + "\")", OPTION_PARAMETER_REQUIRED }},
        {"-o", {"set output file (default is \"" + DefaultOutputFileName + "\")", OPTION_PARAMETER_REQUIRED }},
        {"-c", {"set config file (default is \"" + DefaultConfigFileName + "\")", OPTION_PARAMETER_REQUIRED }},
        {"-e", {"encrypt input (default action)" }},
        {"-d", {"decrypt input" }},
        {"-v", {"show version" }},
    };
}

string GetProjectVersionString()
{
    return string( PROJECT_NAME ) + " " + PROJECT_VERSION;
}

// Получение настроек из переданных аргументов
ProgramSettings ProcessArguments(int argc, char** argv)
{
    auto options = ParseOptions( argc, argv, GetOptionsDescription() );

    ProgramSettings settings{ DefaultInputFileName, DefaultOutputFileName, DefaultConfigFileName, ProgramAction::Encrypt };
    if (options.count("-h"))
    {
        throw ShowHelpAndExit();
    }
    if (options.count("-v"))
    {
        throw ShowVersionAndExit();
    }
    if (options.count("-i"))
    {
        settings.inputFileName = options["-i"];
    }
    if (options.count("-o"))
    {
        settings.outputFileName = options["-o"];
    }
    if (options.count("-c"))
    {
        settings.configFileName = options["-c"];
    }
    if (options.count("-d"))
    {
        settings.action = ProgramAction::Decrypt;
    }
    if (options.count("-e"))
    {
        settings.action = ProgramAction::Encrypt;
    }

    return settings;
}

