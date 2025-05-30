/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:49 by llacsivy          #+#    #+#             */
/*   Updated: 2025/05/03 00:03:31 by llacsivy         ###   ########.fr       */
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
	std::optional<double> 			_inputValue;

	void 					parseData(const std::string& dataFile);
	void 					parseDataLine(std::string& nextLine);
	void					processInputLine(std::string& nextLine);
	bool 					parseInputLine(std::string& nextLine);
	bool					processValue(std::string& value);
	std::optional<double>	getBtcExchangeRate(std::string& inputDate);
	double					calcTurnOver(std::optional<double> exchangeRate, double inputValue);

	void printData();
	void printInput();
	void printResult(double turnOver);
public:
	BitcoinExchange();
	BitcoinExchange(const std::string dataFile);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange& operator=(const BitcoinExchange& other) = delete;

	void executeTurnOver(const std::string& inputFile);
};

void openFile(const std::string& dataFile, 	std::ifstream& file);
bool isLeapYear(int year);
bool isValidDate(std::string date);
template <typename T>
bool isValidRange(T value);
bool isUnsignedInt(std::string nbrStr);
std::optional<unsigned int> convertToUnsignedInt(std::string nbr);
std::optional<double> convertToDouble(std::string nbrStr);

#endif