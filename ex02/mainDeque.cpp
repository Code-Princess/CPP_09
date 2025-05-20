/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainDeque.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/20 20:09:54 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>

#include "PmergeMeDeque.hpp"

int main (int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();
	std::deque<unsigned int> input;
	if (!isValidInputDeque(argc, argv, input))
		return 1;
	else
	{
		PmergeMeDeque mergeMe(input);
		printVecDeque("Before: ", mergeMe.getInputNbrsDeque());
		mergeMe.preSortDeque();
		printVecDeque("After: ", mergeMe.getNbrsDeque());

		const std::deque<unsigned int>& vec_sorted = mergeMe.getNbrsDeque();
		if (std::is_sorted(vec_sorted.begin(), vec_sorted.end()))
			std::cout << "The deque is sorted in ascending order," << std::endl;
		else
			std::cout << "The deque is not sorted, " << std::endl;

		std::cout << "using " << mergeMe.getCompsDeque() << " comparisons.\n";
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cout << "Time to process a range of " << mergeMe.getNbrsDeque().size() << 
			" elements with std::deque: " << duration.count() << " us" << std::endl;
	}
	return 0;
}

