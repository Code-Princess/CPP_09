/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecFcts.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:59:57 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/04 20:56:16 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

#include "PmergeMeDeque.hpp"

void printVecDeque(std::string vecName, std::deque<unsigned int> vec)
{
	std::cout << vecName;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

std::deque<unsigned int> PmergeMeDeque::trimToEvenCountDeque(int level)
{
	int modulus = static_cast<int>(std::pow(2, level + 1));
	float remainder;
	remainder = _nbrsDeque.size() % modulus;
	std::deque<unsigned int> trimmedVec(_nbrsDeque.begin(), _nbrsDeque.end() - remainder);
	return trimmedVec;
}

int calcStartIdxForSwapDeque(int level)
{
	int idx = 0;
	for (int i = 0; i < level; i++)
	{
		idx += static_cast<int>(std::pow(2, i));
	}
	return idx;
}

std::deque<unsigned int> PmergeMeDeque::pairCompSwapDeque(std::deque<unsigned int> vec, int level)
{
	int stepWidth = static_cast<int>(std::pow(2, level));
	int	idxSwap = calcStartIdxForSwapDeque(level);
	for (size_t i = idxSwap; i + stepWidth <= vec.size(); i += (2 * stepWidth))
	{
		_compsDeque++;
		if (vec[i] > vec[i + stepWidth])
			std::swap_ranges(vec.begin() + i - (stepWidth - 1), vec.begin() + i + 1, vec.begin() + i + 1);
	}
	return vec;
}

void PmergeMeDeque::concatVecsDeque(std::deque<unsigned int> vec1, \
	std::deque<unsigned int> vec2)
{
	_nbrsDeque = vec1;
	_nbrsDeque.insert(_nbrsDeque.end(), vec2.begin(), vec2.end());
}

std::deque<unsigned int> PmergeMeDeque::concatVecs2Deque(std::deque<unsigned int> vec1, \
	std::deque<unsigned int> vec2)
{
	std::deque<unsigned int> concVec = vec1;
	concVec.insert(concVec.end(), vec2.begin(), vec2.end());
	return concVec;
}
