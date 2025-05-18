/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:44 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/07 22:29:45 by llacsivy         ###   ########.fr       */
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
	std::vector<unsigned int> _mainChain;
	std::vector<unsigned int> _a;
	std::vector<unsigned int> _b;
	std::vector<unsigned int> _remain;


	void createJacobsthalNbrs();
	void pairCompSwap(int level);
	std::vector<unsigned int> trimToEvenCount(int level);
	std::vector<unsigned int> pairCompSwap(std::vector<unsigned int> vec, int level);
	void concatVecs(std::vector<unsigned int> vec1, std::vector<unsigned int> vec2);
	std::vector<unsigned int> concatVecs2(std::vector<unsigned int> vec1, \
		std::vector<unsigned int> vec2);
	void generate_a_b_remain_mainChain(int level);
	void binInsertbToMainChain(size_t elem_size);
	
public:
	PmergeMe() = delete;
	PmergeMe(const PmergeMe& other) = delete;
	PmergeMe& operator=(const PmergeMe& other) = delete;
	
	PmergeMe(std::vector<unsigned int> inputNbrs);
	~PmergeMe();
	std::vector<unsigned int> getInputNbrs();

	const std::vector<unsigned int>& getNbrs() const;
	
	void sort();
	
};
void printVec(std::string vecName, std::vector<unsigned int> vec);
int calcStartIdxForSwap(int level);

#endif