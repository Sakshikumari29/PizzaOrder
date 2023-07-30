#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
#include<queue>

using namespace std;

class Menu
{
public:
int code;
float price; char name[20];
///////////////  accept /////////////////////
void accept()
{
Menu m;
cout<<"Enter Pizza Code  :";cin>>m.code;
cout<<"Enter Pizza Name  :";cin>>m.name;
cin.ignore();
cout<<"Enter price : ";cin>>m.price;
ofstream mystream("Menu.txt",ios::app);

            mystream.write((char*)(&m),sizeof(Menu));
            mystream.close();
        }
        //////////////////// display ////////////////

void display()
{
Menu m;
cout<<"\t\t \t ----MENU---- \n\n";

cout<<setw(5)<<"Pizza code"<<" ";
            cout<<setw(30)<<"Pizza Name"<<" ";
            cout<<setw(10)<<"Price"<<endl;
            cout<<endl;
ifstream in("Menu.txt");
    while(!in.eof())
    {
   in.read((char*)(&m),sizeof(Menu));
            if (in.fail())
{
            break;
            }
	       cout<<setw(5)<<m.code<<"\t ";
            cout<<setw(30)<<m.name<<"\t ";
            cout<<setw(10)<<m.price<<endl;
		  
    }
           in.close();
}
/// search by Number //////////
Menu searchByNumber()
{
bool found=false;
long long int num;
Menu m;
cout<<"Enter Pizza Code : ";
cin>>num;
ifstream in("Menu.txt");
while(!in.eof())
            {
            in.read((char*)(&m),sizeof(Menu));
            if(in.fail())
            {
           
            break;
}
            if(num==m.code)
{
//cout<<"Number found \n ";
found=true;
cout<<m.code<<"---"<<m.name<<"----"<<m.price<<endl;
return m;
}

}
if(found==false)
{
cout<<"Pizza  not found \n";
}
in.close();
}


void update()
{
bool found=false;
Menu m;
int code;


cout<<"Enter Pizza Code to update Menu Number \n ";
cin>>code;
fstream in("Menu.txt");
while(!in.eof())
{
in.read((char*)(&m),sizeof(Menu));
if(in.fail())
{
break;
}
if(code==m.code)
{
found=true;
cout<<m.name<<"----"<<m.price<<endl;
cout<<"Enter updated Cost  : ";
cin>>m.price;


in.seekg(-sizeof(Menu), ios::cur);	
//fstream out("Menu.txt",ios::out);
in.write((char*)(&m),sizeof(Menu));
//out.close();
break;
}
}
if(found==false)
cout<<"Not founnd \n ";

in.close();
}

};
/////////////////////////////////////////////////////////////////////////////

