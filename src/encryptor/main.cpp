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

        const std::string keyData = ReadFileContents( programData.keyFileName );
        if( keyData.empty() )
        {
            throw std::runtime_error( "Empty key file" );
        }

        const std::string inputData = [ & ]()
        {
            if( programData.inputFileName.has_value() )
            {
                return ReadFileContents( programData.inputFileName.value() );
            }
            else
            {
                return ReadContents( std::cin );
            }
        }();

        if( inputData.empty() )
        {
            return 0;
        }

        const std::string result = [ & ]()
        {
            switch( programData.cypher )
            {
                case CypherType::MagicSquare:
                {
                    MagicSquareCypher cypher( keyData );

                    switch( programData.action )
                    {
                        case ProgramAction::Encrypt:
                            return cypher.Encrypt( inputData );
                        case ProgramAction::Decrypt:
                            return cypher.Decrypt( inputData );
                    }
                    break;
                }
                default:
                    throw std::runtime_error( "No cypher type given" );
            }
        }();

        if( programData.outputFileName.has_value() )
        {
            WriteToFile( result, programData.outputFileName.value() );
        }
        else
        {
            std::cout << result;
        }
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
