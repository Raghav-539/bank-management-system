/* Welcome to Bank System Project  */
/* In this project we are creating a bank system that will contain user and accounts created. */
/* Project Created on - 10 Sept 2022 */

/* For detail information please go to read me file. */

/* Headers used */

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <cstring>
#include <time.h>
#include <sstream>
#include <cstdlib>


using namespace std;

void temp_file_clear();  //for clearing tempeorary files
void copy_content(string a,string b); //global declaration
void number_system_put(int n1);
int number_system_get(); //account number automation
string yearadd(string date1,int year); //for calculating year
void user_menu(int);


void clrscr()
{
    cout << string(100, '\n');
}


/* Classes Used */

/* User Manual Class */

class Manual{
    public:
    void user_guide();
};

void Manual :: user_guide()
{
    cout << "*** Welcome TO Bank Management System ***" << endl;
    cout << endl;
    cout << "** Related Topics: **" << endl;
    cout << "1. How to open new account ? " << endl;
    cout << "-> Use the second option 'Open new account' " << endl;
    cout << "2. You need to remeber your account number and password to login to access your account. " << endl;
    cout << endl;
    cout << "-> Thanks for reading the user manual. " << endl;
}

/* User Class */

class User{
    public:
    char fname[20],lname[20];
    string phone_number;
    string dob;

    User()
    {
        phone_number = '\0';
        dob = '\0';
    }
};


/* Account Class inheriting user properties */

class Account : public User {
    int accountNumber;
    int password;
    int balance;
    string accountType;
    public:
    Account()
    {
        accountNumber = 0;
        password = 0;
        balance = 0;
    }

	void login_user(int,int);	        // user login function
	void createAccount(); 		        // function for openning new account
    void currentBalance(int);	        // balance chack
	void searchDetails(int);	        // function to search details of perticular user
	void delete_details();		        // function for deleting record
	void showDetails(); 		        // function for showing account details
	void addMoney(int,int);             // add Money
	void withdrawMoney(int,int);	 	// withdraw Money
	void ministatement(int);            // function for ministatement
	void tranferMoney(int);             // for tranfering fund between two users
	void cerateFD(int);                 // create an fd
	void viewFD(int);                   // view an fd
	void viewTrans(int);                // view all transections
	void update_details(int); 	        // function for updating record

};


void Account :: login_user(int user, int pass)
{
    int flag = 0;

    // getting data from file
    ifstream file_read("customer_details.txt",ios::in);
    while (!file_read.eof())
    {
        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;
        if(file_read.eof())
        {
            break;
        }
        if(user == accountNumber && pass == password)
        {
            cout << "\n Login Successful !" << endl;
            user_menu(user);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        cout << "\n User name and Password not matched !" << endl;
    }
    file_read.close();
}

void Account :: createAccount()
{
    cout << "Enter your First Name: ";
    cin >> fname;
    cin.clear();

    cout << "Enter your Last Name: ";
    cin >> lname;
    cin.clear();

    string temp_phone;
    cout << "Enter your phone number: ";
    cin >> temp_phone;
    cin.clear();
    if(temp_phone.length()==10)
    {
        phone_number = temp_phone;
    }
    else{
        while(temp_phone.length()==10)
        {
            cout << "Phone number must be 10 digits! " << endl;
            cout << "Enter 10 digit number: ";
            cin >> temp_phone;
            phone_number = temp_phone;
        }
    }

    cout << "\nEnter Date of Birth :";
	cin >>dob;
	cin.ignore();

	char acctype ='\0';
	cout <<"\nSelect Account Type(Savings S/Other O) :";
	cin >>acctype;
	if(tolower(acctype) == 's' )
	{
		accountType = "SAVINGS";
	}
	else
	{
		accountType = "OTHER";
	}
	accountNumber = number_system_get();

	cout << "\n Your Account Number : "<< accountNumber;

	cout << "\n Enter 4 digit Passcode : ";
	cin >> password;

	cout <<"\n Enter Primary Balance :";
	cin >> balance;

	ofstream file("customer_details.txt",ios::out | ios :: app);
	file << fname <<" "<< lname <<" "<< phone_number <<" "<< dob <<" "<< accountType <<" "<< accountNumber <<" "<< password <<" "<< balance <<endl;

	number_system_put(accountNumber);
	file.close();
}


void Account :: currentBalance(int user_number)
{
	Account();
	ifstream file_read("customer_details.txt" ,ios::in);
	while(file_read)
	{
        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

        if(user_number == accountNumber)
        {
            cout<<"\n Current Balance          : "<< balance <<"/-RS.";
        }
	}

	file_read.close();
}

void Account :: searchDetails(int user_number) 
{
	int choice;
	int flag = 0;
	Account();
	ifstream file_read("customer_details.txt" ,ios::in);


	while(file_read)
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

        if(user_number == accountNumber)
        {
            cout<<"\n Account Number is :"<< accountNumber;
            cout<<"\n Name              :"<< fname<<" "<< lname;
            cout<<"\n Phone             :"<< phone_number;
            cout<<"\n Date of birth     :"<< dob;
            cout<<"\n Account Type      :"<< accountType;
            cout<<"\n Balance           :"<< balance <<"/-RS.";
            cout<<"\n\n";
            flag  = 1;
        }

	}
	if(flag != 1)
	{
		cout << "\n No record found";
	}
	file_read.close();

}

