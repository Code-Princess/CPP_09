/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:59 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/14 22:51:32 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	
}

BitcoinExchange::BitcoinExchange(const std::string inputFile)
	:	_inputFile(inputFile)
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

// std::string BitcoinExchange::getInputDate()
// {
// 	return _inputDate;
// }

// float BitcoinExchange::getInputValue()
// {
// 	return _inputValue;
// }

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

bool BitcoinExchange::_parseDataLine(const std::string& nextLine)
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
			std::cerr << "Exception caught: " << e.what() << std::endl;
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
			if (!_parseDataLine(nextLine))
				std::cerr << "Error: parseLine() failed" << std::endl;
		}
		file.close();
		return true;
	}
	else
		return false;
}

std::map<std::string, double> BitcoinExchange::getData()
{
	return _data;
}

template <typename T>
bool BitcoinExchange::_isInRange(T value)
{
	if (value >= 0 && value <= 1000)
	{
		return true;
	}
	else
	{
		std::cerr << "Error: " << value << " not in range [0, 1000]" << std::endl;
		_inputValue = std::nan("");
if (std::isnan(_inputValue)) _printInput();
		return false;
	}
	
}

bool isUnsignedInt(std::string nbrStr)
{
	for (char c : nbrStr) 
	{
		if (!std::isdigit(c)) 
			return false;
	}
	return true;
}

unsigned int BitcoinExchange::_convertToUnsignedInt(std::string nbr)
{
	unsigned int unsignedIntVal;
	
	try
	{
		unsignedIntVal = static_cast<unsigned int>(std::stoul(nbr));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	if (!_isInRange(unsignedIntVal))
		std::cerr << "Error: conversion failed1" << std::endl;
	return unsignedIntVal;
}

float BitcoinExchange::_convertToFloat(std::string nbrStr)
{
	float floatVal;
	try
	{
		floatVal = std::stof(nbrStr);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	if (!_isInRange(floatVal))
		std::cerr << "Error: conversion failed2" << std::endl;
	return floatVal;
}

bool BitcoinExchange::_parseInputLine(std::string nextLine)
{
	std::string		valStr;
	nextLine.erase(std::remove(nextLine.begin(), nextLine.end(), ' '), nextLine.end());
	std::stringstream 	ss(nextLine);
	
	if (std::getline(ss, _inputDate, '|') && std::getline(ss, valStr))
	{
		//TODO check valid date here
		if (valStr.empty())
		{
			std::cerr << "Error: value is empty" << std::endl;
			return false;
		}
		else
		{
			if (isUnsignedInt(valStr))
				_inputValue = _convertToUnsignedInt(valStr);
			else
			{
std::cout << valStr << "\n";
				_inputValue = _convertToFloat(valStr);
std::cout << _inputValue << "\n";
			}
			// else
			// {
			// 	std::cerr << "Error: invalid value" << std::endl;
			// 	return false;	
			// }
		}
	}
_printInput();
	return true;
}

bool BitcoinExchange::readInputLineByLine()
{
	bool 				isFirstLine;
	std::ifstream		file;
	std::string 		nextLine;
	
	
	isFirstLine = true;
	
	if (openFile(_inputFile, file))
	{
		while (std::getline(file, nextLine))
		{
			if (isFirstLine)
			{
				isFirstLine = false;
				continue;	
			}
			if (!_parseInputLine(nextLine))
			{
				std::cerr << "Error: parseInputLine() failed" << std::endl;
				return false;
			}
			
		}
		file.close();
		return true;
	}
	else
		return false;
	
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

void BitcoinExchange::_printInput()
{
	if (std::isnan(_inputValue))
		std::cout << _inputDate << " | " << "nan" << std::endl;
	else
		std::cout << _inputDate << " | " << _inputValue << std::endl;
}