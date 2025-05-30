/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:59 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/03 00:29:40 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	
}

BitcoinExchange::BitcoinExchange(const std::string dataFile)
{
	parseData(dataFile);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::executeTurnOver(const std::string& inputFile)
{
	bool 				isFirstLine;
	std::ifstream		file;
	std::string 		nextLine;
	
	isFirstLine = true;
	openFile(inputFile, file);
	while (std::getline(file, nextLine))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}
		processInputLine(nextLine);
	}
	file.close();
}

void BitcoinExchange::processInputLine(std::string& nextLine)
{
	std::optional<double> exchangeRate;
	double turnOver;

	if (parseInputLine(nextLine))
	{
		if (!_inputDate.empty() && _inputValue.has_value())
		{
			try
			{
				exchangeRate = getBtcExchangeRate(_inputDate);
				if (exchangeRate != std::nullopt)
				{
					turnOver = calcTurnOver(exchangeRate, _inputValue.value());
					printResult(turnOver);
				}
			}
			catch(const std::exception& e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
	}
}

void BitcoinExchange::parseData(const std::string& dataFile)
{
	std::ifstream	file;
	std::string 	nextLine;
	bool			isFirstLine;
	
	isFirstLine = true;

	openFile(dataFile, file);
	while (std::getline(file, nextLine))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;	
		}
		parseDataLine(nextLine);
	}
	file.close();
}

void BitcoinExchange::parseDataLine(std::string& nextLine)
{
	std::string			date;
	std::string			exchangeRateStr;
	double				exchangeRate;
	std::stringstream 	ss(nextLine);
	if (std::getline(ss, date, ',') && std::getline(ss, exchangeRateStr))
	{
		try
		{
			size_t idx;
			exchangeRate = std::stod(exchangeRateStr, &idx);
			if (idx != exchangeRateStr.size())
			{
				std::cerr << "Error: invalid exchange_rate " << exchangeRateStr << std::endl;
				return;
			}
			if (isValidDate(date))
			{
				if(!(_data.insert({date, exchangeRate})).second)
				std::cerr << "duplicate date! taken: " << date << \
					"," << exchangeRate << std::endl;
			}
			else
				std::cerr << "Error: invalid date " << date << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Error: invalid format " << nextLine << std::endl;
}

bool BitcoinExchange::parseInputLine(std::string& nextLine)
{
	std::string		date,value;
	_inputDate = "";
	_inputValue = std::nullopt;
	std::stringstream 	ss(nextLine);

	if (std::getline(ss, date, '|') && std::getline(ss, value))
	{
		if (date[date.size() - 1] != ' ' || value[0] != ' ')
		{
			std::cerr << "Error: invalid format " << nextLine << std::endl;
			return false;
		}
		date.erase(date.size() - 1, 1);
		value.erase(0, 1);
		if (isValidDate(date))
			_inputDate = date;
		else
		{
			std::cerr << "Error: invalid date: " << date << std::endl;
			return false;
		}
		if (!processValue(value))
			return false;
	}
	else
	{
		std::cerr << "Error: invalid format => " << nextLine << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::processValue(std::string& value)
{
	if (value.empty())
	{
		std::cerr << "Error: empty value" << std::endl;
		return false;
	}
	else
	{
		try
		{
			if (isUnsignedInt(value))
				_inputValue = convertToUnsignedInt(value);
			else
				_inputValue = convertToDouble(value);
			if (_inputValue == std::nullopt)
			{
				std::cerr << "Error: invalid value " << value << std::endl;
				return false;
			}
			if (!isValidRange(_inputValue.value()))
				return false;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return true;
}

std::optional<double> BitcoinExchange::getBtcExchangeRate(std::string& inputDate)
{
	auto it = _data.lower_bound(inputDate);
	if (it != _data.end() && it->first == inputDate)
		return it->second;
	if (it == _data.begin())
	{
		std::cerr << "Error: no available exchange rate!" << std::endl;
		return std::nullopt;
	}
	--it;
	return it->second;
}

double 	BitcoinExchange::calcTurnOver(std::optional<double> exchangeRate, double inputValue)
{
	return exchangeRate.value() * inputValue;
}
void BitcoinExchange::printData()
{
	std::cout << "_data map:" << std::endl;
	for (const auto& pair : _data)
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << pair.first << "," << pair.second << std::endl;
	}
}

void BitcoinExchange::printInput()
{
	std::cout << _inputDate << " | " << _inputValue.value() << std::endl;
}

void BitcoinExchange::printResult(double turnOver)
{
	std::cout << _inputDate << " => " << _inputValue.value() << \
		" = " << turnOver << std::endl;
}

void openFile(const std::string& dataFile, 	std::ifstream& file)
{
	file.open(dataFile);
	if (!file.is_open())
		throw std::runtime_error("open file failed!");
}

bool isValidDate(std::string date)
{	
	int year, month, day;
	char dash1, dash2;
	
	int daysInFebruary;
	std::istringstream iss(date);
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	if (!(iss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (month < 1 || month > 12)
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (isLeapYear(year))
		daysInFebruary = 29;
	else
		daysInFebruary = 28;
	int maxDaysOfMonth[12] = {31, daysInFebruary, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > maxDaysOfMonth[month - 1])
		return false;
	return true;
}

bool isLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		return true;
	else
		return false;
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

std::optional<unsigned int> convertToUnsignedInt(std::string nbr)
{
	std::optional<unsigned int> unsignedIntVal;
	try
	{
		size_t idx;
		unsignedIntVal = static_cast<unsigned int>(std::stoul(nbr, &idx));
		if (idx != nbr.size())
			unsignedIntVal = std::nullopt;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return unsignedIntVal;
}

std::optional<double> convertToDouble(std::string nbrStr)
{
	std::optional<double> doubleVal;
	try
	{
		size_t idx;
		doubleVal = std::stod(nbrStr, &idx);
		if (idx != nbrStr.size())
			doubleVal = std::nullopt;
	}
	catch(const std::exception& e)
	{
	}
	return doubleVal;
}

template <typename T>
bool isValidRange(T value)
{
	if (value >= 0 && value <= 1000)
		return true;
	else
	{
		std::cerr << "Error: " << value << " not in range [0, 1000]" << std::endl;
		return false;
	}
}