class Customer
{
public:
int points=0;
long double number; char name[20];
///////////////  accept /////////////////////
void accept()
{
Customer cus;
cout<<"Enter Name  :";cin>>cus.name;
cin.ignore();
cout<<"Enter Phone Number : ";cin>>cus.number;
ofstream mystream("Customer.txt",ios::app);

            mystream.write((char*)(&cus),sizeof(Customer));
            mystream.close();
        }
        //////////////////// display ////////////////

void display()
{
Customer cus;
ifstream in("Customer.txt");
cout<<setw(20)<<"Name  : "<<" ";
            cout<<setw(20)<<"Number : "<<" ";
            cout<<setw(30)<<"Bonus Points : "<<endl;
            cout<<endl;
    while(!in.eof())
    {
   in.read((char*)(&cus),sizeof(Customer));
            if (in.fail())
{
            break;
            }
            cout<<setw(20)<<cus.name<<"\t ";
           cout <<std::fixed<<std::setprecision(0);
            cout<<setw(15)<<cus.number<<"\t ";
            cout<<setw(10)<<cus.points<<endl;
    }
           in.close();
}
/// search by Number //////////
Customer searchByNumber()
{
bool found=false;
long double num;
Customer cus;
cout<<"Enter Number : ";
cin>>num;
ifstream in("Customer.txt");
while(!in.eof())
            {
            in.read((char*)(&cus),sizeof(Customer));
            if(in.fail())
            {
           
            break;
}

if(num==cus.number)
{
cout<<"Number found \n ";
found=true;
cout<<cus.name<<"----"<<cus.number<<endl;
return cus;
}

}
if(found==false)
{
Customer cnot;
cnot.number=-999;
cout<<"NUmber not found \n";
return cnot;
}
in.close();
}
///////////////////////////////////////////////////
void updatePoints(float price)
{
 if(price<100)
 this->points=20;
 else if(price<200)
 this->points=30;
 else if(price<300)
 this->points=40;
else
this->points=50;
}


///////////update //////////////
void update()
{
bool found=false;
Customer cus;
char nameUpdate[20];

cout<<"Enter name to update Customer Number \n ";
cin>>nameUpdate;
fstream in("Customer.txt");
while(!in.eof())
{
in.read((char*)(&cus),sizeof(Customer));
if(in.fail())
{
break;
}
if(strcasecmp(nameUpdate,cus.name)==0)
{
found=true;
cout<<cus.name<<"----"<<cus.number<<endl;
cout<<"Enter new number  : ";
cin>>cus.number;


in.seekg(-sizeof(Customer), ios::cur);	
//fstream out("Customer.txt",ios::out);
in.write((char*)(&cus),sizeof(Customer));
//out.close();
break;
}
}
if(found==false)
cout<<"Not founnd \n ";

in.close();
}

};
//////////////////////////////////////////////////////////////////////////
class Pizza
{
public:
float price=-1;
float quantity;
char name[20];
void display()
{
cout<<"Name"<<this->name<<endl;
cout<<"Quantity"<<this->quantity<<endl;
cout<<"price"<<this->price	<<endl;
}

float priceF(); 
Pizza acceptPizza();
};

