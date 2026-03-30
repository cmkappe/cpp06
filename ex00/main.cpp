/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:57:22 by ckappe            #+#    #+#             */
/*   Updated: 2026/03/30 15:09:51 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <exception>
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "\nError!\nUsage: ./ScalarConverter <literal>\n" << std::endl;
        return 1;
    }
    
    try
    {
        ScalarConverter::convert(av[1]);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Conversion error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}