//error with deposit and withdrawal functions
#include <iostream>
#include<fstream>
#include<cstdio>
#include<string.h>
using namespace std;
class Bank
{
private:
    double bal;
    int accno=0;
    string f_name,l_name;
    int pass;
public:
    Bank(){};
    void open_Account(string f,string l,double dep);
    void Balance(int no);
    void Deposit(int no,double amt);
    void Withdraw(int no,double amt);
    void Close(int no);
    void Show_all(int pas);
    void disp();//General function to display
};
void Bank::disp()
{
    cout<<"Account number: "<<accno<<endl;
    cout<<"First Name :"<<f_name<<endl;
    cout<<"Last Name :"<<l_name<<endl;
    cout<<"Balance: "<<bal<<endl;
}
void Bank::open_Account(string f,string l,double dep)
{
    ifstream i;
    i.open("No.txt");
    if(!i.is_open())
        accno=0;
    else
        i>>accno;
    i.close();
    accno+=1;
    ofstream o ("No.txt");
    o<<accno;
    o.close();
    f_name=f;
    l_name=l;
    bal=dep;
    ofstream o1("Accounts.txt",ios::app);
    o1<<accno<<endl;
    o1<<f_name<<endl;
    o1<<l_name<<endl;
    o1<<bal<<endl;
    o1.close();
    cout<<"Account has been successfully created"<<endl;
    cout<<"Your account number is :"<<accno<<endl;
}
void Bank::Balance(int no)
{
    ifstream i;
    i.open("Accounts.txt");
    int temp=0;
    while(!i.eof())
    {
        i>>accno;
        i>>f_name;
        i>>l_name;
        i>>bal;
        if (no == accno)
        {
            temp=1;
            disp();
            break;
        }
    }
    if(temp==0)
        cout<<"Account does not exist"<<endl;
    i.close();
}
void Bank::Deposit(int no,double amt)
{
    ifstream i;
    i.open("Accounts.txt");
    ofstream o("Temp.txt");
    int temp=0;
    while(i>>accno)
    {
            i>>f_name;
            i>>l_name;
            i>>bal;
            if (no == accno)
            {
                temp=1;
                bal+=amt;
                cout<<"New balance: "<<bal<<endl;
            }
            o<<accno<<endl;
            o<<f_name<<endl;
            o<<l_name<<endl;
            o<<bal<<endl;
    }
    i.close();
    o.close();
    if(temp==0)
        cout<<"Account does not exist"<<endl;
    remove("Accounts.txt");
    rename("Temp.txt","Accounts.txt");
}
void Bank::Withdraw(int no,double amt)
{
    ifstream i;
    i.open("Accounts.txt");
    ofstream o("Temp.txt");
    int temp=0;
    while(i>>accno)
    {
         i>>f_name;
         i>>l_name;
         i>>bal;
         if (no == accno)
        {
            temp=1;
            if(bal<amt)
            {
                 cout<<"Insufficient funds"<<endl;
            }
            else
            {
                bal-=amt;
                cout<<"New balance"<<bal<<endl;
            }

        }
        o<<accno<<endl;;
        o<<f_name<<endl;;
        o<<l_name<<endl;;
        o<<bal<<endl;;


    }
    i.close();
    o.close();
    if (temp==0)
        cout<<"Account does not exist"<<endl;
    remove("Accounts.txt");
    rename("Temp.txt","Accounts.txt");
}
void Bank::Close(int no)
{
    int temp=0;
    ifstream i;
    i.open("Accounts.txt");
    ofstream o("Temp.txt");
    while(!i.eof())
    {
        i>>accno;
        i>>f_name;
        i>>l_name;
        i>>bal;
        if (no == accno)
        {
            temp=1;
        }
        else
        {
            o<<accno<<endl;
            o<<f_name<<endl;
            o<<l_name<<endl;
            o<<bal<<endl;
        }
    }
    i.close();
    o.close();
    remove("Accounts.txt");
    rename("Temp.txt","Accounts.txt");
    if(temp==0)
        cout<<"Account does not exist"<<endl;
    else
        cout<<"Account has been successfully removed"<<endl;
}
void Bank::Show_all(int pass)
{
    ifstream i;
    ifstream i2;
    i.open("Accounts.txt");
    i2.open("Password.txt");
    int p=0;
    i2>>p;
    i2.close();
    if (pass==p)
    {
        cout<<"Access granted"<<endl;
        while(i>>accno)
        {
            i>>f_name;
            i>>l_name;
            i>>bal;
            disp();
        }
    }
    else
        cout<<"Access denied"<<endl;
    i.close();
}
int main()
{
    int c=0;
    while(c!=7)
    {
        cout<<"1.Open Account"<<endl;
        cout<<"2.Balance Enquiry"<<endl;
        cout<<"3.Deposit"<<endl;
        cout<<"4.Withdrawal"<<endl;
        cout<<"5.Close Account"<<endl;
        cout<<"6.Show all Accounts"<<endl;
        cout<<"7.Quit"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>c;
        Bank b1;
        switch(c)
        {
        case 1:
            {
                string f,l;
                double dep;
                cout<<"Enter first name"<<endl;
                cin>>f;
                cout<<"Enter last name"<<endl;
                cin>>l;
                cout<<"Enter starting deposit"<<endl;
                cin>>dep;
                while(dep<2000)//to check for minimum deposit
                {
                    cout<<"Minimum value of starting deposit has to be 2000 INR please try again"<<endl;
                    cout<<"Enter starting deposit"<<endl;
                    cin>>dep;
                }
                b1.open_Account(f,l,dep);
                break;
            }
        case 2:
            {
                int no;
                cout<<"Enter your account number"<<endl;
                cin>>no;
                b1.Balance(no);
                break;
            }
        case 3:
            {
                int no;
                double amt;
                cout<<"Enter account number"<<endl;
                cin>>no;
                cout<<"Enter amount to deposit"<<endl;
                cin>>amt;
                b1.Deposit(no,amt);
                break;
            }
        case 4:
            {
                int no;
                double amt;
                cout<<"Enter account number"<<endl;
                cin>>no;
                cout<<"Enter amount to withdraw"<<endl;
                cin>>amt;
                b1.Withdraw(no,amt);
                break;
            }
        case 5:
            {
                int no;
                cout<<"Enter account number"<<endl;
                cin>>no;
                b1.Close(no);
                break;
            }
        case 6:
            {
                int pas=0;
                cout<<"This is an admin function please enter the four digit password"<<endl;
                cin>>pas;
                b1.Show_all(pas);
                break;
            }
        case 7:
            {
                cout<<"Thank you for working with our bank"<<endl;
                break;
            }
        default:
            {
                cout<<"Wrong input please try again"<<endl;
                break;
            }
        }
    }

    return 0;
}
