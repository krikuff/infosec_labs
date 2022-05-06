#pragma once

#include <string>
#include <unordered_map>

#define OPTION_PARAMETER_REQUIRED true

struct OptionDescription
{
    std::string description;
    bool parameterRequired = false;
};

using OptionsDescriptionMap = std::unordered_map<std::string, OptionDescription>;
using OptionsMap = std::unordered_map<std::string, std::string>;

std::string GetHelpString( std::string const& programDescription, OptionsDescriptionMap const& options );

OptionsMap ParseOptions( int argc, char** argv, OptionsDescriptionMap const& knownOptions );
