/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:59:21 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/03 20:54:42 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <optional>

class RPN{
private:
	std::stack<float> _nbrsStack;
	std::string _inputStr;
	char _operators[4] = {'+', '-', '/', '*'};

	void pushToStack(std::string str);
	bool isOperator(char c);
	void processOpera(char opera);
	void emptyTheStack();
	void printStack();
public:
	RPN() = delete;
	RPN(const RPN& other) = delete;
	RPN& operator=(const RPN& other) = delete;
	
	RPN(const std::string& inputStr);
	~RPN();
	std::stack<float>& getStack();

	void executeRPN();
	void printResult();
};

std::optional<float> calcOperation(float a, float b, char opera);

#endif