/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 20:49:38 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 17:07:26 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <limits>

enum Type { 
    CHAR, 
    INT, 
    FLOAT,
    DOUBLE, 
    SPECIAL, // for nan, inf, -inf
    INVALID 
};

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }
ScalarConverter::~ScalarConverter() {}

static bool isFloatOrDouble(const std::string& literal, bool& isFloat)
{
    if (literal.empty())
        return false;

    size_t i = 0;
    bool hasDot = false;
    bool hasDigit = false;

    // optional sign
    if (literal[i] == '+' || literal[i] == '-')
        i++;

    for (; i < literal.length(); i++)
    {
        if (std::isdigit(static_cast<unsigned char>(literal[i])))
        {
            hasDigit = true;
        }
        else if (literal[i] == '.')
        {
            if (hasDot)
                return false; // second dot -> invalid
            hasDot = true;
        }
        else if (literal[i] == 'f' && i == literal.length() - 1)
        {
            isFloat = true;
            return hasDigit; // must have at least one digit
        }
        else
        {
            return false;
        }
    }
    isFloat = false;
    return hasDot && hasDigit;
}

// --- SPECIALS ---
// nanf: NaN = Not a Number (result of undefined math operations) e.. g. 0.0f/0.0f
// inff: positive/negative infinity (result of overflow) e. g. 1.0f/0.0f
// with f at the end => float literals, without f => double
// Specials need to be hadled manually, because they don’t behave like normal numbers (conversions to char or int are impossible)

static Type detectType(const std::string& literal)
{
    if (literal.empty())
        return INVALID;

    bool isFloat = false;
    
    if (literal == "nan" || literal == "+inf" || literal == "-inf"
        || literal == "nanf" || literal == "+inff" || literal == "-inff")
        return SPECIAL;
        
    if (literal.length() == 1
        && !std::isdigit(static_cast<unsigned char>(literal[0]))
        && std::isprint(static_cast<unsigned char>(literal[0])))
        return CHAR;
        
    // Fast-path for pure signed/unsigned integer literals (e.g. -42, +7, 0)
    size_t i = (literal[0] == '-' || literal[0] == '+') ? 1 : 0;
    bool onlyDigits = (i < literal.length());
    while (i < literal.length() && onlyDigits)
    {
        if (!std::isdigit(static_cast<unsigned char>(literal[i])))
            onlyDigits = false;
        ++i;
    }
    if (onlyDigits)
        return INT;
        
    if (isFloatOrDouble(literal, isFloat))
    {
        if (isFloat)
            return FLOAT;
        return DOUBLE;
    }
    return INVALID;
}

static void printImpossibleAll()
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

static void printConvertedValues(double dVal)
{
    // cache these checks once to keep the output logic readable below
    const bool isNaN = std::isnan(dVal);
    const bool isInf = std::isinf(dVal);

    // Subject-style formatting: whole numbers are shown as x.0 / x.0f
    const bool isWholeNumber = std::isfinite(dVal)
        && dVal == static_cast<long long>(dVal);

    // some casts simply don't make sense (NaN/inf or out of range).
    const bool charImpossible = isNaN || isInf
        || dVal < std::numeric_limits<char>::min()
        || dVal > std::numeric_limits<char>::max();
    const bool intImpossible = isNaN || isInf
        || dVal < std::numeric_limits<int>::min()
        || dVal > std::numeric_limits<int>::max();

    // CHAR output:
    // - impossible if conversion cannot be represented
    // - Non displayable for ASCII control chars (e.g. 0 = nul , 10 = nl)
    // - printable characters are shown in single quotes
    std::cout << "char: ";
    if (charImpossible)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<unsigned char>(static_cast<char>(dVal))))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(dVal) << "'" << std::endl;

    std::cout << "int: ";
    if (intImpossible)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(dVal) << std::endl;

    // FLOAT output keeps pseudo-literals explicit and adds the mandatory 'f'
    std::cout << "float: ";
    if (isNaN)
        std::cout << "nanf" << std::endl;
    else if (isInf)
        std::cout << (dVal < 0 ? "-inff" : "+inff") << std::endl;
    else
    {
        float fVal = static_cast<float>(dVal);
        if (isWholeNumber)
            std::cout << std::fixed << std::setprecision(1) << fVal << "f" << std::endl;
        else
            std::cout << fVal << "f" << std::endl;
        std::cout << std::defaultfloat;
    }

    // DOUBLE output same as float rules but without the trailing 'f'
    std::cout << "double: ";
    if (isNaN)
        std::cout << "nan" << std::endl;
    else if (isInf)
        std::cout << (dVal < 0 ? "-inf" : "+inf") << std::endl;
    else
    {
        if (isWholeNumber)
            std::cout << std::fixed << std::setprecision(1) << dVal << std::endl;
        else
            std::cout << dVal << std::endl;
        std::cout << std::defaultfloat;
    }
}

void ScalarConverter::convert(const std::string& literal)
{
    Type type = detectType(literal);
    double dVal = 0.0;

    if (type == SPECIAL)
    {
        std::string floatLiteral;
        std::string doubleLiteral;

        // handle pseudo-literals so output is stable
        if (literal == "nan" || literal == "nanf")
        {
            floatLiteral = "nanf";
            doubleLiteral = "nan";
        }
        else if (literal == "+inf" || literal == "+inff")
        {
            floatLiteral = "+inff";
            doubleLiteral = "+inf";
        }
        else
        {
            floatLiteral = "-inff";
            doubleLiteral = "-inf";
        }

        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: " << floatLiteral << std::endl;
        std::cout << "double: " << doubleLiteral << std::endl;
        return;
    }

    if (type == INVALID)
    {
        printImpossibleAll();
        return;
    }

    try // Any malformed input or overflow in stoi/stof/stod maps to "impossible" outputs
    {
        switch (type)
        {
            case CHAR:
                dVal = static_cast<double>(literal[0]);
                break;
            case INT:
                dVal = static_cast<double>(std::stoi(literal));
                break;
            case FLOAT:
                dVal = static_cast<double>(std::stof(literal));
                break;
            case DOUBLE:
                dVal = std::stod(literal);
                break;
            default:
                printImpossibleAll();
                return;
        }
    }
    catch (const std::exception&)
    {
        printImpossibleAll();
        return;
    }

    printConvertedValues(dVal);
}
