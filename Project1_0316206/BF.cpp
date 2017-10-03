#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;
double distance(double ax,double ay,double bx,double by)
{
	double ans,temp1,temp2,temp;
	temp1 = ax-bx;
	temp2 = ay-by;
	temp = pow(temp1,2)+pow(temp2,2);
	ans = sqrt(temp);
	return ans;
}
int main()
{
	ifstream myf("test.txt");
	int  n;
	int k=pow(2,16);
	double x[k],y[k];
	myf>>n;
	for(int i=0;i<n;i++)
	{
		myf>>x[i]>>y[i];					
	}		
	double min = distance(x[0],y[0],x[1],y[1]);
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			double temp = distance(x[i],y[i],x[j],y[j]);
			if(temp<min)
			{
				min = temp;
			}
		}
	}
	cout<<"Shortest distance:"<<min;
	myf.close();
	return 0;
}
