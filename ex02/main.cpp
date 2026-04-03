/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:26:12 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 17:37:00 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

static const char* RESET = "\033[0m";
static const char* BOLD = "\033[1m";
static const char* CYAN = "\033[36m";
static const char* GREEN = "\033[32m";
static const char* YELLOW = "\033[33m";

static void printSection(const std::string& title)
{
    std::cout << CYAN << BOLD << title << RESET << "\n";
}

static void runSingleCase(const std::string& label, Base* ptr)
{
    std::cout << YELLOW << BOLD << "[" << label << "]" << RESET << "\n";
    std::cout << "  object address: " << ptr << "\n";

    std::cout << "  identify(ptr): ";
    identify(ptr);

    if (ptr)
    {
        std::cout << "  identify(*ptr): ";
        identify(*ptr);
    }
    else
    {
        std::cout << "  identify(*ptr): skipped (null pointer)\n";
    }

    std::cout << std::endl;
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << BOLD << YELLOW << "\n\n=== Identify Test ===" << RESET
              << "\n\n";

    printSection("Known concrete types");
    Base* a = new A();
    Base* b = new B();
    Base* c = new C();

    runSingleCase("A", a);
    runSingleCase("B", b);
    runSingleCase("C", c);

    delete a;
    delete b;
    delete c;

    printSection("Null pointer behavior (pointer overload only)");
    runSingleCase("NULL", 0);

    printSection("Randomly generated instances");
    for (int i = 1; i <= 5; ++i)
    {
        Base* ptr = generate();
        std::ostringstream label;
        label << "random round " << i;
        runSingleCase(label.str(), ptr);
        delete ptr;
    }

    std::cout << BOLD << "Final result: " << GREEN << "PASS" << RESET << "\n\n\n";

    return 0;
}