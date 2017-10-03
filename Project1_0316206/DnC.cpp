#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
class point
{
	public:
	double x;
	double y;	
};
double distance(point* a,point* b)
{
	double temp=(a->x-b->x)*(a->x-b->x)+(a->y-b->y)*(a->y-b->y);
	double ans;
	ans=sqrt(temp);
	return ans;
}
double which_min(double a,double b)
{
	if(a > b || a == b)
	{
		return b;
	}
	else{
		return a;
	}
}
bool compare_x(const point& lp,const point& rp)
{
	return lp.x<rp.x;
}
bool compare_y(const point& lp,const point& rp)
{
	return lp.y < rp.y;
}
double closest(int l,int r,vector<point> p)
{
	if(r-l+1<=2){
		if(l>=r) return 999999;
		else return distance(&p.at(r),&p.at(l));
	}
	else{
		int m = (l+r)/2;
		double d1 = closest(l,m,p);
		double d2 = closest(m+1,r,p);
		double d_1_2 = which_min(d1,d2);
		double min;
		min = d_1_2;
		
		
		vector<point> ans;
		for(int i=l;i<=r;i++)
		{
			if(abs(p[i].x-p[m].x)<d_1_2)
			{
				ans.push_back(p[i]);
			}
		}
		sort(ans.begin(),ans.end(),compare_y);
		for(int i=0;i<ans.size();i++)
		{
			for(int j=i+1;j<ans.size() && abs(ans[j].y-ans[i].y)<min;j++)
			{
				if(distance(&ans.at(i),&ans.at(j))<min)
				{
					min = distance(&ans[i],&ans[j]);
				}
			}
		}
		return min;
	}
}
int main()
{
	ifstream myf("test.txt");
	int  n;
	vector<point> p;
	myf>>n;
	p.resize(n);
	for(int i=0;i<n;i++)
	{
		myf>>p[i].x>>p[i].y;						
	}
	sort(p.begin(),p.end(),compare_x);//sort all points according to x coordinates
	if(n<=3)
	{
		double min;
		min=distance(&p.at(0),&p.at(1));
		for(int i=0;i<n;i++)
		{	
			for(int j=i+1;j<n;j++)
			{
				double temp = distance(&p.at(i),&p.at(j));
				if(temp<min)
				{
					min = temp;
				}
			}
		}
		cout<<"Shortest distance:"<<min;
	}
	else{
		cout<<"Shortest distance:"<<closest(0,n-1,p);	
	}
	myf.close();
	return 0;
}

