#include <cmath>
#include <iostream>

#include "GNUPlot.hpp"
#include "Maths.hpp"

constexpr uint32_t NPOINTS = 2 * 4 * 50; // length of array

void wait_for_key(); // Programm halts until keypress

using std::cout;
using std::endl;

using namespace signal::maths;

int main()
{
    std::vector<double> x, y, z;

    Maths maths;

    std::cout << maths.factorial(5) << std::endl;

    std::cout << maths.power(5.0, 2) << std::endl;
    std::cout << maths.power(-5.0, 2) << std::endl;
    std::cout << maths.power(5.0, 3) << std::endl;
    std::cout << maths.power(-5.0, 3) << std::endl;

    std::cout << maths.sinus(3) << std::endl;

    for (unsigned int i = 0; i < NPOINTS; i++)  // fill double arrays x, y, z
    {
        x.push_back((double)i);             // x[i] = i
        y.push_back((double)cos(i)); // y[i] = i^2
        z.push_back( x[i]*y[i] );           // z[i] = x[i]*y[i] = i^3
    }

    try
    {
        Gnuplot plot;

        plot.set_grid().set_samples(1000).set_xrange(0,1000);
        plot.set_smooth("bezier").plot_x(y,"bezier");
        plot.unset_smooth();

        //wait_for_key();
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
