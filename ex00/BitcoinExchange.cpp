/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:59 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/14 17:29:47 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	if (parseData("data.csv"))
		std::cout << "_data stored successfully" << std::endl;
	else
		std::cerr << "Error: parseData() failed." << std::endl;
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

bool openFile(const std::string& dataFile, 	std::ifstream& file)
{
	file.open(dataFile);
	if (!file.is_open())
	{
		std::cerr << "Error: open file  " << dataFile << " failed!" << std::endl;
		return false;
	}
	else
		return true;
}

bool BitcoinExchange::_parseLine(const std::string& nextLine)
{
	std::string			date;
	std::string			exchangeRateStr;
	double				exchangeRate;
	std::stringstream 	ss(nextLine);
	if (std::getline(ss, date, ',') && std::getline(ss, exchangeRateStr))
	{
		try
		{
			exchangeRate = std::stod(exchangeRateStr);
			_data.insert({date, exchangeRate});
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}
	}
	return true;
}

bool BitcoinExchange::parseData(const std::string dataFile)
{
	std::ifstream	file;
	std::string 	nextLine;
	bool			isFirstLine;
	
	isFirstLine = true;

	if (openFile(dataFile, file))
	{
		while (std::getline(file, nextLine))
		{
			if (isFirstLine)
			{
				isFirstLine = false;
				continue;	
			}
			if (!_parseLine(nextLine))
				std::cerr << "Error: parseLine() failed." << std::endl;
		}
		file.close();
		return true;
	}
	else
		return false;
}

/* bool BitcoinExchange::parseData(const std::string dataFile)
{
	std::string nextLine;
	bool		isFirstLine;
	std::string	date;
	std::string	exchangeRateStr;
	double		exchangeRate;
	
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
					exchangeRate = std::stod(exchangeRateStr);
					_data.insert({date, exchangeRate});
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << std::endl;
				}
			}
		}
		file.close();
		return true;
	}
} */

std::map<std::string, double> BitcoinExchange::getData()
{
	return _data;
}

void BitcoinExchange::_printData()
{
	std::cout << "_data:" << std::endl;
	for (const auto& pair : _data)
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << pair.first << ", " << pair.second << std::endl;
	}
}