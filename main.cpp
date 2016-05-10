#include <iostream>
#include <fstream>
#include <random>

#include "simplifyPath.h"
#include "lineFitting.h"

using namespace std;

vector<Point> data_generate(line f_line, line s_line, int data_num)
{
    Point temp;
    vector<Point> data;
    line asd(40,30);
    default_random_engine general;
    normal_distribution<double> gauss_nois(0,0);
    for(int i = -data_num; i < 0; i++)
    {
        temp.x = i;
        temp.y = f_line.value_y(i) + gauss_nois(general);
        data.push_back(temp);
    }
    for(int i = 0; i < data_num ; i++)
    {
        temp.x = i;
        temp.y = 100*sin( (double)i / (data_num/4)) + 250;
        data.push_back(temp);
    }
       for(int i = data_num; i < 2*data_num; i++)
    {
        temp.x = i;
        temp.y = s_line.value_y(i) + gauss_nois(general);
        data.push_back(temp);
    }
     return data;
}

void ostream_points(iostream  stream, vector<Point>& Points)
{
    for(int i = 0;i < Points.size(); i++)
        stream<<Points[i].x<<","<<Points[i].y<<endl;
}


void osftream_points(const string name, vector<Point>& Points) // "name.txt" format
{
    ofstream data;
    data.open("asd.txt");
    for(int i = 0;i < Points.size(); i++)
        data<<Points[i].x<<","<<Points[i].y<<endl;
}

int main()
{
    default_random_engine general;
    double szoras;
    szoras = 10;
    normal_distribution<double> gauss_nois(0,szoras);
    double sum_p=0;
    double p=0;
    double sum_n;
    double n;
    double zaj;
    for(int i = 0;i < 100;i++)
    {
        zaj = gauss_nois(general);
        if( zaj > 0 )
            {
                sum_p = sum_p + zaj;
                p++;
            }
        else
            {
                sum_n = sum_n + zaj;
                n++;
            }
    }
    line f_l(135,150);
    line s_l(60,200);
    ofstream f_data;
    ofstream r_data;
    ofstream p_data;
    f_data.open("data.txt");
    r_data.open("r_data.txt");
    p_data.open("p_data.txt");
    std::vector<Point> data = data_generate(f_l,s_l,300);
    vector<polar_point> temp = descart2polar(data);
    for(int i= 0; i < temp.size();i++)
    {
        temp[i].r = (double)temp[i].r + gauss_nois(general);
        temp[i].weight = 1 / (szoras*szoras);
        temp[i].variance = szoras;
    }
    /*line a = lineFitting(temp);
    cout<< a.r<<" "<<a.alfa<<endl;
    cout<<a.residual_error(temp)<<endl;
    double sum_di = 0;
    for(int i = 0;i < temp.size();i++)
        sum_di = sum_di + abs(cos(temp[i].alfa - a.alfa))*4/(sqrt(2*PI));
    double sum_var;
    for(int i= 0; i < temp.size();i++)
        sum_var = sum_var + cos(temp[i].alfa - a.alfa)*cos(temp[i].alfa - a.alfa)*4*((PI - 2)/PI);
    cout<<sum_di + 1.5*sqrt(sum_var) <<endl;*/
    data = polar2descart(temp);
    for(int i = 0; i < data.size();i++)
        f_data<<data[i].x<<","<<data[i].y<<endl;
    lineXtracion get_lines(temp);
    get_lines.Extract();
    vector<Point> result =get_lines.fit_points;
    for(int i = 0; i < result.size();i++)
        r_data<<result[i].x<<","<<result[i].y<<endl;
    for(int i = 0; i < get_lines.Fitlines.size();i++)
        cout<<get_lines.Fitlines[i].alfa<<","<<get_lines.Fitlines[i].r<<endl;
    for(int i = 0 ;i < get_lines.fit_pol_points.size();i++)
        p_data<<get_lines.fit_pol_points[i].r<<","<<get_lines.fit_pol_points[i].alfa<<endl;
    get_lines.Export_polar();
    get_lines.Export_polar_data();
   /* for(int i = 0; i < result_polar.size(); i++)
    {
        if(result_polar[i].alfa < 0)
            {
                result_polar[i].alfa = 2*PI + result_polar[i].alfa;
            }
        r_data<<result_polar[i].alfa<<","<<result_polar[i].r<<endl;
    }*/


   /* line f_l(60,10);
    line s_l(-50,50);
    ofstream f_data;
    ofstream r_data;
    f_data.open("data.txt");
    r_data.open("r_data.txt");
    std::vector<Point> data = data_generate(f_l,s_l,100);
    for(int i = 0; i < data.size(); i++)
        f_data<<data[i].x<<","<<data[i].y<<endl;
    vector<polar_point> result;
    simplifyPath king;
    vector<polar_point> asd;
    asd = descart2polar(data);
    result = king.simplifyWithRDP(asd);
    vector<polar_point>   result_line_point;
    for(int i = 0;i<result.size();i++)
    {
        if( result[i].in_line )
            result_line_point.push_back(result[i]);

    }
    vector<Point> result_points;
    result_points = polar2descart(result_line_point);
    for(int i = 0;i < result_points.size();i++)
        cout<<result_points[i].x<<","<<result_points[i].y<<endl;


    for(int i = 0; i< result_line_point.size();i++)
        r_data<<result_points[i].x<<","<<result_points[i].y<<endl;*/
    /*line fit;
    fit = lineFitting(data);
    cout<<fit.alfa<<" "<<fit.r<<endl;
    for(int i= 0;i < 10;i++)
        {
            temp.x = i;
            temp.y = fit.value_y(i);
            cout<<fit.value_y(i)<<endl;
            result.push_back(temp);
        }
    for(int i = 0; i < data.size();i++)
        prob_data<<result[i].x<<","<<result[i].y<<endl;
    prob_data.close();*/
  /*  vector<polar_point> temp_pol;
    temp_pol = descart2polar(data);
    result = polar2descart(temp_pol);
    for(int i = 0; i < result.size();i++)
        cout<<result[i].x<<" "<<result[i].y<<endl;*/
    return 0;
}
