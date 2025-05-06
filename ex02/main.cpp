/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/05 22:20:08 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PmergeMe.hpp"

int main (int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	std::vector<unsigned int> input = {3, 5, 0, 9, 7, 1, 3, 7, 8, 2, 8};
	PmergeMe mergeMe(input);
	printVec("---Before", mergeMe.getNbrs());
	mergeMe.sort();
	return 0;
}