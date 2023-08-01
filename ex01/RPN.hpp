/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:27:54 by tkong             #+#    #+#             */
/*   Updated: 2023/08/01 14:50:14 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef RPN_HPP
#define RPN_HPP

class RPN {

private:
	RPN(const RPN &rhs);
	RPN &operator=(const RPN &rhs);

public:
	RPN();
	virtual ~RPN();

	virtual void run(int ac, char **av);

};

#endif
