/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/20 21:17:57 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <chrono>

#include "PmergeMe.hpp"
#include "PmergeMeDeque.hpp"

int main (int argc, char* argv[])
{
	bool vecOK;
	bool deqOK;
	
	vecOK = runSortVec(argc, argv);
	deqOK = runSortDeque(argc, argv);
	if (!vecOK || !deqOK)
		return 1;
	return 0;
}

bool runSortVec(int argc, char* argv[])
{
	std::vector<unsigned int> input;
	if (!isValidInput(argc, argv, input))
	return 1;
	else
	{
		auto start = std::chrono::high_resolution_clock::now();
		PmergeMe mergeMe(input);
		printVec("Before: ", mergeMe.getInputNbrs());
		mergeMe.preSort();
		printVec("After: ", mergeMe.getNbrs());
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cout << "Time to process a range of " << mergeMe.getNbrs().size() << 
			" elements with std::vector: " << duration.count() << " us" << std::endl;
	}
	return 0;
}

bool runSortDeque(int argc, char *argv[])
{
	std::deque<unsigned int> input;
	if (!isValidInputDeque(argc, argv, input))
	return 1;
	else
	{
		auto start = std::chrono::high_resolution_clock::now();
		PmergeMeDeque mergeMe(input);
		// printVecDeque("Before: ", mergeMe.getInputNbrsDeque());
		mergeMe.preSortDeque();
		// printVecDeque("After: ", mergeMe.getNbrsDeque());
		// const std::deque<unsigned int>& vec_sorted = mergeMe.getNbrsDeque();
		// if (std::is_sorted(vec_sorted.begin(), vec_sorted.end()))
		// 	std::cout << "The deque is sorted in ascending order," << std::endl;
		// else
		// 	std::cout << "The deque is not sorted, " << std::endl;
		// std::cout << "using " << mergeMe.getCompsDeque() << " comparisons.\n";
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cout << "Time to process a range of " << mergeMe.getNbrsDeque().size() << 
			" elements with std::deque: " << duration.count() << " us" << std::endl;
	}
	return 0;
}

