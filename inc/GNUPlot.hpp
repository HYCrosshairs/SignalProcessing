#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>              // for std::ostringstream
#include <stdexcept>
#include <cstdio>
#include <cstdlib>              // for getenv()
#include <list>                 // for std::list
#include <unistd.h>            // for access(), mkstemp()

constexpr uint8_t GP_MAX_TMP_FILES = 64;


class GNUPlotException : public std::runtime_error
{
public:
    GNUPlotException(const std::string &msg) : std::runtime_error(msg) {}
};

class Gnuplot
{
public:
    static bool set_GNUPlotPath(const std::string &path);

    static void set_terminal_std(const std::string &type);

    ///\brief set a style during construction
    Gnuplot(const std::string &style = "points");

    /// plot a single std::vector at one go
    Gnuplot(const std::vector<double> &x,
            const std::string &title = "",
            const std::string &style = "points",
            const std::string &labelx = "x",
            const std::string &labely = "y");

    /// plot pairs std::vector at one go
    Gnuplot(const std::vector<double> &x,
            const std::vector<double> &y,
            const std::string &title = "",
            const std::string &style = "points",
            const std::string &labelx = "x",
            const std::string &labely = "y");

    /// plot triples std::vector at one go
    Gnuplot(const std::vector<double> &x,
            const std::vector<double> &y,
            const std::vector<double> &z,
            const std::string &title = "",
            const std::string &style = "points",
            const std::string &labelx = "x",
            const std::string &labely = "y",
            const std::string &labelz = "z");

    /// destructor: needed to delete temporary files
    ~Gnuplot();

    Gnuplot& cmd(const std::string &cmdstr);

    inline Gnuplot& operator<<(const std::string &cmdstr)
    {
        cmd(cmdstr);
        return(*this);
    }

    /// sets terminal type to terminal_std
    Gnuplot& showonscreen(); // window output is set by default (win/x11/aqua)

    /// Saves a gnuplot to a file named filename.  Defaults to saving pdf
    Gnuplot& savetofigure(const std::string &filename,
                          const std::string &terminal="ps");

    Gnuplot& set_style(const std::string &stylestr = "points");

    Gnuplot& set_smooth(const std::string &stylestr = "csplines");

    inline Gnuplot& unset_smooth()
    {
        smooth = "";
        return *this;
    };

    /// scales the size of the points used in plots
    Gnuplot& set_pointsize(const double pointsize = 1.0);

    /// turns grid on/off
    inline Gnuplot& set_grid()
    {
        cmd("set grid");
        return *this;
    };
    /// grid is not set by default
    inline Gnuplot& unset_grid()
    {
        cmd("unset grid");
        return *this;
    };

    inline Gnuplot& set_multiplot()
    {
        cmd("set multiplot") ;
        return *this;
    };

    inline Gnuplot& unset_multiplot()
    {
        cmd("unset multiplot");
        return *this;
    };

    /// set sampling rate of functions, or for interpolating data
    Gnuplot& set_samples(const int samples = 100);
    /// set isoline density (grid) for plotting functions as surfaces (for 3d plots)
    Gnuplot& set_isosamples(const int isolines = 10);

    Gnuplot& set_hidden3d()
    {
        cmd("set hidden3d");
        return *this;
    };

    inline Gnuplot& unset_hidden3d()
    {
        cmd("unset hidden3d");
        return *this;
    };

    /// enables/disables contour drawing for surfaces (for 3d plot)
    ///  base, surface, both
    Gnuplot& set_contour(const std::string &position = "base");

    inline Gnuplot& unset_contour()
    {
        cmd("unset contour");
        return *this;
    };

    inline Gnuplot& set_surface()
    {
        cmd("set surface");
        return *this;
    };

    inline Gnuplot& unset_surface()
    {
        cmd("unset surface");
        return *this;
    }


    /// switches legend on/off
    /// position: inside/outside, left/center/right, top/center/bottom, nobox/box
    Gnuplot& set_legend(const std::string &position = "default");

    inline Gnuplot& unset_legend()
    {
        cmd("unset key");
        return *this;
    }

    inline Gnuplot& set_title(const std::string &title = "")
    {
        std::string cmdstr;
        cmdstr = "set title \"";
        cmdstr+=title;
        cmdstr+="\"";
        *this<<cmdstr;
        return *this;
    }

    inline Gnuplot& unset_title()
    {
        this->set_title();
        return *this;
    }

    /// set x axis label
    Gnuplot& set_ylabel(const std::string &label = "x");
    /// set y axis label
    Gnuplot& set_xlabel(const std::string &label = "y");
    /// set z axis label
    Gnuplot& set_zlabel(const std::string &label = "z");

