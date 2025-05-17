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

printVec("-----------------_mainChain", _mainChain);
for (size_t i = 3; i < _jacobsthalNbrs.size(); ++i)
{
	binInsertbToMainChain(_jacobsthalNbrs[i], elem_size);
}	

}

void PmergeMe::binInsertbToMainChain(unsigned int jacobIdx, size_t elem_size)
{
	size_t bIdx = jacobIdx;
	size_t bIdxStart = elem_size * (bIdx - 1);

	std::vector<unsigned int> blockToInsert(_b.begin() + bIdxStart, _b.begin() + bIdxStart + elem_size);
	unsigned int nbrToComp = blockToInsert.back();
printVec("----------blockToInsert", blockToInsert);
	size_t left = 0;
    size_t right = _mainChain.size() / elem_size;

    size_t insertPos = 0;

	while (left < right) {
        size_t mid = (left + right) / 2;
        unsigned int midVal = _mainChain[(mid + 1) * elem_size - 1];

        if (nbrToComp < midVal) 
            right = mid;
    	else 
            left = mid + 1;
    }

	insertPos = left * elem_size;

    _mainChain.insert(_mainChain.begin() + insertPos, blockToInsert.begin(), blockToInsert.end());

    std::cout << "Inserted block at position: " << insertPos << std::endl;
    printVec(">>> Updated _mainChain", _mainChain);

	bIdx--;

std::cout << "bIdx: " << bIdx<< std::endl;
	
std::cout << "_jacobsthalNbrs[jacobIdx - 1]: " << _jacobsthalNbrs[jacobIdx - 1] << std::endl;
	if (bIdx > _jacobsthalNbrs[jacobIdx - 1])
	{
		binInsertbToMainChain(jacobIdx - 1, elem_size);
	}
}



