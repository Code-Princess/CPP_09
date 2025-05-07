/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 19:12:08 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<unsigned int> inputNbrs)
	:	_inputNbrs(inputNbrs)
{
	
}
PmergeMe::~PmergeMe()
{
	
}

std::vector<unsigned int> PmergeMe::getNbrs()
{
	return _inputNbrs;
}

void PmergeMe::sort()
{
	_nbrs = _inputNbrs;
// printVec("---_nbrs", _nbrs);
// 	std::vector<unsigned int> trimNbrs = trimToEvenCount(_nbrs);
// printVec("---trimNbrs", trimNbrs);
// 	std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
// printVec("---remainNbrs", remainNbrs);
// 	std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs);
// printVec("---pairwiseSorted", pairwiseSorted);
// 	_nbrs = concatVecs(pairwiseSorted, remainNbrs);
// printVec("---_nbrs", _nbrs);
int level = 0;
recursivePairCompSwap(level);
// printVec("---pairSortedNbrs", pairSortedNbrs);


}
void PmergeMe::recursivePairCompSwap(int level)
{
	std::cout << "level: " << level << std::endl;
	if (_inputNbrs.size()/std::pow(2, level + 1) >= 2)
	{
		// printVec("---_nbrs", _nbrs);
			std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
		printVec("----trimNbrs", trimNbrs);
			std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
		printVec("----------------------remainNbrs", remainNbrs);
			std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs, level);
		printVec("---pairwiseSorted", pairwiseSorted);
			concatVecs(pairwiseSorted, remainNbrs);
		printVec("---_nbrs", _nbrs);
		recursivePairCompSwap(++level);
	}
	
}