void Account ::delete_details()
{
	char choice[10];
	char buff;
	int flag = 0;
	string a = "customer_details.txt";
	string b = "temp.txt";

	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	cout <<"\n Enter name: ";
	cin >> choice;
	cin.clear();

	while(!file_read.eof())
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }
		if(strcmp(fname,choice) == 0)
		{
			cout <<fname<<" "<<lname<<"\t"<<dob<<"\t"<<phone_number<<"\t"<< accountType <<"\t"<<accountNumber<<"\t"<<balance <<endl;
			flag  = 1;
		}
		else{
			file_temp << fname <<" "<<lname<<" "<< phone_number <<" "<<dob<<" "<<accountType<<" "<<accountNumber<<" "<< password <<" "<< balance << endl;
		}

	}
	if(flag != 1)
	{
		cout << "\n No record found" << endl;
	}

	file_temp.close();
	file_read.close();
	copy_content(b,a);

	cout<<"\n Done Account Is Removed !" << endl;
	temp_file_clear();
}  

void Account :: addMoney(int user_no,int amt)
{
	string a = "customer_details.txt";
	string b = "temp.txt";
	char tr_date[9];

	Account();
	ifstream file_read("customer_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transactions.txt",ios::out | ios::app);
	while(!file_read.eof())
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

        if(user_no == accountNumber)
        {
            balance = balance + amt;
            _strdate(tr_date);

            file_temp << fname <<" "<< lname<<" "<< phone_number <<" "<<dob<<" "<< accountType <<" " << accountNumber <<" "<<password<<" "<<balance<<endl;
            tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl;
        }else{
            file_temp << fname <<" "<< lname<<" "<< phone_number <<" "<<dob<<" "<< accountType <<" " << accountNumber <<" "<<password<<" "<<balance<<endl;
        }

	}

	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n Done ! Amount Added" << endl; 
	temp_file_clear();

}


void Account :: withdrawMoney(int user_no,int amt)
{
	string a = "customer_details.txt";
	string b = "temp.txt";
	char tr_date[9];

	int flag = 0;
	Account();
	ifstream file_read("customer_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transactions.txt",ios::out | ios::app);
	while(!file_read.eof())
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

        if(user_no == accountNumber)
        {
            if(balance != 0 && balance > amt)
            {

                balance = balance - amt;
                _strdate(tr_date); //saving current date

                file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
                tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"DR"<<endl;
                flag = 1;
            }
            else
            {
                cout<<"\n Your transection can not be completed balance is Zero or Less than withdrawal amount! " << endl;
                file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
            }
        }

        else
        {
            file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
        }

	}

	file_temp.close();
	file_read.close();
	copy_content(b,a);
	if(flag == 1)
	{
		cout<<"\n Done ! Amount Deducted" << endl;

	}

	temp_file_clear();

}

