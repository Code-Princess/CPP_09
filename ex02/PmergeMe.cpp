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
	createJacobsthalNbrs();
	recursivePairCompSwap(level);

}

void PmergeMe::recursivePairCompSwap(int level)
{
	std::cout <<  std::endl << "level: " << level << std::endl;
	size_t elem_size = calcStartIdxForSwap(level) + 1;
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements < 2)
		return;
	if (_inputNbrs.size()/std::pow(2, level + 1) >= 1)
	{
			std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
			std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
			std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs, level);
			concatVecs(pairwiseSorted, remainNbrs);
		printVec("---_nbrs", _nbrs);
		recursivePairCompSwap(level + 1);
	}
	if (level != 0)
		generate_a_b_remain_mainChain(level - 1);
	
}

void PmergeMe::generate_a_b_remain_mainChain(int level)
{
	std::cout << std::endl << std::endl << "level: " << level << std::endl;
	size_t elem_size = calcStartIdxForSwap(level) + 1;
	std::cout << std::endl <<  "elem_size: " << elem_size << std::endl;
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements <= 2)
		return;
	int remainder = _nbrs.size() % elem_size;
	std::vector<unsigned int> trimNbrs(_nbrs.begin(), _nbrs.end() - remainder);
	_remain.assign(_nbrs.end() - remainder, _nbrs.end());
printVec("----trimNbrs", trimNbrs);
printVec("-----------------_remain", _remain);
	while (!trimNbrs.empty())
	{
		if (trimNbrs.size() >= elem_size)
		{	
			_b.insert(_b.end(), trimNbrs.begin(), trimNbrs.begin() + elem_size);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + elem_size);
		}
		if (trimNbrs.size() >= elem_size)
		{
			_a.insert(_a.end(), trimNbrs.begin(), trimNbrs.begin() + elem_size);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + elem_size);
		}
	}
	_mainChain = _a;
printVec("-----------------_a", _a);
printVec("-----------------_b", _b);
	_mainChain.insert(_mainChain.begin(), _b.begin(), _b.begin() + elem_size);
	// _b.erase(_b.begin(), _b.begin() + elem_size);
printVec("-----------------_b", _b);
printVec("-----------------_mainChain", _mainChain);
	binInsertbToMainChain(3, elem_size);
}

void PmergeMe::binInsertbToMainChain(int jacobIdx, size_t elem_size)
{
	if (_b.size() >= _jacobsthalNbrs[jacobIdx] * elem_size)
	{
		unsigned int nbrToComp = _b[_jacobsthalNbrs[jacobIdx] * elem_size - 1];
		if (nbrToComp)
		{
			/* code */
		}
		
		
	}

	// unsigned int JacobNbr = _jacobsthalNbrs[jacobIdx];
	
}


