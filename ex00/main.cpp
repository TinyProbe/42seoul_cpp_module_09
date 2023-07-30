/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:24:49 by tkong             #+#    #+#             */
/*   Updated: 2023/07/30 16:48:48 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Need 1 argument" << '\n';
		return 1;
	}
	std::fstream fs(av[1]);
	if (!fs.is_open()) {
		std::cout << "Failed open file" << '\n';
		return 2;
	}
	
}
