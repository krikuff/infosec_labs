#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <cyphers/magic_square_cypher.h>
#include <encryptor/general_functions.h>

int main( int argc, char** argv )
{
    try
    {
        auto const programData = ProcessArguments( argc, argv );

        const std::string configData = ReadFileContents( programData.configFileName );
        const std::string inputData = ReadFileContents( programData.inputFileName );

        std::string result;
        switch( programData.cypher )
        {
            case CypherType::MagicSquare:
            {
                MagicSquareCypher cypher( configData );

                switch( programData.action )
                {
                    case ProgramAction::Encrypt:
                        result = cypher.Encrypt( inputData );
                        break;
                    case ProgramAction::Decrypt:
                        result = cypher.Decrypt( inputData );
                        break;
                }
                break;
            }
            default:
                throw std::runtime_error( "No cypher type given" );
        }

        WriteToFile( result, programData.outputFileName );
    }
    catch( ShowHelpAndExit& )
    {
        std::cout << GetHelpString( "Simple encryption/decryption utility.", GetOptionsDescription() );
    }
    catch( ShowVersionAndExit& )
    {
        std::cout << GetProjectVersionString() << std::endl;
    }
    catch( std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch( ... )
    {
        std::cerr << "Critical error!" << std::endl;
        return 2;
    }

    return 0;
}
