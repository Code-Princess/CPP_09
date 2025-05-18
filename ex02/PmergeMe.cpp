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

const std::vector<unsigned int>& PmergeMe::getNbrs() const
{
	return _nbrs;
}

std::vector<unsigned int> PmergeMe::getInputNbrs()
{
	return _inputNbrs;
}

void PmergeMe::preSort()
{
	_nbrs = _inputNbrs;
	int level = 0;
	createJacobsthalNbrs();
	sort(level);
}

void PmergeMe::sort(int level)
{
	// size_t elem_size = calcStartIdxForSwap(level) + 1;
	// size_t elem_size = 1 << level;
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements < 2)
		return;
		// if (_inputNbrs.size()/std::pow(2, level + 1) >= 1)
	// if (_inputNbrs.size() >= elem_size * 2)
	if (_nbrs.size() >= elem_size * 2)
	{
		std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
		std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
		std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs, level);
		concatVecs(pairwiseSorted, remainNbrs);
printVec("after pairwise sorting and concat: ", _nbrs);
		sort(level + 1);
	}

std::cout << "\n\nnow inserting\n" << "elem_size: " << elem_size << "\n";
// maybe should check if level is negative
	if (level < 0) return ;
	generate_a_b_remain_mainChain(level);
	printVec("_a: ", _a);
	printVec("_b: ", _b);
	printVec("_remain: ", _remain);
	printVec("_main_chain: ", _mainChain);



	// insert b1, no comparissons with a1!
	_mainChain.insert(_mainChain.begin(), _b.begin(), _b.begin() + elem_size);
	binInsertbToMainChain(elem_size);

	_mainChain.insert(_mainChain.end(), _remain.begin(), _remain.end());
	_nbrs = std::move(_mainChain);
printVec("_nbrs: ", _nbrs);
	_a.clear();
	_b.clear();
	_mainChain.clear();
	_remain.clear();
}

void PmergeMe::generate_a_b_remain_mainChain(int level)
{
	// size_t elem_size = calcStartIdxForSwap(level) + 1;
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements < 2)
		return;
	std::cout << "still alive!\n\n";
	int remainder = _nbrs.size() % elem_size;
	std::vector<unsigned int> trimNbrs(_nbrs.begin(), _nbrs.end() - remainder);
	_remain.assign(_nbrs.end() - remainder, _nbrs.end());
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
}

void PmergeMe::binInsertbToMainChain(size_t elem_size)
{
	for (size_t jacobIdx = 3; jacobIdx < _jacobsthalNbrs.size(); ++jacobIdx)
	{
		size_t bIdx = _jacobsthalNbrs[jacobIdx];
std::cout << "elem_size: " << elem_size << " bIdx: " << bIdx << "\n";
		while (true) {
			if (bIdx <= _jacobsthalNbrs[jacobIdx - 1])
				break ;
			if (bIdx * elem_size > _b.size()) 
			{
				bIdx--;
				continue ;
			}
std::cout << "bIdx: " << bIdx << "\n";
			size_t bIdxStart = elem_size * (bIdx - 1);
			std::vector<unsigned int> blockToInsert(_b.begin() + bIdxStart, _b.begin() + bIdxStart + elem_size);
			unsigned int nbrToComp = blockToInsert.back();
			size_t left = 0;
			size_t right = _mainChain.size() / elem_size;
			
			size_t insertPos = 0;
			
			while (left < right) 
			{
				size_t mid = (left + right) / 2;
				unsigned int midVal = _mainChain[(mid + 1) * elem_size - 1];
				if (nbrToComp < midVal) 
					right = mid;
				else 
					left = mid + 1;
			}
			
			insertPos = left * elem_size;
			_mainChain.insert(_mainChain.begin() + insertPos, blockToInsert.begin(), blockToInsert.end());
			bIdx--;
		}
	}
}



