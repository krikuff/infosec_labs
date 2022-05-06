#include <encryptor/general_functions.h>

#include <fstream>

#include <config.h>

namespace
{

const std::string DefaultKeyFileName = "key.txt";

const CypherType DefaultCypher = CypherType::MagicSquare;

} // namespace

std::string CypherToString( CypherType cypher )
{
    switch( cypher )
    {
        case CypherType::MagicSquare:
            return "MagicSquare";
        default:
            throw std::invalid_argument( "Couldn't convert cypher of unknown type to string" );
    }
}

CypherType StringToCypher( std::string const& cypher )
{
    if( cypher == "MagicSquare" )
    {
        return CypherType::MagicSquare;
    }

    throw std::invalid_argument( "Couldn't parse cypher from string" );
}

std::string ReadFileContents( std::string const& filename )
{
    std::ifstream file( filename );
    if( !file.good() )
    {
        throw std::runtime_error( "Couldn't open file " + filename );
    }

    return ReadContents( file );
}

void WriteToFile( std::string const& data, std::string const& filename )
{
    std::ofstream file( filename );
    if( !file.good() )
    {
        throw std::runtime_error( "Couldn't open file " + filename );
    }

    file << data;
}

// Определение поддерживаемых аргументов командной строки
OptionsDescriptionMap GetOptionsDescription()
{
    return {
        { "-h", { "show this help and exit" } },
        { "-i", { "set input file  (reads from stdin if not specified)", OPTION_PARAMETER_REQUIRED } },
        { "-o", { "set output file (prints to stdout if not specified)", OPTION_PARAMETER_REQUIRED } },
        { "-k", { "set config file (default is \"" + DefaultKeyFileName + "\")", OPTION_PARAMETER_REQUIRED } },
        { "-m", { "set encryption method\"" + CypherToString( DefaultCypher ) + "\"", OPTION_PARAMETER_REQUIRED } },
        { "-e", { "encrypt input (default action)" } },
        { "-d", { "decrypt input" } },
        { "-v", { "show version" } },
    };
}

std::string GetProjectVersionString()
{
    return std::string( PROJECT_NAME ) + " " + PROJECT_VERSION;
}

// Получение настроек из переданных аргументов
ProgramSettings ProcessArguments( int argc, char** argv )
{
    auto options = ParseOptions( argc, argv, GetOptionsDescription() );

    ProgramSettings settings{ std::nullopt, std::nullopt, DefaultKeyFileName, ProgramAction::Encrypt, DefaultCypher };

    if( options.count( "-h" ) )
    {
        throw ShowHelpAndExit();
    }
    if( options.count( "-v" ) )
    {
        throw ShowVersionAndExit();
    }

    if( options.count( "-m" ) )
    {
        settings.cypher = StringToCypher( options[ "-m" ] );
    }

    // TODO: сделать инпут и аутпут зависимыми от типа шифра. Ну или унифицировать на уровне шифров
    if( options.count( "-i" ) )
    {
        settings.inputFileName = options[ "-i" ];
    }
    if( options.count( "-o" ) )
    {
        settings.outputFileName = options[ "-o" ];
    }
    if( options.count( "-k" ) )
    {
        settings.keyFileName = options[ "-k" ];
    }

    if( options.count( "-d" ) )
    {
        settings.action = ProgramAction::Decrypt;
    }
    else if( options.count( "-e" ) )
    {
        settings.action = ProgramAction::Encrypt;
    }

    return settings;
}
