#include <cmath>
#include <iostream>

#include "GNUPlot.hpp"
#include "Maths.hpp"

constexpr uint32_t NPOINTS = 360; // length of array

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

using namespace signal::maths;

int main()
{
    std::vector<double> x, y, z;

    Maths maths;

    std::cout << maths.toRadians(maths.sinus(PI / 2)) << std::endl;



    //std::cout << maths.sinus(3) << std::endl;

    for (unsigned int i = 0; i < NPOINTS; i++)  // fill double arrays x, y, z
    {
        cout << "sinus(" << i << ") : " << maths.sinus(i) << " | " << sin(i) << endl; 
        x.push_back(i);             // x[i] = i
        y.push_back((double)maths.sinus(i)); // y[i] = i^2
        z.push_back( x[i]*y[i] );           // z[i] = x[i]*y[i] = i^3
    }

    try
    {
        Gnuplot plot;

        plot.set_grid().set_samples(1000).set_xrange(0,360);
        plot.set_smooth("csplines").plot_x(y,"csplines");
        plot.unset_smooth();

        wait_for_key();
    }
    catch (GNUPlotException &ge)
    {
        cout << ge.what() << endl;
    }

    return 0;
}

void wait_for_key()
{
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    return;
}
