/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:44 by tkong             #+#    #+#             */
/*   Updated: 2023/08/02 09:19:08 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
	std::map<long, double> db;

private:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &rhs);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	bool check_flag(long before, long after, long afafter, long inv_d, long inv_a);
	bool check_date(long y, long m, long d);
	bool check_amount(double amount);

public:
	BitcoinExchange(const std::string &csv);
	virtual ~BitcoinExchange();

	virtual void run(const std::string &input);

};

#endif
