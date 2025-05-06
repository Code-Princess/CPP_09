/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:44 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/06 18:17:33 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>

class PmergeMe {
private:
	std::vector<unsigned int> _inputNbrs;
	std::vector<unsigned int> _nbrs;
	std::vector<unsigned int> _jacobsthalNbrs;

	void createJacobsthalNbrs();
	void recursivePairCompSwap(int level);
	std::vector<unsigned int> trimToEvenCount(int level);
	std::vector<unsigned int> pairCompSwap(std::vector<unsigned int> vec, int level);
	void concatVecs(std::vector<unsigned int> vec1, std::vector<unsigned int> vec2);
	
public:
	PmergeMe() = delete;
	PmergeMe(const PmergeMe& other) = delete;
	PmergeMe& operator=(const PmergeMe& other) = delete;
	
	PmergeMe(std::vector<unsigned int> inputNbrs);
	~PmergeMe();
	std::vector<unsigned int> getNbrs();
	
	void sort();
	
};
void printVec(std::string vecName, std::vector<unsigned int> vec);

int calcStartIdxForSwap(int level);

#endif