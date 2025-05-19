/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/19 22:02:53 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>

#include "PmergeMe.hpp"

int main (int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<unsigned int> input;
	if (!isValidInput(argc, argv, input))
		return 1;
	else
	{
		PmergeMe mergeMe(input);
		printVec("Before: ", mergeMe.getInputNbrs());
		mergeMe.preSort();
		printVec("After: ", mergeMe.getNbrs());

		const std::vector<unsigned int>& vec_sorted = mergeMe.getNbrs();
		if (std::is_sorted(vec_sorted.begin(), vec_sorted.end()))
			std::cout << "The vector is sorted in ascending order," << std::endl;
		else
			std::cout << "The vector is not sorted, " << std::endl;

		std::cout << "using " << mergeMe.getComps() << " comparisons.\n";
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cout << "Time to process a range of " << mergeMe.getNbrs().size() << 
			" elements with std::vector: " << duration.count() << " us" << std::endl;
	}
	return 0;
}

