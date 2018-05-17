#include <iostream> 
#include <string>
#include <sstream>
#include <array>
#include <math.h>   
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <unistd.h>

#define ShittyLoop while(!!!glfwWindowShouldClose(window))
#define WINDOW 640
#define SIZE 50

typedef std::array<std::array<bool, SIZE>, SIZE> grid;
const double dt = 1000000*0.1;
const double cell_size = (double)WINDOW/SIZE;
	

grid this_gen;
grid next_gen;

bool alive_cells[9]; 
bool dead_cells[9]; 

GLFWwindow* windowSetup() 
{
	if(!glfwInit())
		return  NULL;

	GLFWwindow * window = glfwCreateWindow(SIZE, SIZE, "Game of life", NULL, NULL);

	if(!window) 
		return 	NULL;

	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 0); 
	return window; 
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void resize(GLFWwindow * window, int& width, int& height) 
{  
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glOrtho(0, width, 0, height, 0, 1);
}
void initState() 
{//pulsar 
	int offset_x = 0;
	int offset_y = 0;
	for (int i = 0; i < 4; i++)
	{
	if ( i == 2 || i == 3) {
	this_gen[4+offset_x][3+offset_y] = 1;
	this_gen[5+offset_x][3+offset_y] = 1;
	this_gen[6+offset_x][3+offset_y] = 1; 
	}else{
	this_gen[5+offset_x][3+offset_y] = 1;
	this_gen[6+offset_x][3+offset_y] = 1;
	this_gen[7+offset_x][3+offset_y] = 1; 
	}

	if ( i== 1 || i == 2){
	this_gen[3+offset_x][4+offset_y] = 1; 
	this_gen[3+offset_x][5+offset_y] = 1;
	this_gen[3+offset_x][6+offset_y] = 1; 
	}else{
	this_gen[3+offset_x][5+offset_y] = 1; 
	this_gen[3+offset_x][6+offset_y] = 1;
	this_gen[3+offset_x][7+offset_y] = 1; 
	}
	if ( i == 2 || i == 3 ) {
	this_gen[4+offset_x][8+offset_y] = 1; 
	this_gen[5+offset_x][8+offset_y] = 1; 
	this_gen[6+offset_x][8+offset_y] = 1; 
	}else {
	this_gen[5+offset_x][8+offset_y] = 1; 
	this_gen[6+offset_x][8+offset_y] = 1; 
	this_gen[7+offset_x][8+offset_y] = 1; 
	}
	
	if ( i == 1 || i == 2){
	this_gen[8+offset_x][4+offset_y] = 1; 
	this_gen[8+offset_x][5+offset_y] = 1; 
	this_gen[8+offset_x][6+offset_y] = 1;
	} else { 
	this_gen[8+offset_x][5+offset_y] = 1; 
	this_gen[8+offset_x][6+offset_y] = 1; 
	this_gen[8+offset_x][7+offset_y] = 1;
	}

	if ( i == 0 )
	offset_y = 7;
	if ( i == 1 ) 
	offset_x = 7;
	offset_y = 7;
	if ( i == 2 ) 
	{
	offset_x = 7;
	offset_y = 0;
	}

	}

	alive_cells[2] = 1; 
	alive_cells[3] = 1;
	dead_cells[3] = 1; 
}
void draw_square(int x, int y)
{
	x *= cell_size;
	y *= cell_size;
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x, y+cell_size);
		glVertex2f(x+cell_size, y+cell_size);
		glVertex2f(x+cell_size, y);
	glEnd();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool in_bounds(int x, int y)
{
	return ((x >= 0 && x < SIZE) && ( y >= 0 && y < SIZE ));
}

int countNeighbours(int x, int y) 
{
	int count = 0;
	for  (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++) 
			if (!(i==0 && j==0)) 
				count += this_gen[x+i][y+j];
	return count;
}

bool get_next_gen(bool this_gen_cell, int neighbours) 
{
	return this_gen_cell ? alive_cells[neighbours] : dead_cells[neighbours];
}

void render() 
{
	for (int i = 0; i < SIZE; i++) 
		for (int j = 0; j < SIZE; j++) 
			if (this_gen[i][j]) 
				draw_square(i, j); 

	for (int i = 0; i < SIZE; i++) 
	{
		for (int j = 0; j < SIZE; j++)
		{
			int count = countNeighbours(i,j);
			next_gen[i][j] = get_next_gen(this_gen[i][j], count);
		}
	}
	for (int i = 0; i < SIZE; i++) 
		for (int j = 0; j < SIZE; j++)
			this_gen[i][j] = next_gen[i][j];
}

int main()
{
	GLFWwindow* window = windowSetup();

	if(window == NULL)
	{
		glfwTerminate();
		return 1;
	}
	initState();	
	int width, height;
	ShittyLoop
	{
		glfwPollEvents(); 
		clear(); 
		resize(window, width, height); 
		render();
		glfwSwapBuffers(window);
		usleep(dt);
	}
	return 0;
}
