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
	(void)argc;
	(void)argv;

	auto start = std::chrono::high_resolution_clock::now();

	// std::vector<unsigned int> input = {3, 5, 0, 9, 7, 1, 3, 7, 8, 2, 8};
	std::vector<unsigned int> input = {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


	PmergeMe mergeMe(input);
	printVec("------------Before: ", mergeMe.getInputNbrs());
	mergeMe.sort();
	printVec("------------After: ", mergeMe.getNbrs());

	const std::vector<unsigned int>& vec_sorted = mergeMe.getNbrs();
	if (std::is_sorted(vec_sorted.begin(), vec_sorted.end()))
        std::cout << "The vector is sorted in ascending order." << std::endl;
    else
        std::cout << "The vector is not sorted." << std::endl;
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Time to process a range of " << mergeMe.getNbrs().size() << 
		" elements with std::vector: " << duration.count() << " us" << std::endl;
	return 0;
}