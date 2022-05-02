#include <program_options/program_options.h>

#include <stdexcept>
#include <vector>

namespace {

std::string OptionsToString(OptionsDescriptionMap const& options)
{
    std::string ret ("Options:");
    for(auto& option : options)
    {
        std::string parameter(11, ' ');
        if( option.second.parameterRequired )
        {
            parameter = "<parameter>";
        }
        ret += "\n    " + option.first + " " + parameter + " " + option.second.description;
    }
    return ret;
}

} // namespace anonymous

std::string GetHelpString(std::string const& programDescription, OptionsDescriptionMap const& options)
{
    return programDescription + "\n" + OptionsToString(options);
}

OptionsMap ParseOptions(int argc, char** argv, OptionsDescriptionMap const& knownOptions)
{
    OptionsMap options;
    for(int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if( !knownOptions.count(arg) )
        {
            throw std::invalid_argument(
                "Found option \"" + arg + "\" which wasn't expected.\n" + OptionsToString(knownOptions)
            );
        }

        auto& param = options[arg];
        if( knownOptions.at(arg).parameterRequired )
        {
            ++i;
            if( i >= argc )
            {
                throw std::runtime_error("Option \"" + arg + "\" needs a parameter");
            }

            param = std::string( argv[i] );
        }
    }

    return options;
}
