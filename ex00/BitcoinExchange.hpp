/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llacsivy <llacsivy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:46:49 by llacsivy          #+#    #+#             */
/*   Updated: 2025/03/13 23:42:32 by llacsivy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>

class BitcoinExchange
{
private:
	std::map<std::string, float>	_data;
	// std::string						_inputFile;
	// std::string						_inputDate;
	// float							_inputValue;
public:
	BitcoinExchange();
	// BitcoinExchange(std::string inputFile);
	// BitcoinExchange(const BitcoinExchange& other);
	// BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	
	bool parseData(const std::string dataFile, std::map<std::string, float> _data);
	// std::map<std::string, float> getDatabase();
	// float getBitcoinExchangeRate(std::string date);
	
};



#endif