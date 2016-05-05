#include <string>
#include "simplifyPath.h"
#include "lineFitting.h"

using std::vector;
//Given an array of points, "findMaximumDistance" calculates the GPS point which have largest distance from the line formed by first and last points in RDP algorithm. Returns the index of the point in the array and the distance.


const std::pair<int, double> simplifyPath::findMaximumDistance(const vector<Point>& Points,line& at_line)const
{
  Point firstpoint;
  Point lastpoint;
  firstpoint.x = Points[0].x;
  lastpoint.x = Points[Points.size() - 1].x;
  firstpoint.y = at_line.value_y(firstpoint.x);
  lastpoint.y = at_line.value_y(lastpoint.x);
  int index=0;  //index to be returned
  double Mdist=-1; //the Maximum distance to be returned

  //distance calculation
  Point p=lastpoint-firstpoint;
  for(int i=1;i<Points.size();i++)
  { //traverse through second point to second last point
  Point pp=Points[i]-firstpoint;
  double Dist=fabs(pp * p) / p.Norm(); //formula for point-to-line distance
  if (Dist>Mdist)
  {
    Mdist=Dist;
    index=i;
  }
  }
  return std::make_pair(index, Mdist);
}

const std::pair<int, double> simplifyPath::findMaximumDistance(const vector<Point>& Points)const
{
    Point firstpoint=Points[0];
    Point lastpoint=Points[Points.size()-1];
  int index=0;  //index to be returned
  double Mdist=-1; //the Maximum distance to be returned

  //distance calculation
  Point p=lastpoint-firstpoint;
  for(int i=1;i<Points.size();i++)
  { //traverse through second point to second last point
  Point pp=Points[i]-firstpoint;
  double Dist=fabs(pp * p) / p.Norm(); //formula for point-to-line distance
  if (Dist>Mdist)
  {
    Mdist=Dist;
    index=i;
  }
  }
  return std::make_pair(index, Mdist);
}



vector<polar_point> simplifyPath::simplifyWithRDP(vector<polar_point>& polar_Points)
{

   if(polar_Points.size() < 3)
  {  //base case 1
    /*for(int i = 0; i < polar_Points.size();i++)
    { //if the result of the split is a small size points array  ( 3,4 ,5 small)
        polar_Points[i].in_line = false; // that those points probably aren't on a line.
    }*/
    polar_point temp;
    temp.in_line = false;
    vector<polar_point> temp_vect;
    temp_vect.push_back(temp);
    return temp_vect;
  }
    line p_s;
    p_s = lineFitting(polar_Points);

    vector<Point> temp_point;
    temp_point = polar2descart(polar_Points); // Calculate the index where we want to split
    std::pair<int, double> maxDistance=findMaximumDistance(temp_point);

    int index=maxDistance.first;
    vector<polar_point>::iterator it=polar_Points.begin();
    vector<polar_point> path1(polar_Points.begin(),it+index + 1); //new path l1 from 0 to index
    vector<polar_point> path2(it+index,polar_Points.end()); // new path l2 from index to last
                // split if interpretation gets better
    line p_e;
    line p_b;

    p_e = lineFitting(path1);
    p_b = lineFitting(path2);


    if( p_s.residual_error(polar_Points) > (p_e.residual_error(path1) + p_b.residual_error(path2)))
    {
    vector<polar_point> r1 =simplifyWithRDP(path1);
    vector<polar_point> r2=simplifyWithRDP(path2);

    vector<Point> r1_p= polar2descart(r1);
    vector<Point> r2_p= polar2descart(r2);

    //Concat simplified path1 and path2 together
    vector<polar_point> rs(r1);
    rs.insert(rs.end(),r2.begin(),r2.end());;
    return rs;
  }
  else
  { //base case 2, all points between are to be removed.
    vector<polar_point> r(1,polar_Points[0]);
      r.push_back(polar_Points[polar_Points.size()-1]);
    return r;
  }
}