Pizza Pizza::acceptPizza()
{
Menu m,m1;
Pizza p;
int code;
//cout<<"Enter Pizza Code  : ";
//cin>>code;

m=m1.searchByNumber();
cout<<"Quantity :";
cin>>p.quantity;
for(int i=0;i<sizeof(p.name);++i)
{
p.name[i]=m.name[i];
}
p.price=p.quantity*m.price;
return p;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////\

class Order
{
public:
int count=-1;
friend class Shop;
Pizza p_arr[10];
int orderNo;
static int totalOrderNumber;
float total_price=0.0F;
friend ostream& operator<<(ostream& out,  Order& s);
};
ostream& operator<<(ostream& out,  Order& s)
{
    out <<s.total_price<<endl;
  for(int i=0;i<=s.count;i++)
 s.p_arr[i].display();
 

    return out;
}
int Order::totalOrderNumber=1;

class Shop
{

public:

queue <Order> orderQueue;
Order ord;
void displayMenu();
void placeOrder();
void deliver();
void displayCost(); // calls priceF() for all objects of pizza and displays total cost
void payment();
Customer acceptCus();
void displayBill();
void billCard();
int billCash();
void customerDetails();
void updateMenu();
};

void Shop::customerDetails()
{
int ch;
Customer cus;
cout<<"1. Store data \n 2. display \n 3. search by number \n 4. update \n 5. exit \n ";
cin>>ch;
switch(ch)
{
case 1 : cus.accept();
break;
case 2 : cus.display();
break;
case 3 : cus.searchByNumber();
break;
case 4 : cus.update();
break;

}

}
void Shop::placeOrder()
{
Pizza p;
int ch;

Shop s;
do
{
ord.count++;
ord.p_arr[ord.count]=p.acceptPizza();

//queue[0]=p_arr[count]

cout<<"Want to add more ? (0/1) : ";
cin>>ch;

}while(ch!=0);

for(int j=0;j<=ord.count;j++)
{
ord.total_price=ord.total_price + ord.p_arr[j].price;
}
cout<<"total price"<<ord.total_price<<endl;
 


}    

Customer Shop::acceptCus()
{
Customer c;
Customer found=c.searchByNumber();
if(found.number==-999)
	found.accept();
return found;


}
/////////////////////////////////
void Shop::payment()
{int ch;
Customer c;
c=acceptCus();
int point=c.points;
cout<<"Do you want to use Bonus Points ? (0/1)  :";
cin>>ch;
if(ch==1)
	{
	if(ord.total_price>point)
		{
		ord.total_price=ord.total_price-point;
		c.points=0;
		}
	else
		{
		ord.total_price=0;
		c.points=c.points-ord.total_price;
		}

	}
c.updatePoints(ord.total_price);
displayBill();
cout<<"Mode of Payment : \n 1.Card \t\t\t 2.Cash \n";
cin>>ch;
switch(ch)
{
case 1:billCard();
break;
case 2:{int c=billCash();
       if(c==0)
       return;
}
break;
}

cout<<"\nOrder number: "<<ord.totalOrderNumber<<endl;
ord.totalOrderNumber++;
cout<<"\n\tTHANK YOU..!!"<<endl;
orderQueue.push(ord);
}
/////////////////////////////////
void Shop::billCard()
{
string name;
int pin;
long double card_no;
cout<<"\nEnter card number: ";
cin>>card_no;
cout<<"\nEnter card holder name: ";
getline(cin,name);
cin.ignore();
cout<<"\nEnter pin : ";
cin>>pin;
cout<<"\nPayment done successfully...\n Rs."<<ord.total_price<<" is deducted from your account."<<endl;
}
/////////////////////////////////////////
int Shop::billCash()
{int count=3;
 int cash;
do{
 cout<<"\nEnter cash received(Rs.): ";
 cin>>cash;

 if(cash<ord.total_price)
 {
 count--;
 cout<<"\nInsufficient cash";
  }
 else
 { 
   int cash_ret = cash - ord.total_price ;
   cout<<"\nCash returned(Rs.) : "<<cash_ret;
   return 1;
 }

}while(count!=0);
if(count==0)
{
 return 0;
}
}

void Shop::displayBill()
{
Shop s;
int i=0;
while(ord.p_arr[i].price!=-1)
{
cout<<endl;
cout<<"\t"<<ord.p_arr[i].name<<"\t"<<ord.p_arr[i].quantity<<"\t"<<ord.p_arr[i].price<<endl;
++i;
}
cout<<"Total Price  : "<<ord.total_price<<endl;
}

void Shop::displayMenu()
{
Menu m;
m.display();
}

void Shop::updateMenu()
{
Menu m;
int ch;
cout<<"\t\t 1. Add Menu \n\t\t 2.Update Menu\n";
cin>>ch;
switch(ch)
{
case 1 :m.accept();
break;
case 2:m.update();
break;
}
}

void Shop::deliver(){
cout<<orderQueue.front();
orderQueue.pop();
}

int main()
{

Menu m;
Customer cus;
Shop s;
int ch;
do
{
//system("clear");
cout<<"\n\t *******PIZZA TAPRI******* \n\t________________________________\n\n \t\t1.Display Menu \n\t\t2.Place Order \n\t\t3.Generate Bill \n\t\t4.Customer Details \n\t\t5.Update Menu \n\t\t6. Deliver\n\t\t\ 7.Exit \n\t________________________________\n\n ";
cout<<"Enter your choice: ";
cin>>ch;
cout<<endl; 
switch(ch)
{
case 1 :{s.displayMenu();
         //cin.ignore(1024, '\n');
         //cin.get();
        }
        break;

case 2 :s.displayMenu();
        s.placeOrder();
        break;
case 3:s.payment();
       
       break;

case 4:s.customerDetails();
        break;

case 5:s.updateMenu();
       break;

case 6:s.deliver();
break;
case 7:break;
}
}
while(ch!=7);
return 0;
}