void Account::ministatement(int user_no)
{
	int number,amount,flag = 0,pbalance = 0;
	string date,status;
	char today[9];
	_strdate(today);
	Account();
	ifstream file_read("customer_details.txt" ,ios::in);

	while(file_read)
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

            if(user_no == accountNumber)
            {
                pbalance = balance;
            }
	}

	file_read.close();
	//transaction part

	cout<<"\n Mini statement for "<< today <<endl;
	cout<<"\n";
	cout<<"\n Account Number : "<<accountNumber<<endl;
	cout<<"\n\n";

	ifstream tr_file_read("transec.txt" ,ios::in);
	cout<<"\n "<<"Date" <<" | "<<"Amount"<<" | "<<"CR / DR "<<endl;

	while(tr_file_read)
	{
		tr_file_read >>number;
		tr_file_read >>date;
		tr_file_read >>amount;
		tr_file_read >>status;
        if(tr_file_read.eof())
        {
            break;
        }

        if(user_no == number)
        {
            cout<<"\t"<<date<<" | "<< amount <<" | "<<status<<" | "<<endl ;
            flag  = 1;
        }


	}
	if(flag != 1)
	{
		cout << "\nNo record found";
	}
	cout<<"\n\n";
	cout<<"Total Primary Balance :"<<pbalance<<"/."<<endl;
	tr_file_read.close();

}



