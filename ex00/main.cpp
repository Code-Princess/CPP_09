/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/04/30 19:35:43 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "BitcoinExchange.hpp"

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid input! Please enter ./btc <input.txt>." << std::endl;
		return 1;
	}
	else
	{
		const std::string inputFile = argv[1];
		try
		{
			BitcoinExchange btc("data.csv");
			btc.executeTurnOver(inputFile);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
	return 0;
}