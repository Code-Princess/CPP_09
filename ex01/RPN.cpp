/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:59:27 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/03 20:54:19 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>

#include "RPN.hpp"

RPN::RPN(const std::string& inputStr)
	:	_inputStr(inputStr)
{
}

RPN::~RPN()
{
}

std::stack<float>& RPN::getStack()
{
	return _nbrsStack;
}

void RPN::executeRPN()
{
	std::istringstream iss(_inputStr);
	std::string element;
	
	
	while (iss >> element)
	{
		if (element.size() == 1)
		{
			if (std::isdigit(element[0]))
				pushToStack(element);
			else if (!isOperator(element[0]))
				return;
			else if (isOperator(element[0]) && _nbrsStack.size() >= 2)
				processOpera(element[0]);
			else
			{
				std::cerr << "Error: not enough numbers" << std::endl;
				emptyTheStack();
			}
		}
		else
		{
			std::cerr << "Error: invalid input " << element << std::endl;
			emptyTheStack();
			return;
		}
	}
}

void RPN::printResult()
{
	if (_nbrsStack.size() == 1)
		std::cout << _nbrsStack.top() << std::endl;
	else if (_nbrsStack.size() > 1)
		std::cerr << "Error: not enough operators"<< std::endl;
	else if (_nbrsStack.size() == 0)
		std::cerr << "Error: no result"<< std::endl;
	else
	std::cerr << "Error"<< std::endl;
}

void RPN::pushToStack(std::string str)
{
	int nbr;
	try
	{
		nbr = std::stoi(str);
		_nbrsStack.push(nbr);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool RPN::isOperator(char c)
{
	for (int i = 0; i < 4; i++)
	{
		if (c == _operators[i])
			return true;
	}
	std::cerr << "Error: invalid input " << c << std::endl;
	emptyTheStack();
	return false;
}

void RPN::processOpera(char opera)
{
	float a,b;
	std::optional<float> c;
	
	b = _nbrsStack.top();
	_nbrsStack.pop();
	a = _nbrsStack.top();
	_nbrsStack.pop();
	c = calcOperation(a, b, opera);
	if (c != std::nullopt)
		_nbrsStack.push(c.value());
}

void RPN::emptyTheStack()
{
	while (!_nbrsStack.empty()) 
	{
		_nbrsStack.pop();
	}
}

void RPN::printStack()
{
	std::stack<float> stackCopy = _nbrsStack;
	std::cout << "Stack: ";
	while (!stackCopy.empty())
	{
		std::cout << stackCopy.top() << " ";
		stackCopy.pop();
	}
	std::cout << std::endl;
}

std::optional<float> calcOperation(float a, float b, char opera)
{
	std::optional<float> c;
	switch (opera)
	{
	case '+':
		c = a + b;
		break;
	case '-':
		c = a - b;
		break;
	case '*':
		c = a * b;
		break;
	case '/':
		if (b == 0)
		{
			std::cerr << "Error: division by zero" << std::endl;
			c = std::nullopt;
		}
		else
			c = a / b;
		break;
	default:
		c = std::nullopt;
		break;
	}
	return c;
}
