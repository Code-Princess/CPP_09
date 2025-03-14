/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:37 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/14 18:44:09 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "BitcoinExchange.hpp"

int main (int argc, char* argv[])
{
(void)argv;
(void)argc;
	// if (argc != 2)
	// {
	// 	std::cerr << "Error: please enter ./btc <input.txt>." << std::endl;
	// 	return 1;
	// }
	// else
	// {
	// 	BitcoinExchange btc(argv[1]);
	// }
	// return 0;

	BitcoinExchange btc("input.txt");
	btc.readInputLineByLine();
	return 0;
}