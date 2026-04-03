/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:57:22 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 17:08:32 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <exception>
#include <iostream>

static const char* RESET = "\033[0m";
static const char* BOLD = "\033[1m";
static const char* CYAN = "\033[36m";
static const char* GREEN = "\033[32m";
static const char* RED = "\033[31m";
static const char* YELLOW = "\033[33m";

int main(int ac, char **av)
{
    std::cout << BOLD << YELLOW << "\n=== Scalar Converter ===" << RESET << "\n\n";

    if (ac != 2)
    {
        std::cerr << RED << BOLD << "Error" << RESET << ": exactly one argument expected.\n";
        std::cerr << "Usage: ./ScalarConverter <literal>\n";
        std::cerr << "Examples: ./ScalarConverter 42 | ./ScalarConverter a | ./ScalarConverter nan\n\n\n";
        return 1;
    }

    std::cout << CYAN << BOLD << "Input literal" << RESET << "\n";
    std::cout << "  " << av[1] << "\n\n";

    try
    {
        std::cout << CYAN << BOLD << "Converted values" << RESET << "\n";
        ScalarConverter::convert(av[1]);
        std::cout << "\n" << BOLD << "Final result: " << GREEN << "PASS" << RESET << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << RED << BOLD << "Conversion error" << RESET << ": " << e.what() << "\n";
        std::cerr << BOLD << "Final result: " << RED << "FAIL" << RESET << "\n";
        return 1;
    }

    return 0;
}