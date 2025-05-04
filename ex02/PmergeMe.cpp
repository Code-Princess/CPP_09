/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:35:33 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/04 21:31:40 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<unsigned int> inputNbrs)
	:	_inputNbrs(inputNbrs)
{
	
}
PmergeMe::~PmergeMe()
{
	
}

std::vector<unsigned int> PmergeMe::getNbrs()
{
	return _inputNbrs;
}

void PmergeMe::sort()
{
	std::vector<unsigned int> nbrsCopy = _inputNbrs;
printVec("nbrsCopy", nbrsCopy);
	std::vector<unsigned int> trimmedNbrs = trimToEvenCount(nbrsCopy);
printVec("trimmedNbrs", trimmedNbrs);
	std::vector<unsigned int> remainingNbrs(nbrsCopy.begin() + trimmedNbrs.size(), nbrsCopy.end());
printVec("remainingNbrs", remainingNbrs);
	std::vector<unsigned int> pairwiseSorted = pairCompSwap(trimmedNbrs);
printVec("pairwiseSorted", pairwiseSorted);
	nbrsCopy = concatVecs(pairwiseSorted, remainingNbrs);
printVec("nbrsCopy", nbrsCopy);


}

