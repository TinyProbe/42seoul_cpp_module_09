/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:28:52 by tkong             #+#    #+#             */
/*   Updated: 2023/08/02 09:41:08 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <exception>

int main(int ac, char **av) {
	try {
		PmergeMe().run(ac, av);
	} catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
