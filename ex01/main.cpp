/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:27:50 by tkong             #+#    #+#             */
/*   Updated: 2023/08/02 09:21:35 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av) {
	try {
		RPN().run(ac, av);
	} catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
