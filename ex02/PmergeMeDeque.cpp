/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeDeque.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/20 20:13:28 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

#include "PmergeMeDeque.hpp"

PmergeMeDeque::PmergeMeDeque(std::deque<unsigned int> inputNbrs)
	:	_inputNbrsDeque(inputNbrs)
{
}

PmergeMeDeque::~PmergeMeDeque()
{
}

const std::deque<unsigned int>& PmergeMeDeque::getNbrsDeque() const
{
	return _nbrsDeque;
}

std::deque<unsigned int> PmergeMeDeque::getInputNbrsDeque()
{
	return _inputNbrsDeque;
}

int	PmergeMeDeque::getCompsDeque() {
	return _compsDeque;
}


void PmergeMeDeque::preSortDeque()
{
	_nbrsDeque = _inputNbrsDeque;
	int level = 0;
	createJacobsthalNbrsDeque();
	sortDeque(level);
}

void PmergeMeDeque::sortDeque(int level)
{
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrsDeque.size() / elem_size;
	if (number_elements < 2)
		return;
	if (_nbrsDeque.size() >= elem_size * 2)
	{
		std::deque<unsigned int> trimNbrs = trimToEvenCountDeque(level);
		std::deque<unsigned int> remainNbrs(_nbrsDeque .begin() + trimNbrs.size(), _nbrsDeque.end());
		std::deque<unsigned int> pairwiseSorted = pairCompSwapDeque(trimNbrs, level);
		concatVecsDeque(pairwiseSorted, remainNbrs);
		sortDeque(level + 1);
	}
	if (level < 0) 
		return ;
	generate_a_b_remain_mainChainDeque(level);
	generate_a_idxsDeque(_aDeque.size() / elem_size);
	_mainChainDeque.insert(_mainChainDeque.begin(), _bDeque.begin(), _bDeque.begin() + elem_size);
	update_a_idxsDeque(0);
	binInsertbToMainChainDeque(elem_size);
	_mainChainDeque.insert(_mainChainDeque.end(), _remainDeque.begin(), _remainDeque.end());
	_nbrsDeque = std::move(_mainChainDeque);
	_aDeque.clear();
	_bDeque.clear();
	_mainChainDeque.clear();
	_remainDeque.clear();
	_a_idxsDeque.clear();
}

void PmergeMeDeque::generate_a_b_remain_mainChainDeque(int level)
{
	size_t elem_size = std::pow(2, level);
	size_t number_elements = _nbrsDeque.size() / elem_size;
	if (number_elements < 2)
		return;
	int remainder = _nbrsDeque.size() % elem_size;
	std::deque<unsigned int> trimNbrs(_nbrsDeque.begin(), _nbrsDeque.end() - remainder);
	_remainDeque.assign(_nbrsDeque.end() - remainder, _nbrsDeque.end());
	while (!trimNbrs.empty())
	{
		if (trimNbrs.size() >= elem_size)
		{	
			_bDeque.insert(_bDeque.end(), trimNbrs.begin(), trimNbrs.begin() + elem_size);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + elem_size);
		}
		if (trimNbrs.size() >= elem_size)
		{
			_aDeque.insert(_aDeque.end(), trimNbrs.begin(), trimNbrs.begin() + elem_size);
			trimNbrs.erase(trimNbrs.begin(), trimNbrs.begin() + elem_size);
		}
	}
	_mainChainDeque = _aDeque;
}

void	PmergeMeDeque::generate_a_idxsDeque(unsigned int number_elements) 
{
	for (unsigned int i = 0; i <= number_elements; i++) 
	{
		_a_idxsDeque.push_back(i);
	}
	_a_idxsDeque.push_back(_a_idxsDeque.back());
}

void PmergeMeDeque::binInsertbToMainChainDeque(size_t elem_size)
{
	for (size_t jacobIdx = 3; jacobIdx < _jacobsthalNbrsDeque.size(); ++jacobIdx)
	{
		size_t bIdx = _jacobsthalNbrsDeque[jacobIdx];
		while (true) {
			if (bIdx <= _jacobsthalNbrsDeque[jacobIdx - 1])
				break ;
			if (bIdx * elem_size > _bDeque.size()) 
			{
				bIdx--;
				continue ;
			}
			size_t bIdxStart = elem_size * (bIdx - 1);
			std::deque<unsigned int> blockToInsertDeque(_bDeque.begin() + bIdxStart, _bDeque.begin() + bIdxStart + elem_size);
			unsigned int nbrToComp = blockToInsertDeque.back();
			int insertPos = findInsertPositionDeque(bIdx, nbrToComp, elem_size);
			_mainChainDeque.insert(_mainChainDeque.begin() + insertPos, blockToInsertDeque.begin(), blockToInsertDeque.end());
			update_a_idxsDeque(insertPos / elem_size);
			bIdx--;
		}
	}
}

size_t	PmergeMeDeque::findInsertPositionDeque(size_t bIdx, unsigned int nbrToComp, size_t elem_size) {
	size_t left = 0;
	size_t right = _a_idxsDeque[bIdx] - 1;
	if (_a_idxsDeque.size() - 2 < bIdx) 
	{
		right = _a_idxsDeque[bIdx];
	}
	while (left < right) 
	{
		size_t mid = (left + right) / 2;
		unsigned int midVal = _mainChainDeque[(mid + 1) * elem_size - 1];
		_compsDeque++;
		if (nbrToComp < midVal) 
			right = mid;
		else 
			left = mid + 1;
	}
	return left * elem_size;
}

void 	PmergeMeDeque::update_a_idxsDeque(int insertPos) 
{
	for (auto& el : _a_idxsDeque) 
	{
		if (static_cast<int>(el) > insertPos)
			el++;
	}
}

