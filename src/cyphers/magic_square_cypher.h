#pragma once

#include <vector>

#include <cyphers/i_cypher.h>

using namespace std;

// Шифр, использующий магический квадрат
class MagicSquareCypher final : public ICypher
{
public:

    // Задать магический квадрат
    // Параметр config содержит квадрат n на n целых чисел от 1 до n в строковом представлении.
    // Если в config не квадрат, либо квадрат не магический, то вылетает исключение
    virtual void Configure(string const& config) override;

    virtual string Encrypt(string const& input) override;

    virtual string Decrypt(string const& input) override;

private:
    // Имплементация алгоритма шифровки/расшифровки
    string Pass(vector<int> const& square, string const& input);

    vector<int> ParseSquare(string const& str);

    void CheckSquareForMagic(vector<int> const& square);

private:
    vector<int> decryptionSquare_; //< Магический квадрат. Хранится в виде линейного массива строка за строкой
    vector<int> encryptionSquare_; //< Тот же квадрат, но индексы вместо значений, а значения вместо индексов
};
