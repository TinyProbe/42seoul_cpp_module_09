/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:44 by tkong             #+#    #+#             */
/*   Updated: 2023/07/30 18:11:04 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange {

private:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &rhs);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

public:
	BitcoinExchange(const std::string &db);
	virtual ~BitcoinExchange();

	virtual void run(const std::string &input);

};

#endif
