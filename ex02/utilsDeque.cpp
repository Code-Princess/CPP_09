/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsDeque.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:39:51 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/20 20:14:41 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeDeque.hpp"
#include <iostream>

void PmergeMeDeque::createJacobsthalNbrsDeque()
{
	size_t nextNbr = 0;
	size_t i = 2;
	_jacobsthalNbrsDeque.push_back(0);
	_jacobsthalNbrsDeque.push_back(1);
	while (true)
	{
		nextNbr = _jacobsthalNbrsDeque[i - 2] * 2 + _jacobsthalNbrsDeque[i - 1];

			if (nextNbr > _inputNbrsDeque.size())
				break;
			_jacobsthalNbrsDeque.push_back(nextNbr);
			i++;
		}
}

bool isPositiveIntegerDeque(const std::string& str) 
{
    if (str.empty()) 
		return false;
    for (char c : str) {
        if (!std::isdigit(c)) 
			return false;
    }
    return true;
}

bool isValidInputDeque(int argc, char* argv[], std::deque<unsigned int>& input)
{
	if (argc < 2)
	{
		std::cerr << "Error: invalid input! Expect numbers!" << std::endl;
        return false;
	}
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (!isPositiveIntegerDeque(arg)) 
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
