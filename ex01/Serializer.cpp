
#include "Serializer.hpp"

// “Can I store a pointer as a number and recover it exactly?”
// uintptr_t is uintptr_t is an unsigned integer type capable of holding a converted pointer value
// reinterpret_cast allows for pointer-to-integer and integer-to-pointer conversions

Serializer::Serializer() {}
Serializer::Serializer(const Serializer&) {}
Serializer& Serializer::operator=(const Serializer&) { return *this; }
Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data* ptr){
    return reinterpret_cast<uintptr_t>(ptr);
}

// take this integer pointer representation and interpret it as a Data*
Data* Serializer::deserialize(uintptr_t raw){
    return reinterpret_cast<Data*>(raw);
}
