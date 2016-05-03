#include "lineFitting.h"

using namespace std;

line::line()
{
    alfa = 0;
    r = 0;
}

line::line(float alfa, float r)
{
    this->alfa = alfa*(PI/180);
    this->r = r;
    b = (this->r)/sin(this->alfa);
    m = - 1 / tan(this->alfa);
}

float line::value_y(float x)
{
        return b + x*m;
}

float line::residual_error(vector<polar_point> pol_points)
{
    vector<Point> temp_points;
    temp_points = polar2descart(pol_points);

    Point firstpoint;
    Point lastpoint;
    double dist;
    double sum_dist;

    firstpoint.x = temp_points[0].x;
    firstpoint.y = this->value_y(temp_points[0].x);

    lastpoint.x = temp_points[temp_points.size()-1].x;
    lastpoint.y = this->value_y(temp_points[temp_points.size()-1].x);

    Point p=lastpoint-firstpoint;

    for(int i=1;i<temp_points.size()-1;i++)
    {
        Point pp=temp_points[i]-firstpoint;
        dist=fabs(pp * p) / p.Norm();
        sum_dist = sum_dist + dist;
    }
    return sum_dist;
}

vector<Point> line::line_graf(float x_1,float x_2)
{
    vector<Point> temp;
    Point temp_point;
    float x_i = x_1;
    float res = (x_2 - x_1)/100; // resolusion
    while( x_i < x_2 )
    {
        temp_point.x = x_i;
        temp_point.y = this->value_y(x_i);
        temp.push_back(temp_point);
        x_i = x_i + res;
    }
    return temp;
}

/*__________Polar Point_______________________________*/
polar_point::polar_point()
{
    alfa = 0;
    r = 0;
    weight = 1;
    in_line = true;
}

polar_point::polar_point(float alfa, float r)
{
    this->alfa = alfa*(PI/180);
    this->r = r;
    weight = 1;
    in_line = true;
}

polar_point::polar_point(float alfa, float r, float weight)
{
    this->alfa = alfa*(PI/180);
    this->r = r;
    this->weight = weight;
    in_line = true;
}

bool operator==(const polar_point& this_one, const polar_point& other_one)
{
    if( (this_one.alfa == other_one.alfa) && (this_one.r == other_one.r) )
        return true;
    else
        return false;
}

std::vector<polar_point> descart2polar(std::vector<Point>& Points)
{
    std::vector<polar_point> temp_vect;
    polar_point temp_point;
    for(int i = 0 ; i < Points.size();i++)
    {
        temp_point.r = sqrt( Points[i].x*Points[i].x + Points[i].y*Points[i].y );
        temp_point.alfa = atan2(Points[i].y,Points[i].x);
        temp_vect.push_back(temp_point);
    }
    return temp_vect;
}

std::vector<Point> polar2descart(std::vector<polar_point>& polar_Points)
{
    std:vector<Point> temp_vect;
    Point temp_point;
    for(int i = 0;i < polar_Points.size(); i++)
    {
        temp_point.x = cos(polar_Points[i].alfa)*polar_Points[i].r;
        temp_point.y = sin(polar_Points[i].alfa)*polar_Points[i].r;
        temp_vect.push_back(temp_point);
    }
    return temp_vect;
}

line lineFitting(std::vector<Point>& Points)
{
    float r;
    float alfa;
    vector<polar_point> polar_data;
    float sum_1 = 0;
    float sum_2 = 0;
    float sum_3 = 0;
    float sum_4 = 0;
    float sum_r = 0;
    polar_data = descart2polar(Points);
    float sum_var = 1 / (float)polar_data.size();


    for(int i= 0; i < polar_data.size();i++)
        for(int j = i + 1; j < polar_data.size(); j++)
            sum_1 = sum_1 + polar_data[i].r*polar_data[j].r*sin(polar_data[i].alfa +  polar_data[j].alfa);

    for(int i = 0;i < polar_data.size();i++)
        sum_2 = sum_2 + ( 1 - (float)polar_data.size() )*polar_data[i].r*polar_data[i].r*sin(2*polar_data[i].alfa);


    for(int i= 0; i < polar_data.size();i++)
        for(int j = i + 1; j < polar_data.size(); j++)
            sum_3 = sum_3 + polar_data[i].r*polar_data[j].r*cos(polar_data[i].alfa + polar_data[j].alfa);

    for(int i = 0;i < polar_data.size();i++)
        sum_4 = sum_4 + (1 - (float)polar_data.size())*polar_data[i].r*polar_data[i].r*cos(2*polar_data[i].alfa);

    float wi = (float)polar_data.size();

    alfa = 0.5*atan2( (2/wi)*sum_1 + (1/wi)*sum_2, (2/wi)*sum_3 +(1/wi)*sum_4 );

    for(int i = 0;i < polar_data.size();i++)
        sum_r = sum_r + polar_data[i].r*cos(polar_data[i].alfa - alfa);

    line linefit(alfa*180/PI,sum_r*sum_var);
    return linefit;
}


