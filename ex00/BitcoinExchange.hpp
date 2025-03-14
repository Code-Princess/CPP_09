/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:49 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/14 22:05:33 by llacsivy         ###   ########.fr       */
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
	const std::string				_inputFile;
	std::string						_inputDate;
	float 							_inputValue;
	
	bool _parseInputLine(std::string nextLine);	
	template <typename T>
	bool _isInRange(T value);
	unsigned int _convertToUnsignedInt(std::string nbr);
	float _convertToFloat(std::string nbrStr);
	bool _parseDataLine(const std::string& nextLine);
	void _printData();
	void _printInput();
public:
	BitcoinExchange();
	BitcoinExchange(const std::string inputFile);
	// BitcoinExchange(const BitcoinExchange& other);
	// BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	
	// std::string getInputDate();
	// float getInputValue();
	

	bool parseData(const std::string dataFile);
	std::map<std::string, double> getData();
	bool readInputLineByLine();
	// float getBitcoinExchangeRate(std::string date);
	
};



#endif