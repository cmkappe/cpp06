#pragma once

#include <iostream>
#include <cstdint>

struct Data
{
    int i;
    float f;
    char c;
};


class Serialization
{
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);

    private:
        Serialization();
        Serialization(const Serialization&);
        Serialization& operator=(const Serialization&);
        ~Serialization();
};
