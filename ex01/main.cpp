/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/03 20:55:55 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "RPN.hpp"

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid input! Please enter ./RPN \"reverse polish notation\""<< std::endl \
			<< "Example: ./RPN \"8 9 * 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
		return 1;
	}
	else
	{
		const std::string inputStr = argv[1];
		RPN rpn(inputStr);
		rpn.executeRPN();
		if (!rpn.getStack().empty())
			rpn.printResult();
	}
	return 0;
}