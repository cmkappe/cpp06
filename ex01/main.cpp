/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckappe <ckappe@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:40:24 by ckappe            #+#    #+#             */
/*   Updated: 2026/04/03 14:40:29 by ckappe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

static const char* RESET = "\033[0m";
static const char* BOLD = "\033[1m";
static const char* CYAN = "\033[36m";
static const char* GREEN = "\033[32m";
static const char* RED = "\033[31m";
static const char* YELLOW = "\033[33m";

static void printData(const std::string& label, Data* ptr)
{
	std::cout << CYAN << BOLD << label << RESET << "\n";
	std::cout << "  address: " << ptr << "\n";
	if (ptr)
	{
		std::cout << "  x: " << ptr->x << "\n";
		std::cout << "  name: " << ptr->name << "\n";
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << BOLD << YELLOW << "=== Serialization Test ===" << RESET
			  << "\n\n";

	bool allPassed = true;

	Data stackData;
	stackData.x = 42;
	stackData.name = "stack_object";

	uintptr_t rawStack = Serializer::serialize(&stackData);
	Data* restoredStack = Serializer::deserialize(rawStack);

	printData("[STACK] Original", &stackData);
	printData("[STACK] Restored", restoredStack);
	std::cout << "[STACK] raw value: " << rawStack << "\n";
	bool stackPassed = (restoredStack == &stackData);
	allPassed = allPassed && stackPassed;
	std::cout << "[STACK] same address? "
			  << (stackPassed ? "YES" : "NO")
			  << " ("
			  << (stackPassed ? GREEN : RED)
			  << (stackPassed ? "PASS" : "FAIL")
			  << RESET << ")"
			  << "\n\n";

	Data* heapData = new Data;
	heapData->x = 2026;
	heapData->name = "heap_object";

	uintptr_t rawHeap = Serializer::serialize(heapData);
	Data* restoredHeap = Serializer::deserialize(rawHeap);

	printData("[HEAP] Original", heapData);
	printData("[HEAP] Restored", restoredHeap);
	std::cout << "[HEAP] raw value: " << rawHeap << "\n";
	bool heapPassed = (restoredHeap == heapData);
	allPassed = allPassed && heapPassed;
	std::cout << "[HEAP] same address? "
			  << (heapPassed ? "YES" : "NO")
			  << " ("
			  << (heapPassed ? GREEN : RED)
			  << (heapPassed ? "PASS" : "FAIL")
			  << RESET << ")"
			  << "\n\n";

	Data* nullPtr = 0;
	uintptr_t rawNull = Serializer::serialize(nullPtr);
	Data* restoredNull = Serializer::deserialize(rawNull);

	std::cout << "[NULL] raw value: " << rawNull << "\n";
	std::cout << "[NULL] deserialized pointer: " << restoredNull << "\n";
	bool nullPassed = (restoredNull == 0);
	allPassed = allPassed && nullPassed;
	std::cout << "[NULL] null preserved? "
			  << (nullPassed ? "YES" : "NO")
			  << " ("
			  << (nullPassed ? GREEN : RED)
			  << (nullPassed ? "PASS" : "FAIL")
			  << RESET << ")"
			  << "\n\n";

	std::cout << BOLD << "Final result: "
			  << (allPassed ? GREEN : RED)
			  << (allPassed ? "PASS" : "FAIL")
			  << RESET << "\n";

	delete heapData;
	return (allPassed ? 0 : 1);
}

