/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:39:51 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/19 22:02:25 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

void PmergeMe::createJacobsthalNbrs()
{
	size_t nextNbr = 0;
	size_t i = 2;
	_jacobsthalNbrs.push_back(0);
	_jacobsthalNbrs.push_back(1);
	while (true)
	{
		nextNbr = _jacobsthalNbrs[i - 2] * 2 + _jacobsthalNbrs[i - 1];

			if (nextNbr > _inputNbrs.size())
				break;
			_jacobsthalNbrs.push_back(nextNbr);
			i++;
		}
}

bool isPositiveInteger(const std::string& str) 
{
    if (str.empty()) 
		return false;
    for (char c : str) {
        if (!std::isdigit(c)) 
			return false;
    }
    return true;
}

bool isValidInput(int argc, char* argv[], std::vector<unsigned int>& input)
{
	if (argc < 2)
	{
		std::cerr << "Error: invalid input! Expect numbers!" << std::endl;
        return false;
	}
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (!isPositiveInteger(arg)) 
		{
			std::cerr << "Error: invalid input '" << arg << "'. Only positive integers are allowed." << std::endl;
            return false;
		}	
		try 
		{
			unsigned long val = std::stoul(arg);
			if (val > std::numeric_limits<unsigned int>::max()) 
			{
				std::cerr << "Error: Value '" << arg << "' exceeds unsigned int limit." << std::endl;
				return false;
			}
			input.push_back(static_cast<unsigned int>(val));
		} 
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return true;
}
