#pragma once

#include <string>
#include <vector>

// Шифр, использующий магический квадрат
class MagicSquareCypher final
{
public:
    explicit MagicSquareCypher( std::string const& square );

    // Задать магический квадрат
    // Параметр config содержит квадрат n на n целых чисел от 1 до n в строковом представлении.
    // Если в config не квадрат, либо квадрат не магический, то вылетает исключение
    void Configure( std::string const& square );

    std::string Encrypt( std::string const& input );

    std::string Decrypt( std::string const& input );

private:
    // Имплементация алгоритма шифровки/расшифровки
    std::string Pass( std::vector<int> const& square, std::string const& input );

    std::vector<int> ParseSquare( std::string const& str );

    void CheckSquareForMagic( std::vector<int> const& square );

private:
    std::vector<int> decryptionSquare_; //< Магический квадрат. Хранится в виде линейного массива строка за строкой
    std::vector<int> encryptionSquare_; //< Тот же квадрат, но индексы вместо значений, а значения вместо индексов
};
