/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbroggi <pbroggi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 16:38:56 by pbroggi           #+#    #+#             */
/*   Updated: 2015/06/11 18:32:20 by pbroggi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

# include <View.hpp>
# include <Model.hpp>
# include <Define.hpp>
# include <Parser.hpp>
# include <Exceptions.hpp>

static void 		exceptionsHandler(std::exception & e)
{
	if (typeid(e) == typeid(std::ifstream::failure))
	{
		std::cerr << RED << "MOD1 error: " << std::strerror(errno) << WHITE << std::endl;
	}
	else
	{
		std::cerr << RED << "MOD1 error: " << e.what() << WHITE << std::endl;
	}
}

int					main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage:\t./mod1 <scenario> <map>" << std::endl
		<< "\t- Available scenarios: flood, rain, waves, drain, tsunami" << std::endl;
		return -1;
	}
	try
	{
		Model					model;
		Parser					parser(model, argv[1], argv[2]);
		View					view(model);

		model.build();
		view.render();
	}
	catch (std::exception & e)
	{
		exceptionsHandler(e);
	}
	return 0;
}
