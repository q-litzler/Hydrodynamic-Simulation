/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Terrain.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlitzler <qlitzler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/21 09:56:50 by p                 #+#    #+#             */
/*   Updated: 2015/06/02 21:22:10 by qlitzler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERRAIN_CLASS_HPP
# define TERRAIN_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <AModule.hpp>

class Terrain: public AModule
{
	public:
		Terrain(Model & model);
		~Terrain(void);

	private:
		Terrain(void);
		Terrain(Terrain const & model);
		Terrain &		operator=(Terrain const & rhs);
		void			inverseWeightedDistance(void);
		void			calculateNormals(void);
		void			createVertices(void);
		void			createElements(void);
		void			createColors(void);
};

#endif /* ! TERRAIN_CLASS_HPP */
