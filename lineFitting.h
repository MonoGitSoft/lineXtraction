#ifndef __lineFitting__H__
#define __lineFitting__H__

#include "simplifyPath.h"

#define PI 3.14159265

using namespace std;


std::vector<polar_point> descart2polar(std::vector<Point>& Points);

std::vector<Point> polar2descart(std::vector<polar_point>& Points);

line lineFitting(std::vector<Point>& Points);
line lineFitting(std::vector<polar_point>& polar_data);

class lineXtracion
{
    public:
        vector<polar_point> fit_pol_points;
        vector<Point> fit_points;
        lineXtracion();
        lineXtracion(vector<polar_point>& pol_points);
        lineXtracion(vector<Point>& points);
        void Extract(void);//Extract line from pol_data
        void Filter(int window); // Simple moving avarage "filter"
        void Export_polar();
        void Export_polar_data();
        vector<Point> Result_export(void);
        vector<line> Fitlines;
        vector<polar_point> pol_data;
};

#endif // __lineFitting__H__

