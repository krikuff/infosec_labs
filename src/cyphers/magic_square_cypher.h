#pragma once

#include <vector>

#include <cyphers/i_cypher.h>

// Шифр, использующий магический квадрат
class MagicSquareCypher final : public ICypher
{
public:

    // Задать магический квадрат
    // Параметр config содержит квадрат n на n целых чисел от 1 до n в строковом представлении.
    // Если в config не квадрат, либо квадрат не магический, то вылетает исключение
    virtual void Configure(std::string const& config) override;

    virtual std::string Encrypt(std::string const& input) override;

    virtual std::string Decrypt(std::string const& input) override;

private:
    // Имплементация алгоритма шифровки/расшифровки
    std::string Pass(std::vector<int> const& square, std::string const& input);

    std::vector<int> ParseSquare(std::string const& str);

    void CheckSquareForMagic(std::vector<int> const& square);

private:
    std::vector<int> decryptionSquare_; //< Магический квадрат. Хранится в виде линейного массива строка за строкой
    std::vector<int> encryptionSquare_; //< Тот же квадрат, но индексы вместо значений, а значения вместо индексов
};
