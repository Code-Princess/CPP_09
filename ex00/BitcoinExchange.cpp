/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:59 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/13 23:47:31 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	if (parseData("data.csv", _data) == false)
		return ;
}

// BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
// {
	
// }
// BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
// {
	
// }
	
BitcoinExchange::~BitcoinExchange()
{
}

bool BitcoinExchange::parseData(const std::string dataFile, std::map<std::string, float> _data)
{
	std::string nextLine;
	bool		isFirstLine;
	std::string	date;
	std::string	exchangeRateStr;
	float		exchangeRate;
	
	isFirstLine = true;
	std::ifstream file(dataFile);
	if (!file.is_open())
	{
		std::cerr << "Error: open file  " << dataFile << " failed!" << std::endl;
		return false;
	}
	else
	{
		while (std::getline(file, nextLine))
		{
			if (isFirstLine)
			{
				isFirstLine = false;
				continue;	
			}
			std::stringstream ss(nextLine);
			if (std::getline(ss, date, ',') && std::getline(ss, exchangeRateStr))
			{
				try
				{
					exchangeRate = std::stof(exchangeRateStr);
					_data.insert({date, exchangeRate});
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
			
		}
		file.close();
	}
	return true;
}

// std::map<std::string, float> getDatabase()
// {
// 	// return _data;
// }
