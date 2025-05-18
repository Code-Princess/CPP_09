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

int	PmergeMe::getComps() {
	return _comps;
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
// printVec("after pairwise sorting and concat: ", _nbrs);
		sort(level + 1);
	}

std::cout << "\n\nnow inserting\n" << "elem_size: " << elem_size << "\n";
// maybe should check if level is negative
	if (level < 0) return ;
	generate_a_b_remain_mainChain(level);
	printVec("_a: ", _a);
	printVec("_b: ", _b);
	// printVec("_remain: ", _remain);
	printVec("_main_chain: ", _mainChain);

	generate_a_idxs(_a.size() / elem_size);
// printVec("_a_idxs: ", _a_idxs);

	// insert b1, no comparissons with a1!
	_mainChain.insert(_mainChain.begin(), _b.begin(), _b.begin() + elem_size);
	update_a_idxs(0);
	printVec("after update: _a_idxs: ", _a_idxs);
	printVec("_main_chain: ", _mainChain);
	binInsertbToMainChain(elem_size);

	_mainChain.insert(_mainChain.end(), _remain.begin(), _remain.end());
	_nbrs = std::move(_mainChain);
// printVec("_nbrs: ", _nbrs);
	_a.clear();
	_b.clear();
	_mainChain.clear();
	_remain.clear();
	_a_idxs.clear();
}

void PmergeMe::generate_a_b_remain_mainChain(int level)
{
	// size_t elem_size = calcStartIdxForSwap(level) + 1;
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements < 2)
		return;
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

void	PmergeMe::generate_a_idxs(unsigned int number_elements) {
	for (unsigned int i = 0; i <= number_elements; i++) {
		_a_idxs.push_back(i);
	}
	_a_idxs.push_back(_a_idxs.back());
}


void PmergeMe::binInsertbToMainChain(size_t elem_size)
{
	for (size_t jacobIdx = 3; jacobIdx < _jacobsthalNbrs.size(); ++jacobIdx)
	{
		size_t bIdx = _jacobsthalNbrs[jacobIdx];
// std::cout << "elem_size: " << elem_size << " bIdx: " << bIdx << "\n";
		while (true) {
			if (bIdx <= _jacobsthalNbrs[jacobIdx - 1]){
				// std::cout << "bIdx: " << bIdx << " - > break!\n";
				break ;
			}
			if (bIdx * elem_size > _b.size()) 
			{
				// std::cout << "bIdx: " << bIdx << " - > continue!\n";
				bIdx--;
				continue ;
			}
// std::cout << "__bIdx: " << bIdx << "\n";
			size_t bIdxStart = elem_size * (bIdx - 1);
			std::vector<unsigned int> blockToInsert(_b.begin() + bIdxStart, _b.begin() + bIdxStart + elem_size);
			unsigned int nbrToComp = blockToInsert.back();

			// int insertPos = findInsertPosition(bIdx, elem_size);
			int insertPos = findInsertPosition(bIdx, nbrToComp, elem_size);

			// size_t left = 0;
			// size_t right = _mainChain.size() / elem_size;
			
			// size_t insertPos = 0;
			
			// while (left < right) 
			// {
			// 	size_t mid = (left + right) / 2;
			// 	unsigned int midVal = _mainChain[(mid + 1) * elem_size - 1];
			// 	_comps++;
			// 	if (nbrToComp < midVal) 
			// 		right = mid;
			// 	else 
			// 		left = mid + 1;
			// }
			// insertPos = left * elem_size;
			
			_mainChain.insert(_mainChain.begin() + insertPos, blockToInsert.begin(), blockToInsert.end());
			update_a_idxs(insertPos / elem_size);
			std::cout << "insertPos: " << insertPos << "\n";
			std::cout << "insertPos / elem_size: " << insertPos / elem_size << "\n";
			printVec("after update: _a_idxs: ", _a_idxs);
			printVec("_main_chain: ", _mainChain);
			bIdx--;
		}
	}
}

size_t	PmergeMe::findInsertPosition(size_t bIdx, unsigned int nbrToComp, size_t elem_size) {
// size_t	PmergeMe::findInsertPosition(size_t bIdx, size_t elem_size) {
		// (void)bIdx;
	// unsigned int nbrToComp = _b[bIdx * elem_size];
	size_t left = 0;
	// size_t right = _mainChain.size() / elem_size;
	size_t right = _a_idxs[bIdx] - 1;
	if (_a_idxs.size() - 2 < bIdx) {
		right = _a_idxs[bIdx];
	}
	// std::cout << "bIdx: " << bIdx << "\n";
	// std::cout << "_a_idxs[bIdx]: " << _a_idxs[bIdx] << "\n";
	// std::cout << "right: " << right << "\n";
	
	// size_t insertPos = 0;
	
	while (left < right) 
	{
		size_t mid = (left + right) / 2;
		unsigned int midVal = _mainChain[(mid + 1) * elem_size - 1];
		// std::cout << "still alive!\n\n";
		_comps++;
		if (nbrToComp < midVal) 
			right = mid;
		else 
			left = mid + 1;
	}
	return left * elem_size;
}

void 	PmergeMe::update_a_idxs(int insertPos) {
	for (auto& el : _a_idxs) {
		if (static_cast<int>(el) > insertPos) el++;
		// if (static_cast<int>(el) > insertPos) el++;
	}
}
