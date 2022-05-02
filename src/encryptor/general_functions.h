#pragma once

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

struct ProgramSettings
{
    std::string inputFileName;
    std::string outputFileName;
    std::string configFileName;
    ProgramAction action;
};

std::string ReadFileContents(std::string const& filename);

void WriteToFile(std::string const& data, std::string const& filename);

// Определение поддерживаемых аргументов командной строки
OptionsDescriptionMap GetOptionsDescription();

std::string GetProjectVersionString();

// Получение настроек из переданных аргументов
ProgramSettings ProcessArguments(int argc, char** argv);
