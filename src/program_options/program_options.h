#pragma once

#include <string>
#include <unordered_map>

using namespace std;

#define OPTION_PARAMETER_REQUIRED true

struct OptionDescription
{
    string description;
    bool parameterRequired = false;
};

using OptionsDescriptionMap = unordered_map<string, OptionDescription>;
using OptionsMap = unordered_map<string, string>;

void ShowHelp(string const& programDescription, OptionsDescriptionMap const& options);

OptionsMap ParseOptions(int argc, char** argv, OptionsDescriptionMap const& knownOptions);