    /// set axis - ranges
    Gnuplot& set_xrange(const double iFrom,
                        const double iTo);
    /// set y-axis - ranges
    Gnuplot& set_yrange(const double iFrom,
                        const double iTo);
    /// set z-axis - ranges
    Gnuplot& set_zrange(const double iFrom,
                        const double iTo);
    
    inline Gnuplot& set_xautoscale()
    {
        cmd("set xrange restore");
        cmd("set autoscale x");
        return *this;
    };

    inline Gnuplot& set_yautoscale()
    {
        cmd("set yrange restore");
        cmd("set autoscale y");
        return *this;
    };

    inline Gnuplot& set_zautoscale()
    {
        cmd("set zrange restore");
        cmd("set autoscale z");
        return *this;
    };


    /// turns on/off log scaling for the specified xaxis (logscale is not set by default)
    Gnuplot& set_xlogscale(const double base = 10);
    /// turns on/off log scaling for the specified yaxis (logscale is not set by default)
    Gnuplot& set_ylogscale(const double base = 10);
    /// turns on/off log scaling for the specified zaxis (logscale is not set by default)
    Gnuplot& set_zlogscale(const double base = 10);

    inline Gnuplot& unset_xlogscale()
    {
        cmd("unset logscale x");
        return *this;
    };

    inline Gnuplot& unset_ylogscale()
    {
        cmd("unset logscale y");
        return *this;
    };

    // -----------------------------------------------
    inline Gnuplot& unset_zlogscale()
    {
        cmd("unset logscale z");
        return *this;
    };


    /// set palette range (autoscale by default)
    Gnuplot& set_cbrange(const double iFrom, const double iTo);

    //--------------------------------------------------------------------------
    // plot

    /// plot a single std::vector: x
    ///   from file
    Gnuplot& plotfile_x(const std::string &filename,
                        const unsigned int column = 1,
                        const std::string &title = "");
    ///   from std::vector
    template<typename X>
    Gnuplot& plot_x(const X& x, const std::string &title = "");

    /// plot x,y pairs: x y
    ///   from file
    Gnuplot& plotfile_xy(const std::string &filename,
                         const unsigned int column_x = 1,
                         const unsigned int column_y = 2,
                         const std::string &title = "");
    ///   from data
    template<typename X, typename Y>
    Gnuplot& plot_xy(const X& x, const Y& y, const std::string &title = "");

    /// plot x,y pairs with dy errorbars: x y dy
    ///   from file
    Gnuplot& plotfile_xy_err(const std::string &filename,
                             const unsigned int column_x  = 1,
                             const unsigned int column_y  = 2,
                             const unsigned int column_dy = 3,
                             const std::string &title = "");
    ///   from data
    /*template<typename X, typename Y, typename E>
    Gnuplot& plot_xy_err(const X &x, const Y &y, const E &dy,
                         const std::string &title = "");*/

    /// plot x,y,z triples: x y z
    ///   from file
    Gnuplot& plotfile_xyz(const std::string &filename,
                          const unsigned int column_x = 1,
                          const unsigned int column_y = 2,
                          const unsigned int column_z = 3,
                          const std::string &title = "");
    ///   from std::vector
    template<typename X, typename Y, typename Z>
    Gnuplot& plot_xyz(const X &x,
                      const Y &y,
                      const Z &z,
                      const std::string &title = "");

    Gnuplot& plot_slope(const double a,
                        const double b,
                        const std::string &title = "");

    Gnuplot& plot_equation(const std::string &equation,
                           const std::string &title = "");

    Gnuplot& plot_equation3d(const std::string &equation,
                             const std::string &title = "");


    /// plot image
    Gnuplot& plot_image(const unsigned char *ucPicBuf,
                        const unsigned int iWidth,
                        const unsigned int iHeight,
                        const std::string &title = "");

    inline Gnuplot& replot(void)
    {
        if (nplots > 0) cmd("replot");
        return *this;
    };

    /// resets a gnuplot session (next plot will erase previous ones)
    Gnuplot& reset_plot();

    /// resets a gnuplot session and sets all variables to default
    Gnuplot& reset_all();

    /// deletes temporary files
    void remove_tmpfiles();

    inline bool is_valid()
    {
        return(valid);
    };

private:
    FILE                    *gnucmd;
    bool                     valid;
    bool                     two_dim;
    int                      nplots;
    std::string              pstyle;
    std::string              smooth;
    std::vector<std::string> tmpfile_list;

    static int               tmpfile_num;
    static std::string       m_sGNUPlotFileName;
    static std::string       m_sGNUPlotPath;
    static std::string       terminal_std;

    void           init();
    std::string    create_tmpfile(std::ofstream &tmp);
    static bool    get_program_path();
    bool file_available(const std::string &filename);
    static bool    file_exists(const std::string &filename, int mode=0);
};