line lineFitting(std::vector<polar_point>& polar_Points)
{

    float r;
    float alfa;

    float sum_1 = 0;
    float sum_2 = 0;
    float sum_3 = 0;
    float sum_4 = 0;
    float sum_r = 0;
    vector<polar_point> polar_data;
    polar_data = polar_Points;
    float sum_var = 1 / (float)polar_data.size();

    for(int i= 0; i < polar_data.size();i++)
        for(int j = i + 1; j < polar_data.size(); j++)
            sum_1 = sum_1 + polar_data[i].r*polar_data[j].r*sin(polar_data[i].alfa +  polar_data[j].alfa);

    for(int i = 0;i < polar_data.size();i++)
    {
        sum_2 = sum_2 + ( 1 - (float)polar_data.size() )*polar_data[i].r*polar_data[i].r*sin(2*polar_data[i].alfa);
    }


    for(int i= 0; i < polar_data.size();i++)
        for(int j = i + 1; j < polar_data.size(); j++)
            sum_3 = sum_3 + polar_data[i].r*polar_data[j].r*cos(polar_data[i].alfa + polar_data[j].alfa);

    for(int i = 0;i < polar_data.size();i++)
    {
        sum_4 = sum_4 + (1 - (float)polar_data.size() )*polar_data[i].r*polar_data[i].r*cos(2*polar_data[i].alfa);
    }

    float wi = (float)polar_data.size();

    alfa = 0.5*atan2( (2/wi)*sum_1 + (1/wi)*sum_2, (2/wi)*sum_3 +(1/wi)*sum_4 );

    for(int i = 0;i < polar_data.size();i++)
        sum_r = sum_r + polar_data[i].r*cos(polar_data[i].alfa - alfa);

    line linefit(alfa*180/PI,sum_r*sum_var);
    return linefit;
}


/*_____________Line Extracion_______________*/

lineXtracion::lineXtracion()
{
}

lineXtracion::lineXtracion(vector<polar_point>& pol_points)
{
    this->pol_data = pol_points;
}

lineXtracion::lineXtracion(vector<Point>& points)
{
    this->pol_data = descart2polar(points);
}

void lineXtracion::Extract(void)
{
    simplifyPath black_magic;
    vector<polar_point> temp;
    temp = black_magic.simplifyWithRDP(this->pol_data);
    for(int i = 0; i < temp.size(); i++)
    {
        if( temp[i].in_line )
            this->fit_pol_points.push_back(temp[i]);
    }

    this->fit_points = polar2descart(this->fit_pol_points);
    temp.clear();
    vector<polar_point>::iterator line_begin;
    vector<polar_point>::iterator line_end;

    line temp_line;
    for(int i = 0; i < fit_pol_points.size(); i = i + 2)
    {
        line_begin = find(this->pol_data.begin(), this->pol_data.end(), fit_pol_points[i]);
        line_end = find(this->pol_data.begin(), this->pol_data.end(),fit_pol_points[i+1]);
        temp.insert(temp.begin(),line_begin,line_end);
        temp_line = lineFitting(temp);
        this->Fitlines.push_back(temp_line);
        temp.clear();
    }
}

vector<Point> lineXtracion::Result_export(void)
{
    this->fit_points = polar2descart(this->fit_pol_points);
    vector<Point> temp = polar2descart(this->pol_data);
    vector<Point> point_result;
    temp.clear();
    int j = 0;
    for(int i = 0; i < this->Fitlines.size();i++)
        {
            temp = this->Fitlines[i].line_graf(fit_points[j].x,fit_points[j + 1].x);
            point_result.insert(point_result.end(),temp.begin(),temp.end());
            temp.clear();
            j = j + 2;
        }
    return point_result;
}
