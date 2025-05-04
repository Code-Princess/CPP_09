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

#include "PmergeMe.hpp"

void printVec(std::string vecName, std::vector<unsigned int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << vecName;
	std::cout << std::endl;
}
std::vector<unsigned int> trimToEvenCount(std::vector<unsigned int> vec)
{
	size_t remainder;
	remainder = vec.size() % 2;
	std::vector<unsigned int> trimmedVec(vec.begin(), vec.end() - remainder);
	return trimmedVec;
}
std::vector<unsigned int> pairCompSwap(std::vector<unsigned int> vec)
{
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
	}
	return vec;
}
std::vector<unsigned int> concatVecs(std::vector<unsigned int> vec1, \
	std::vector<unsigned int> vec2)
{
	std::vector<unsigned int> resultVec = vec1;
	resultVec.insert(resultVec.end(), vec2.begin(), vec2.end());
	return resultVec;
}


