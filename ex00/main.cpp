/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:49 by tkong             #+#    #+#             */
/*   Updated: 2023/07/31 16:55:32 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

#define DB "data.csv"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: Need 1 argument" << std::endl;
		return -1;
	}
	try {
		BitcoinExchange(DB).run(av[1]);
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
