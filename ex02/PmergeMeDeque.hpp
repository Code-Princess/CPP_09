/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeDeque.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:34:44 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/20 21:24:48 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEMEDEQUE_HPP
#define PMERGEMEDEQUE_HPP

#include <deque>

class PmergeMeDeque {
private:
	std::deque<unsigned int> 	_inputNbrsDeque;
	std::deque<unsigned int> 	_nbrsDeque;
	std::deque<unsigned int> 	_jacobsthalNbrsDeque;
	std::deque<unsigned int> 	_mainChainDeque;
	std::deque<unsigned int> 	_aDeque;
	std::deque<unsigned int> 	_bDeque;
	std::deque<unsigned int> 	_remainDeque;
	std::deque<unsigned int>	_a_idxsDeque;
	int							_compsDeque{0};


	void createJacobsthalNbrsDeque();
	void sortDeque(int level);
	std::deque<unsigned int> trimToEvenCountDeque(int level);
	std::deque<unsigned int> pairCompSwapDeque(std::deque<unsigned int> vec, int level);
	void concatVecsDeque(std::deque<unsigned int> vec1, std::deque<unsigned int> vec2);
	std::deque<unsigned int> concatVecs2Deque(std::deque<unsigned int> vec1, \
		std::deque<unsigned int> vec2);
	void generate_a_b_remain_mainChainDeque(int level);
	void generate_a_idxsDeque(unsigned int number_elements);
	void binInsertbToMainChainDeque(size_t elem_size);
	size_t	findInsertPositionDeque(size_t bIdx, unsigned int nbrToComp, size_t elem_size);
	void 	update_a_idxsDeque(int insertPos);

public:
	PmergeMeDeque() = delete;
	PmergeMeDeque(const PmergeMeDeque& other) = delete;
	PmergeMeDeque& operator=(const PmergeMeDeque& other) = delete;
	
	PmergeMeDeque(std::deque<unsigned int> inputNbrs);
	~PmergeMeDeque();

	std::deque<unsigned int> getInputNbrsDeque();
	const std::deque<unsigned int>& getNbrsDeque() const;
	int	getCompsDeque();
	void preSortDeque();
};

void printVecDeque(std::string vecName, std::deque<unsigned int> vec);
int calcStartIdxForSwapDeque(int level);
bool isPositiveIntegerDeque(const std::string& str);
bool isValidInputDeque(int argc, char* argv[], std::deque<unsigned int>& input);
bool runSortDeque(int argc, char *argv[]);

#endif