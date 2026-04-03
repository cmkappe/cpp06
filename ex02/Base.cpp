/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:27:14 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 17:32:32 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base* generate(void)
{
    int random = rand() % 3;
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p)
{
    // Pointer dynamic_cast returns NULL on mismatch, so we can chain checks
    if (dynamic_cast<A*>(p))
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p))
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p))
        std::cout << "C\n";
    else
        std::cout << "Unknown type\n";
}

void identify(Base& p)
{
    try
    {
        // Reference dynamic_cast throws std::bad_cast on mismatch
        (void)dynamic_cast<A&>(p);
        std::cout << "A\n";
    }
    catch (std::bad_cast&)
    {
        try
        {
            // If A cast failed, try B, then C
            (void)dynamic_cast<B&>(p);
            std::cout << "B\n";
        }
        catch (std::bad_cast&)
        {
            try
            {
                (void)dynamic_cast<C&>(p);
                std::cout << "C\n";
            }
            catch (std::bad_cast&)
            {
                // Should not really happen here, just extra safety check
                std::cout << "Unknown type\n";
            }
        }
    }
}

