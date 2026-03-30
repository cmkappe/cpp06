/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:49:38 by ckappe            #+#    #+#             */
/*   Updated: 2026/03/30 15:03:34 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

enum Type { 
    CHAR, 
    INT, 
    FLOAT,
    DOUBLE, 
    SPECIAL, // for nan, inf, -inf
    INVALID 
};

// --- SPECIALS ---
// nanf: NaN = Not a Number (result of undefined math operations) e.. g. 0.0f/0.0f
// inff: positive/negative infinity (result of overflow) e. g. 1.0f/0.0f
// with f at the end => float literals, without f => double
// Specials need to be hadled manually, because they don’t behave like normal numbers (conversions to char or int are impossible)

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}

static Type detectType(const std::string& literal)
{

    // placeholder
    if (literal.length() == 1 && !std::isdigit(literal[0]) && std::isprint(literal[0]))
        return CHAR;
    if (literal.find('.') != std::string::npos)
    {
        if (literal.back() == 'f')
            return FLOAT;
        return DOUBLE;
    }
    if (literal == "nan" || literal == "+inf" || literal == "-inf"
        || literal == "nanf" || literal == "+inff" || literal == "-inff")
        return SPECIAL;
    if (std::all_of(literal.begin(), literal.end(), ::isdigit))
        return INT;
    return INVALID;
}

void ScalarConverter::convert(const std::string& literal)
{
    (void)literal;
}
