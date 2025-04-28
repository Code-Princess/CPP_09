/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:49 by llacsivy          #+#    #+#             */
/*   Updated: 2025/04/28 20:44:51 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <cmath>
#include <limits>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_data;
	std::string						_inputDate;
	float 							_inputValue;

		
	void parseData(const std::string& dataFile);
	void parseDataLine(const std::string& nextLine);
	
	void readInputLineByLine(const std::string& inputFile);
	void parseInputLine(std::string nextLine);
	
	template <typename T>
	bool isInRange(T value);
	
	void printData();
	void printInput();
public:
	BitcoinExchange();
	BitcoinExchange(const std::string dataFile);
	~BitcoinExchange();
	
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange& operator=(const BitcoinExchange& other) = delete;

	// std::string getInputDate();
	// float getInputValue();
	
	// float getBitcoinExchangeRate(std::string date);

	void calcTurnOver(const std::string& inputFile);
};

bool isValidDate(std::string date);
bool isLeapYear(int year);
unsigned int convertToUnsignedInt(std::string nbr);
float convertToFloat(std::string nbrStr);

#endif