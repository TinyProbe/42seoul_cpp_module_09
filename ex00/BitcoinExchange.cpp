/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:41 by tkong             #+#    #+#             */
/*   Updated: 2023/08/02 09:19:58 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

BitcoinExchange::BitcoinExchange(const std::string &csv) {
	std::fstream fs(csv);
	if (!fs.is_open()) {
		throw std::runtime_error("Failed to open .csv");
	}
	std::string line;
	fs>>line;
	while (fs>>line) {
		bool after=false, afafter=false;
		long date=0L;
		double amount=0., div=1.;
		for (size_t i=0; i<line.size(); ++i) {
			if (line[i]==',') {
				after = true;
			} else if (!after) {
				if (line[i]=='-') { continue; }
				date = (date<<1)+(date<<3)+(line[i]-'0');
			} else {
				if (line[i]=='.') { afafter = true; continue; }
				if (!afafter) {
					amount = 10*amount+(line[i]-'0');
				} else {
					amount += (line[i]-'0')/(div*=10);
				}
			}
		}
		db[date] = amount;
	}
	fs.close();
}
BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::check_flag(long before, long after, long afafter, long inv_d, long inv_a) {
	if (before != 2 || after != 1 || afafter > 1 || inv_d > 0 || inv_a > 0) {
		std::cerr << "Error: Invalid format" << std::endl;
		return false;
	}
	return true;
}
bool BitcoinExchange::check_date(long y, long m, long d) {
	static const long day_limit[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((y<1923 || y>2023) || (m<1 || m>12) || (d<1 || d>day_limit[m]+(y%4==0 && m==2 ? 1 : 0))) {
		std::cerr << "Error: Invalid date => "
			<< (y<1000 ? "0" : "") << (y<100 ? "0" : "") << (y<10 ? "0" : "") << y << "-"
			<< (m<10 ? "0" : "") << m << "-"
			<< (d<10 ? "0" : "") << d << std::endl;
		return false;
	}
	return true;
}
bool BitcoinExchange::check_amount(double amount) {
	if (amount < 0. || amount > 1000.) {
		std::cerr << "Error: Invalid amount" << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::run(const std::string &input) {
	if (db.empty()) {
		throw std::runtime_error("Nothing else in database");
	}
	std::fstream fs(input);
	if (!fs.is_open()) {
		throw std::runtime_error("Failed to open file");
	}
	std::string line;
	std::getline(fs, line);
	while (std::getline(fs, line)) {
		long y=0L, m=0L, d=0L;
		long before=0L, after=0L, afafter=0L, inv_d=0L, inv_a=0L;
		double amount=0., div=1.;
		for (size_t i=0; i<line.size(); ++i) {
			if (line[i]==' ' || (line[i]=='|' && ++after)) {
				continue;
			} else if (after==0) {
				if (std::isdigit(line[i])) {
					if      (before==0) { y = (y<<1)+(y<<3)+(line[i]-'0'); }
					else if (before==1) { m = (m<<1)+(m<<3)+(line[i]-'0'); }
					else if (before==2) { d = (d<<1)+(d<<3)+(line[i]-'0'); }
					else { break; }
				} else if (line[i]=='-') {
					++before;
				} else {
					++inv_d; break;
				}
			} else {
				if (std::isdigit(line[i])) {
					if (afafter == 0) {
						amount = 10*amount+(line[i]-'0');
					} else {
						amount += (line[i]-'0')/(div*=10);
					}
				} else if (line[i]=='.') {
					++afafter;
				} else {
					++inv_a; break;
				}
			}
		}
		if (check_flag(before, after, afafter, inv_d, inv_a)
		&& check_date(y, m, d) && check_amount(amount)) {
			long date = y*10000+m*100+d;
			if (db.begin()->first > date) {
				std::cerr << "Error: No data for reference" << std::endl;
				continue;
			}
			std::map<long, double>::iterator it = --db.upper_bound(date);
			std::cout << (y<1000 ? "0" : "") << (y<100 ? "0" : "") << (y<10 ? "0" : "") << y << '-'
				<< (m<10 ? "0" : "") << m << '-'
				<< (d<10 ? "0" : "") << d << " => "
				<< amount << " = " << (it->second * amount) << std::endl;
		}
	}
	fs.close();
}
