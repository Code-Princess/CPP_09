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
	_nbrs = _inputNbrs;
	int level = 0;
	recursivePairCompSwap(level);
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
	int remainder = _nbrs.size() % 2;
	std::vector<unsigned int> trimNbrs(_nbrs.begin(), _nbrs.end() - remainder);
	_remain.assign(_nbrs.end() - remainder, _nbrs.end());
printVec("----trimNbrs", trimNbrs);
	while (!trimNbrs.empty())
	{
		if (trimNbrs.size() >= 2)
		{	_b.insert(_b.end(), trimNbrs.begin(), trimNbrs.begin() + 2);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + 2);
		}
		if (trimNbrs.size() >= 2)
		{
			_a.insert(_a.end(), trimNbrs.begin(), trimNbrs.begin() + 2);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + 2);
		}
	}
	_mainChain = _a;
	printVec("-----------------_a", _a);
	printVec("-----------------_b", _b);
	printVec("-----------------_remain", _remain);
	printVec("-----------------_mainChain", _mainChain);
	std::cout << "DEBUG _jacobsthalNbrs.size: " << _jacobsthalNbrs.size() << std::endl;
for (size_t i = 2; i < _jacobsthalNbrs.size(); i++)
{
	if (i == 2)
	{
		_mainChain.insert(_mainChain.begin(), _b.begin(), _b.begin() + 2);
		_b.erase(_b.begin(), _b.begin() + 2);
		printVec("DEBUG-----------------_a", _a);
		printVec("-----------------_b", _b);
		printVec("-----------------_remain", _remain);
		printVec("-----------------_mainChain", _mainChain);
	}
	std::cout << "_jacobsthalNbrs: " << _jacobsthalNbrs[i] << std::endl;
}

	
	
// 	int idxbEnd = calcStartIdxForSwap(level) + 1;
// std::cout << "idxbEnd: " << idxbEnd << "\n";

// 	_b.assign(trimNbrs.begin(), trimNbrs.begin() + idxbEnd);
// 	_a.assign(trimNbrs.begin() + idxbEnd, trimNbrs.end());






	// binInsertMainChain(level - 1);
}
