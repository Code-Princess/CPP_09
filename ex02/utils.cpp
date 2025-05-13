/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:39:51 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 23:08:07 by llacsivy         ###   ########.fr       */
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
	// printVec("_jacobsthalNbrs", _jacobsthalNbrs);
}