void Account::tranferMoney(int user_no)
{
	int user2_no ,amt =0,flag = 0;
	char ans;

	cout <<"\nEnter Friends Account Numbber: ";
	cin >> user2_no;

	cout <<"\nEnter Amount : ";
	cin >> amt;

	string a = "customer_details.txt";
	string b = "temp.txt";
	char tr_date[9];

	Account();
	ifstream file_read("customer_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream tr_write("transactions.txt",ios::out | ios::app);
	while(!file_read.eof())
	{

	file_read >> fname;
	file_read >> lname;
	file_read >> phone_number;
	file_read >> dob;
	file_read >> accountType;
	file_read >> accountNumber;
	file_read >> password;
	file_read >> balance;

	if(file_read.eof())
	{
		break;
	}

	if(user2_no == accountNumber)
	{
		cout << "\nAccount Holder's name :"<<fname<< " "<<lname<<endl;
		cout<<"enter(Y/N): ";
		cin >>ans;

		if(ans == 'n')
		{
			flag = 1;
			break;
		}


		balance = balance + amt;
		_strdate(tr_date);

		file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;

		tr_write<<accountNumber<<" "<<tr_date<<" "<<amt<<" "<<"CR"<<endl;

	}
	else
	{
	    file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
	}

	}

	if(flag == 1)
	{
		cout <<"\n NO Account Found";
	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);
	cout<<"\n Done ! Amount Added\n";
	temp_file_clear();

	//now time for deducting amount from main user
	withdrawMoney(user_no,amt);
	cout << "\n Money Successfully Transferd !";
}

void Account::cerateFD(int user_no)
{
	int flag = 0,f_plan;
	string f_fname,f_lname,f_startdate,f_enddate;
	int f_amount,f_finalAmount = 0,f_time;
	float f_intrestAmount=0;
	float f_rate = 0.06 ;
	char tr_date[9]; //for autometic date
	cout<<"\n Enter First name for FD:";
	cin>>f_fname;
	cout<<"\n Enter Last name For FD:";
	cin>>f_lname;
	cout<<"\n Enter Amount ";
	cin>>f_amount;
	cout<<"\n enter Current Date:";
	cin>>f_startdate;

	cout<<"\n\t\tSelect Plan:\n";
	cout<<"\n\t\t1.Fd For 12 Month Intrest rate is 6%" << endl;
	cout<<"\n\t\t2.Fd For 24 Month Intrest rate is 8%" << endl;
	cout<<"\n\t\t3.Fd For 36 Month Intrest rate is 10%" << endl;
	cin>>f_plan;
	cin.clear();

	if(f_plan == 1)
	{
		f_rate=0.06;
		f_time=1;
	}
	else if(f_plan == 2)
	{
		f_rate=0.08;
		f_time=2;

	}
	else if(f_plan == 3)
	{
		f_rate=0.1;
		f_time=3;
	}
	else
	{
		cout<<"\n\t Default 6% rate is selected !\n";
		f_rate = 0.06;
		f_time = 1;
	}

	f_enddate = yearadd(f_startdate,f_time);
	string a = "customer_details.txt";
	string b = "temp.txt";
	Account();//constructor call to empty variables;
	ifstream file_read("customer_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);
	ofstream fd_file("fd.txt",ios::out | ios::app);
	ofstream tr_write("transactions.txt",ios::out | ios::app);

	_strdate(tr_date); //time.h ,function for saving current date
	while(!file_read.eof())
	{

	file_read >> fname;
	file_read >> lname;
	file_read >> phone_number;
	file_read >> dob;
	file_read >> accountType;
	file_read >> accountNumber;
	file_read >> password;
	file_read >> balance;

	if(file_read.eof())
	{
		break;
	}

	if(user_no == accountNumber)
	{
		if(balance != 0 && balance > f_amount)
		{
	        balance = balance - f_amount;

			f_intrestAmount = f_amount * f_rate * f_time;
			f_finalAmount=  f_amount + f_intrestAmount;

			cout<<"\n\tIntrest rate:"<<f_rate<<"\n\tIntrest Amount:"<<f_intrestAmount <<"\n\tTotal Amount When FD Completed:"<<f_finalAmount<<endl;

			file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
			fd_file<<accountNumber<<" "<<f_fname<<" "<<f_lname<<" "<<f_startdate <<" "<<f_enddate<<" "<<f_time<<" "<<f_amount <<" "<<f_intrestAmount <<" "<<f_finalAmount<<endl ;
			tr_write<<accountNumber<<" "<<tr_date<<" "<<f_amount<<" "<<"DR"<<endl;
			flag = 1;
		}
		else
		{
			cout<<"\n FD Amount Must Be Less than Primary Balance! " <<endl;
			file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
		}
	}
	else
	{
		file_temp << fname <<" "<< lname <<" "<< phone_number <<" "<<dob<<" "<< accountType <<" "<<accountNumber<<" "<< password <<" "<< balance <<endl;
	}

	}

	file_temp.close();
	file_read.close();
	fd_file.close();
	copy_content(b,a);
	if(flag == 1)
	{
		cout<<"\n Done !FD created" << endl;
	}

	temp_file_clear();

}

void Account::viewFD(int user_no)
{
	int flag = 0,f_plan,f_number;
	string f_fname,f_lname,f_startdate,f_enddate;
	int f_amount,f_finalAmount = 0,f_time;
	float f_intrestAmount=0;
	float f_rate =0.0;

	ifstream fd_file_read("fd.txt" ,ios::in);

	cout<<"\n"<<"Name"<<" |"<<"StartDate"<<" |"<<"EndDate"<<" |"<<"Years"<<" |"<<"Amount"<<" |"<<"Intrest"<<" |"<<"FAmount"<<endl;
	cout<<string(60,'_');
	while(fd_file_read)
	{
		fd_file_read >>f_number;
		fd_file_read >>f_fname;
		fd_file_read >>f_lname;
		fd_file_read >>f_startdate;
		fd_file_read >>f_enddate;
		fd_file_read >>f_time;
		fd_file_read >>f_amount;
		fd_file_read >>f_intrestAmount;
		fd_file_read >>f_finalAmount;

        if(fd_file_read.eof())
        {
            break;
        }

        if(user_no == f_number)
        {
            cout<<"\n"<<f_fname<<" "<<f_lname<<" |"<<f_startdate<<" |"<<f_enddate<<" |"<<f_time<<" |"<<f_amount<<" |"<<f_intrestAmount<<" |"<<f_finalAmount<<endl ;
            flag  = 1;
        }

	}
	if(flag != 1)
	{
		cout << "\n No record found" << endl;
	}
	fd_file_read.close();

}

void Account::viewTrans(int user_no)
{

	int number,amount,flag = 0;
	string date,status;

	ifstream tr_file_read("transactions.txt" ,ios::in);

	cout<<"\n\t"<<"AccountNumber"<<" | "<<"Date" <<" | "<<"Amount"<<" | "<<"CR / DR "<<endl;

	while(tr_file_read)
	{
        tr_file_read >>number;
        tr_file_read >>date;
        tr_file_read >>amount;
        tr_file_read >>status;
        if(tr_file_read.eof())
        {
            break;
        }

        if(user_no == number)
        {
            cout<<"\t"<<number<<" | "<<date<<" | "<< amount <<" | "<<status<<" | "<<endl;
            flag  = 1;
        }

	}
	if(flag != 1)
	{
		cout << "\n No record found" << endl;
	}
	tr_file_read.close();
}


void Account ::update_details(int user_no)
{
	int ch;
	char buff;
	int flag = 0;
	string a = "customer_details.txt";
	string b = "temp.txt";

	Account();
	ifstream file_read("cus_details.txt" ,ios::in);
	ofstream file_temp("temp.txt",ios::out |ios::app);

	while(!file_read.eof())
	{

        file_read >> fname;
        file_read >> lname;
        file_read >> phone_number;
        file_read >> dob;
        file_read >> accountType;
        file_read >> accountNumber;
        file_read >> password;
        file_read >> balance;

        if(file_read.eof())
        {
            break;
        }

        if(user_no == accountNumber)
        {
            cout <<"\nAccount Number is : "<<accountNumber;
            cout <<"\n Fill up Details with new records :" << endl;

            cout<<"\n\n New First name:";

            cin >>fname;
            cin.clear();

            cout <<"\n New Last name:";
            cin >> lname;
            cin.clear();

            cout <<"\n New  phone:";
            cin >> phone_number;
            cin.clear();

            cout <<"\n New Dob";
            cin >> dob;
            cin.clear();

            cout <<"\n Current Account Type:"<<accountType;
            cout <<"\n Change Type (Saving S/Other O) otherwiese press (N) :";
            char ans;
            cin >> ans;
            cin.clear();
            if(tolower(ans) == 'n')
            {
                cout <<"\nOk !account type is not changed !" << endl;
            }
            else if(tolower(ans) == 's')
            {
                accountType = "SAVING";
            }
            else
            {
                accountType = "OTHER";
            }
            file_temp << fname <<" "<<lname<<" "<< phone_number<<" "<<dob<<" "<<accountType<<" "<<accountNumber<<" "<<password<<" "<<balance<<endl;
            flag  = 1;
        }
        else
        {
            file_temp << fname <<" "<<lname<<" "<< phone_number <<" "<<dob<<" "<<accountType<<" "<<accountNumber<<" "<<password<<" "<<balance<<endl;
        }

	}
	if(flag != 1)
	{
		cout << "\n No record found" << endl;

	}
	file_temp.close();
	file_read.close();
	copy_content(b,a);

	cout<< "\n Done ! Details Updated Thank You." << endl;
	temp_file_clear();

}

/* copy content function for copy text to other file */
void copy_content(string a,string b)
{
	char ch;
	int flag = 0;
	ifstream temp_read(a.c_str(),ios :: in);
	ofstream file_write(b.c_str(),ios::out);
	while(!temp_read.eof())
	{
		temp_read.get(ch);
		file_write.put(ch);
		flag = 1;
	}
	if(flag != 1)
	{
		cout <<"\nFile Error !" << endl;
	}
}


//functions for account number automation
int number_system_get()
{
	int number;
	ifstream number_read("number.txt",ios::in);
	number_read >>number;
	return number;
}

void number_system_put(int n1)
{
	n1 = n1+1;
	ofstream number_write("number.txt",ios::out);
	number_write <<n1;
}

//function for clearing temp file
void temp_file_clear()
{

	char ch;
	int flag = 0;
	ofstream temp_write("temp.txt",ios :: out);

	temp_write <<" ";
	temp_write.close();

}

//function for calculating year
string yearadd(string date1,int year)
{
	int add ;
	string date2;
	stringstream ss(date1.substr(6,4));
	stringstream ss2(date1.substr(0,6));
	stringstream ss3;
	string s2; //for remaining part
	ss2 >> s2;
	ss >> add;
	add = add + year;
	ss3 << add;
	date2 = s2 + ss3.str();

	return date2;
}


//menu for register user
void user_menu(int user_session)
{
	int ch;
	int amount = 0;
	Account a;
	do{
		cout<<"Welcome your account number is : "<<user_session<<endl;
		cout<<"\n\t 1.View Your Account.";
		cout<<"\n\t 2.Update Your Details.";
		cout<<"\n\t 3.Transfer Fund.";
		cout<<"\n\t 4.Withdrawal.";
		cout<<"\n\t 5.Add Money.";
		cout<<"\n\t 6.View Transaction.";
		cout<<"\n\t 7.Close Account.";
		cout<<"\n\t 8.Create A FD";
		cout<<"\n\t 9.View All FD";
		cout<<"\n\t 10.MiniStatement";
		cout<<"\n\t 0.Exit";

		cout<<"\n\t Enter your Choice (1-7)::";
        if(cin >> ch)
        {
            switch (ch)
            {
                case 1:
                    system("cls");
                    a.searchDetails(user_session);
                    break;

                case 2:
                    system("cls");
                    a.update_details(user_session);
                    break;

                case 3:
                    system("cls");
                    a.tranferMoney(user_session);
                    break;

                case 4:
                    cout<<"\n Enter Amount to withdraw :";
                    cin >> amount;

                    a.withdrawMoney(user_session,amount);
                    break;

                case 5:
                    cout<<"\nEnter Amount to Add : ";
                    cin >> amount;
                    a.addMoney(user_session,amount);
                    a.currentBalance(user_session);
                    break;

                case 6:
                    a.viewTrans(user_session);
                    break;

                case 7:
                    a.delete_details();
                    break;
                case 8:
                    a.cerateFD(user_session);
                    break;
                case 9:
                    a.viewFD(user_session);
                    break;
                case 10:
                    a.ministatement(user_session);
                    break;

                default :
                    cout<<"\n Worng choise " << endl;
                    break;
            }
        }
		else
		{
			cout<<"\n Input only Digits please !";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15;
		}

	}while(ch != 0);

}

/* Driver Code */

int main()
{
int ch;
	int login_state = 0;
	int user;
	int pass;
	Account a;
	Manual m;

	do{

		system("cls");
		cout<<"\n Welcome to Bank management System "<<endl;
		cout<<endl;

		cout <<"\n\t 1.Login To your Account.";
		cout <<"\n\t 2.Open An Account.";
		cout <<"\n\t 3.User Manual.";
		cout <<"\n\t 0.Exit";

		cout<<"\n Enter your choice: ";
		if(cin >> ch )
		{
			switch (ch)
			{
				case 1:
					cout << "\n\t Enter Account Number:";
					cin >>user;
					cout <<"\n\t Enter 4-digit passcode :";
					cin >>pass;
					system("cls");
					a.login_user(user,pass);

				break;
				case 2:
					a.createAccount();
					break;

				case 3:
				m.user_guide();
				getch();
					break;

			}
		}
		else
		{
			cout<<"\n Input only Digits please ! Press Enter To continue : ";
			getch();
			cin.clear();
		 	cin.ignore();
			ch = 15 ;
		}

	}while(ch !=0);
 
    return 0;
}
