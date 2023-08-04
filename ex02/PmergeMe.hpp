/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkong <tkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:28:54 by tkong             #+#    #+#             */
/*   Updated: 2023/08/03 21:51:04 by tkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>

class PmergeMe {
	std::vector<size_t> vec;
	std::list<size_t> lst;

private:
	typedef unsigned long long u64;

	PmergeMe(const PmergeMe &rhs);
	PmergeMe &operator=(const PmergeMe &rhs);

	virtual void sort_vec(const std::vector<size_t> &args);
	virtual void sort_lst(const std::vector<size_t> &args);
	virtual u64 gettime() const;
	virtual size_t nextnum(bool clear = false) const;

public:
	PmergeMe();
	virtual ~PmergeMe();

	virtual void run(int ac, char **av);

};

#endif
