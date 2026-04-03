/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:40:33 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 14:44:11 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

uintptr_t Serialization::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serialization::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}

Serialization::Serialization() {}
Serialization::Serialization(const Serialization&) {}
Serialization& Serialization::operator=(const Serialization&) { return *this; }
Serialization::~Serialization() {}
