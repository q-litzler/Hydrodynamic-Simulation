#ifndef MODEL_CLASS_HPP
# define MODEL_CLASS_HPP

# include <glm/glm.hpp>
# include <Define.hpp>
# include <Terrain.hpp>
# include <Drop.hpp>
# include <Water.hpp>
# include <WaterBorders.hpp>
# include <Borders.hpp>
# include <vector>

class Model
{
	friend class Terrain;
	friend class Drop;
	friend class Water;
	friend class Borders;
	friend class WaterBorders;

	public:
		Model(void);
		~Model(void);
		glm::mat4					getMatrix(void) const;
		GLuint						getWidth(void) const;
		GLuint						getHeight(void) const;
		GLuint						getRow(void) const;
		GLuint						getCol(void) const;
		GLfloat						getTop(void) const;
		glm::vec3					getLight(void) const;
		e_scenarios					getScenario(void) const;
		Water *						getWater(void) const;
		Terrain *					getTerrain(void) const;
		Borders *					getBorders(void) const;
		WaterBorders *				getWaterBorders(void) const;
		Drop *						getDrop(void) const;
		std::vector<glm::vec3>		getPoints(void) const;

		void						setRotation(float angle);
		void						setScaleFactor(float delta);
		void						setScenario(e_scenarios type);
		void						setWidth(GLuint width);
		void						setHeight(GLuint height);
		void						setRow(GLuint row);
		void						setCol(GLuint col);

		void						build(void);
		void						addPoints(glm::vec3 point, bool override);
	
	private:
		Model(Model const & model);
		Model &						operator=(Model const & rhs);
		void						setMapCorners(void);

		std::vector<glm::vec3> 		_points;
		float						_top;
		float						_bottom;
		GLuint						_width;
		GLuint						_height;
		GLuint						_row;
		GLuint						_col;
		GLuint						_stride;
		glm::vec3					_scale;
		GLfloat						_scaleFactor;
		glm::vec3					_light;
		float						_rotation;
		GLuint						_vertexRow;
		GLuint						_vertexCol;
		GLuint						_grid;
		Terrain *					_terrain;
		Drop *						_drop;
		Water *						_water;
		Borders *					_borders;
		WaterBorders *				_waterBorders;
		e_scenarios					_scenario;
};

#endif /* ! MODEL_CLASS_HPP */
