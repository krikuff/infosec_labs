#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <cyphers/magic_square_cypher.h>
#include <encryptor/general_functions.h>

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        const auto programData = ProcessArguments(argc, argv);

        const string configData = ReadFileContents( programData.configFileName );
        const string inputData = ReadFileContents( programData.inputFileName );

        unique_ptr<ICypher> cypher = make_unique< MagicSquareCypher >();
        cypher->Configure(configData);

        string result;
        switch(programData.action)
        {
            case ProgramAction::Encrypt:
                result = cypher->Encrypt(inputData);
                break;
            case ProgramAction::Decrypt:
                result = cypher->Decrypt(inputData);
                break;
        }

        WriteToFile(result, programData.outputFileName);
    }
    catch( ShowHelpAndExit& )
    {
        cout << GetHelpString( "Simple encryption/decryption utility.", GetOptionsDescription() );
    }
    catch( ShowVersionAndExit& )
    {
        cout << GetProjectVersionString() << endl;
    }
    catch( exception& e )
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch( ... )
    {
        cerr << "Critical error!" << endl;
        return 2;
    }

    return 0;
}
