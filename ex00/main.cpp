/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:49 by tkong             #+#    #+#             */
/*   Updated: 2023/07/30 18:04:13 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

#define DB "data.csv"

int main(int ac, char **av) {
	try {
		if (ac != 2) { throw std::runtime_error("Need 1 argument"); }
	} catch (const std::exception &e) {
		std::cout << e.what() << '\n';
	}
	BitcoinExchange btex(DB);
	btex.run(av[1]);
}
