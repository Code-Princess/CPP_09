/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 23:10:19 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>

#include "PmergeMe.hpp"

int main (int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<unsigned int> input;
	
	if (argc < 2)
	{
		std::cerr << "Error: invalid input! Expect numbers!" << std::endl;
        return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (!isPositiveInteger(arg)) 
		{
			std::cerr << "Error: invalid input '" << arg << "'. Only positive integers are allowed." << std::endl;
            return 1;
		}	
		try 
		{
			unsigned long val = std::stoul(arg);
			if (val > std::numeric_limits<unsigned int>::max()) 
			{
				std::cerr << "Error: Value '" << arg << "' exceeds unsigned int limit." << std::endl;
				return 1;
			}
			input.push_back(static_cast<unsigned int>(val));
		} 
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	
	PmergeMe mergeMe(input);
	printVec("Before: ", mergeMe.getInputNbrs());
	mergeMe.preSort();
	printVec("After: ", mergeMe.getNbrs());

	const std::vector<unsigned int>& vec_sorted = mergeMe.getNbrs();
	if (std::is_sorted(vec_sorted.begin(), vec_sorted.end()))
	std::cout << "The vector is sorted in ascending order." << std::endl;
    else
	std::cout << "The vector is not sorted." << std::endl;
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> duration = end - start;
	std::cout << "Time to process a range of " << mergeMe.getNbrs().size() << 
		" elements with std::vector: " << duration.count() << " us" << std::endl;
	return 0;
}
