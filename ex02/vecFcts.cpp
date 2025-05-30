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

#include "PmergeMe.hpp"

void printVec(std::string vecName, std::vector<unsigned int> vec)
{
	std::cout << vecName;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<unsigned int> PmergeMe::trimToEvenCount(int level)
{
	int modulus = static_cast<int>(std::pow(2, level + 1));
	float remainder;
	remainder = _nbrs.size() % modulus;
	std::vector<unsigned int> trimmedVec(_nbrs.begin(), _nbrs.end() - remainder);
	return trimmedVec;
}

int calcStartIdxForSwap(int level)
{
	int idx = 0;
	for (int i = 0; i < level; i++)
	{
		idx += static_cast<int>(std::pow(2, i));
	}
	return idx;
}

std::vector<unsigned int> PmergeMe::pairCompSwap(std::vector<unsigned int> vec, int level)
{
	int stepWidth = static_cast<int>(std::pow(2, level));
	int	idxSwap = calcStartIdxForSwap(level);
	for (size_t i = idxSwap; i + stepWidth <= vec.size(); i += (2 * stepWidth))
	{
		_comps++;
		if (vec[i] > vec[i + stepWidth])
			std::swap_ranges(vec.begin() + i - (stepWidth - 1), vec.begin() + i + 1, vec.begin() + i + 1);
	}
	return vec;
}

void PmergeMe::concatVecs(std::vector<unsigned int> vec1, \
	std::vector<unsigned int> vec2)
{
	_nbrs = vec1;
	_nbrs.insert(_nbrs.end(), vec2.begin(), vec2.end());
}

std::vector<unsigned int> PmergeMe::concatVecs2(std::vector<unsigned int> vec1, \
	std::vector<unsigned int> vec2)
{
	std::vector<unsigned int> concVec = vec1;
	concVec.insert(concVec.end(), vec2.begin(), vec2.end());
	return concVec;
}
