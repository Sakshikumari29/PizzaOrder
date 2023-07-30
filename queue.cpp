#include<queue>
#include<iostream>
using namespace std;

class Sample{

public:
int x,y;
Sample()
{
 x=10;
 y=20;
}
friend ostream& operator<<(ostream& out,  Sample& s);
};
ostream& operator<<(ostream& out,  Sample& s)
{
    out <<s.x<<endl;
 out<<s.y;
    return out;
}

int main()
{

queue<Sample> my;

for(int i=0;i<3;i++)
{
Sample s;
cout<<"x and y : ";
cin>>s.x;
cin>>s.y;
my.push(s);
}

cout<<my.front();
my.pop();
cout<<my.front();
return 0;
}
