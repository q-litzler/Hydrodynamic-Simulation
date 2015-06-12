/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlitzler <qlitzler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/13 18:13:48 by qlitzler          #+#    #+#             */
/*   Updated: 2015/06/02 21:21:44 by qlitzler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <glm/glm.hpp>

# include <fstream>
# include <vector>
# include <regex>

# include <Define.hpp>

class Model;

class Parser
{

	public:
		Parser(Model & model, char const * scenario, char const * path);
		~Parser(void);
		void			parse(void);

	private:
		Parser(void);
		Parser(Parser const & src);
		Parser &		operator=(Parser const & rhs);
		void			checkScenario(char const * scenario);
		void			checkPath(char const * path);
		void			checkBounds(void) const;
		Model &			_model;
		std::ifstream	_file;
};

#endif /* ! PARSER_CLASS_HPP */
