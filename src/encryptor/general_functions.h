#pragma once

#include <optional>
#include <stdexcept>
#include <string>

#include <program_options/program_options.h>

// Исключение, нужное чтобы показать инструкцию и корректно завершиться
struct ShowHelpAndExit : public std::exception
{
    using std::exception::exception::exception;
};

// Исключение, нужное чтобы показать версию и корректно завершиться
struct ShowVersionAndExit : public std::exception
{
    using std::exception::exception::exception;
};

// Действие, требуемое от программы
enum ProgramAction
{
    Encrypt,
    Decrypt,
};

enum class CypherType
{
    MagicSquare,
};

struct ProgramSettings
{
    std::optional<std::string> inputFileName;
    std::optional<std::string> outputFileName;
    std::string keyFileName;
    ProgramAction action;
    CypherType cypher;
};

std::string CypherToString( CypherType cypher );

CypherType StringToCypher( std::string const& cypher );

std::string ReadFileContents( std::string const& filename );

void WriteToFile( std::string const& data, std::string const& filename );

// Определение поддерживаемых аргументов командной строки
OptionsDescriptionMap GetOptionsDescription();

std::string GetProjectVersionString();

// Получение настроек из переданных аргументов
ProgramSettings ProcessArguments( int argc, char** argv );

template<typename T>
std::string ReadContents( T& stream )
{
    std::string contents;
    std::string line;
    while( getline( stream, line ) )
    {
        contents += line + '\n';
    }
    contents.pop_back();
    return contents;
}
