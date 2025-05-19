/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/19 22:02:01 by llacsivy         ###   ########.fr       */
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
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrs.size() / elem_size;
	if (number_elements < 2)
		return;
	if (_nbrs.size() >= elem_size * 2)
	{
		std::vector<unsigned int> trimNbrs = trimToEvenCount(level);
		std::vector<unsigned int> remainNbrs(_nbrs.begin() + trimNbrs.size(), _nbrs.end());
		std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimNbrs, level);
		concatVecs(pairwiseSorted, remainNbrs);
		sort(level + 1);
	}
	if (level < 0) 
		return ;
	generate_a_b_remain_mainChain(level);
	generate_a_idxs(_a.size() / elem_size);
	_mainChain.insert(_mainChain.begin(), _b.begin(), _b.begin() + elem_size);
	update_a_idxs(0);
	binInsertbToMainChain(elem_size);
	_mainChain.insert(_mainChain.end(), _remain.begin(), _remain.end());
	_nbrs = std::move(_mainChain);
	_a.clear();
	_b.clear();
	_mainChain.clear();
	_remain.clear();
	_a_idxs.clear();
}

void PmergeMe::generate_a_b_remain_mainChain(int level)
{
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

void	PmergeMe::generate_a_idxs(unsigned int number_elements) 
{
	for (unsigned int i = 0; i <= number_elements; i++) 
	{
		_a_idxs.push_back(i);
	}
	_a_idxs.push_back(_a_idxs.back());
}

void PmergeMe::binInsertbToMainChain(size_t elem_size)
{
	for (size_t jacobIdx = 3; jacobIdx < _jacobsthalNbrs.size(); ++jacobIdx)
	{
		size_t bIdx = _jacobsthalNbrs[jacobIdx];
		while (true) {
			if (bIdx <= _jacobsthalNbrs[jacobIdx - 1])
				break ;
			if (bIdx * elem_size > _b.size()) 
			{
				bIdx--;
				continue ;
			}
			size_t bIdxStart = elem_size * (bIdx - 1);
			std::vector<unsigned int> blockToInsert(_b.begin() + bIdxStart, _b.begin() + bIdxStart + elem_size);
			unsigned int nbrToComp = blockToInsert.back();
			int insertPos = findInsertPosition(bIdx, nbrToComp, elem_size);
			_mainChain.insert(_mainChain.begin() + insertPos, blockToInsert.begin(), blockToInsert.end());
			update_a_idxs(insertPos / elem_size);
			bIdx--;
		}
	}
}

size_t	PmergeMe::findInsertPosition(size_t bIdx, unsigned int nbrToComp, size_t elem_size) {
	size_t left = 0;
	size_t right = _a_idxs[bIdx] - 1;
	if (_a_idxs.size() - 2 < bIdx) 
	{
		right = _a_idxs[bIdx];
	}
	while (left < right) 
	{
		size_t mid = (left + right) / 2;
		unsigned int midVal = _mainChain[(mid + 1) * elem_size - 1];
		_comps++;
		if (nbrToComp < midVal) 
			right = mid;
		else 
			left = mid + 1;
	}
	return left * elem_size;
}

void 	PmergeMe::update_a_idxs(int insertPos) 
{
	for (auto& el : _a_idxs) 
	{
		if (static_cast<int>(el) > insertPos)
			el++;
	}
}

