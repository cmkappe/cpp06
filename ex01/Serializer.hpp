#pragma once

#include <iostream>
#include <cstdint> // used for uintptr_t
#include <string>

struct Data
{
    int         x;
    std::string name;
};


class Serializer
{
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);

    private:
        Serializer();
        Serializer(const Serializer&);
        Serializer& operator=(const Serializer&);
        ~Serializer();
};
