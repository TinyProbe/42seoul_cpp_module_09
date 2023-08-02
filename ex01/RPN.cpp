/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:27:52 by tkong             #+#    #+#             */
/*   Updated: 2023/08/02 09:24:29 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>
#include <stack>

RPN::RPN() {}
RPN::~RPN() {}

void RPN::run(int ac, char **av) {
	std::string arg;
	for (size_t i=1; i<(size_t)ac; ++i) {
		arg += av[i];
		arg += ' ';
	}
	const std::string allow = "0123456789-+*/";
	std::stack<long> stk;
	for (size_t i=0; i<arg.size(); ++i) {
		if (i+1 < arg.size()) {
			if (std::isdigit(arg[i]) && std::isdigit(arg[i+1])) {
				if (arg[i]!='0') {
					throw std::invalid_argument("Invalid format");
				} else {
					continue;
				}
			}
		}
		if (allow.find_first_of(arg[i]) != std::string::npos) {
			if (std::isdigit(arg[i])) {
				stk.push(arg[i]-'0');
			} else {
				if (stk.size() < 2) { throw std::runtime_error("Not enough operand"); }
				long a, b;
				b = stk.top(), stk.pop();
				a = stk.top(), stk.pop();
				if      (arg[i] == '-') { stk.push(a-b); }
				else if (arg[i] == '+') { stk.push(a+b); }
				else if (arg[i] == '*') { stk.push(a*b); }
				else if (arg[i] == '/') {
					if (b == 0) { throw std::runtime_error("Zero divide"); }
					stk.push(a/b);
				}
			}
		} else if (!std::isspace(arg[i])) {
			throw std::invalid_argument("Invalid format");
		}
	}
	if (stk.size() != 1) { throw std::invalid_argument("Invalid formula"); }
	std::cout << stk.top() << std::endl;
}
