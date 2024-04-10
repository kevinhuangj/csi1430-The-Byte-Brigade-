/* NOTES FOR GROUP PROJECT
 *
 * Learn how to link GitHub repository?
 *
 * Maybe have starting colonies for 2 animals?
 *
 * One natural disaster be poke of the overseer?  Clicking on different types does something?
 *
 * System for determining grid position based off of pixel interaction x / SIDE y / SIDE
 */


#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"
#include "config.h"
#include "grid.h"
#include "square.h"
using namespace std;




int main(int argc, char ** argv)
{

    SDL_Plotter g(SIZE,SIZE);
    //int R, G, B;
    int dim = SIZE/SIDE;
    Square data[dim][dim];

    for(int r = 0;r < dim;r++)
    {
    	for(int c = 0;c < dim;c++)
    	{
    		data[r][c].setRow(r);
    		data[r][c].setCol(c);
    	}
    }
    while (!g.getQuit())
    {
		if(g.kbhit()){
		}

		if(g.mouseClick()){
			point p = g.getMouseClick();
			cout << p.x/SIDE << " " << p.y/SIDE << endl;
			data[p.y/SIDE][p.x/SIDE].click();
		}

		for(int r = 0;r < dim;r++)
		{
			for(int c = 0;c < dim;c++)
			{
				data[r][c].draw(g);

			}
		}
		drawGrid(g);
		g.update();
    }
}


