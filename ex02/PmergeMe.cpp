/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 21:32:51 by llacsivy         ###   ########.fr       */
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
	int level = 0;
	recursivePairCompSwap(level);
}

void PmergeMe::recursivePairCompSwap(int level)
{
	std::cout <<  std::endl << "level: " << level << std::endl;
	if (_inputNbrs.size()/std::pow(2, level + 1) >= 1)
	{
			std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
		// printVec("----trimNbrs", trimNbrs);
			std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
		// printVec("----------------------remainNbrs", remainNbrs);
			std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs, level);
		// printVec("---pairwiseSorted", pairwiseSorted);
			concatVecs(pairwiseSorted, remainNbrs);
		printVec("---_nbrs", _nbrs);
		recursivePairCompSwap(level + 1);
	}
	binInsertMainChain(level - 1);
}

void PmergeMe::binInsertMainChain(int level)
{
std::cout << std::endl << std::endl << "level: " << level << std::endl;

	int idxbEnd = calcStartIdxForSwap(level) + 1;
std::cout << "idxbEnd: " << idxbEnd << "\n";
	_b.assign(_nbrs.begin(), _nbrs.begin() + idxbEnd);
	_a.assign(_nbrs.begin() + idxbEnd, _nbrs.end());

printVec("-----------------_a", _a);
printVec("-----------------_b", _b);

}
