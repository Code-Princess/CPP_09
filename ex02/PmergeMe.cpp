/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 22:38:58 by llacsivy         ###   ########.fr       */
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
	// _nbrs = _inputNbrs;
	// int level = 0;
	// recursivePairCompSwap(level);

	createJacobsthalNbrs();

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

	std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
printVec("----trimNbrs", trimNbrs);

	int idxbEnd = calcStartIdxForSwap(level) + 1;
std::cout << "idxbEnd: " << idxbEnd << "\n";
	_b.assign(trimNbrs.begin(), trimNbrs.begin() + idxbEnd);
	_a.assign(trimNbrs.begin() + idxbEnd, trimNbrs.end());

printVec("-----------------_a", _a);
printVec("-----------------_b", _b);

	_mainChain = concatVecs2(_b, _a);
printVec("-----------------_mainChain", _mainChain);


	
}
