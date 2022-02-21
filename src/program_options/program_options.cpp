#include <program_options/program_options.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

namespace {

string OptionsToString(OptionsDescriptionMap const& options)
{
    stringstream ret;
    ret << "Options:";
    for(auto& option : options)
    {
        string parameter(11, ' ');
        if( option.second.parameterRequired )
        {
            parameter = "<parameter>";
        }
        ret << "\n    " << option.first << " " << parameter << " " << option.second.description;
    }
    return ret.str();
}

} // namespace anonymous

void ShowHelp(string const& programDescription, OptionsDescriptionMap const& options)
{
    cout << programDescription << "\n" << OptionsToString(options);
}

OptionsMap ParseOptions(int argc, char** argv, OptionsDescriptionMap const& knownOptions)
{
    OptionsMap options;
    for(int i = 1; i < argc; ++i)
    {
        string arg(argv[i]);
        auto& param = options[arg];
        if( !knownOptions.count(arg) )
        {
            throw invalid_argument(
                "Found option \"" + arg + "\" which wasn't expected.\n" + OptionsToString(knownOptions)
            );
        }

        if( knownOptions.at(arg).parameterRequired )
        {
            ++i;
            if( i >= argc )
            {
                throw runtime_error("Option \"" + arg + "\" needs a parameter");
            }

            param = string( argv[i] );
        }
    }

    return options;
}
