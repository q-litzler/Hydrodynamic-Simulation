#ifndef DEFINE_HPP
# define DEFINE_HPP

# define GL_MAJOR					4
# define GL_MINOR					1

# define BATCH						100
# define MAX_INSTANCES				17000

# define X							1
# define Y							2
# define Z							3

# define WIDTH						1
# define HEIGHT						2
# define SCENARIOS					5

# define SCALE_FACTOR				50.0f 
# define UNIT						5.0f
# define DROP_UNIT					2.5f
# define WATER_OFFSET				2.5f
# define RAIN_SPEED					10
# define DROP_FILLING_RATE			5
# define WATER_DISTRIBUTION_RATE 	4
# define TSUNAMI_COEFFICIENT		4.0f
# define WAVES_COEFFICIENT			5.0f
# define DRAIN_COEFFICIENT			3.0f

# define COL						1
# define ROW						2

# define MAX_WIDTH					2560
# define MIN_WIDTH					100

# define MAX_HEIGHT					1440
# define MIN_HEIGHT					100

# define MAX_COL					3000
# define MIN_COL					20

# define MAX_ROW					3000
# define MIN_ROW					20

# define DIMENSIONS					3
# define COLOR_CHANNELS				4

# define RED						"\x1b[31m"
# define WHITE						"\x1b[0m"
# define CYAN						"\x1b[36m"

enum								e_scenarios
{
	FLOOD = 0,
	RAIN,
	WAVES,
	DRAIN,
	TSUNAMI
};

# define GLEW_STATIC
# include <GL/glew.h>

#endif
