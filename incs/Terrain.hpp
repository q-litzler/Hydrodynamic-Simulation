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
		void			createNormals(void);
		void			createVertices(void);
		void			createElements(void);
		void			createColors(void);
};

#endif /* ! TERRAIN_CLASS_HPP */
