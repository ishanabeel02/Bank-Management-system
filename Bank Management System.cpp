# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <ctime>
# include <windows.h> 
# include <limits>
using namespace std;

class Bank 
{
public:
    string password;
    string username;
    int Account_no;
    double Balance;
    int acc_type;
    static int count;
	
	//Functions 
    virtual bool login() 
	{
		cout << "base class func" << endl;
	}

	//To Set color
    void setColor(int color)
    {
    	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, color);
	}
	
	//To set timer
    void timer() 
	{
        int seconds = 10;
        setColor(2);
        cout << "\n\n" << endl;
        for (int i = seconds; i >= 0; --i) 
		{
            cout << "\t\t\t\t\tTime remaining: 00:00:" << i << " seconds\r" << flush;
            Sleep(1000); // Sleep for 1000 milliseconds (1 second)  
        }
         cout << "\n\n\n";
        setColor(15);
    }
    //To add loading animation 
	void Loading() 
	{
		int barWidth = 40;
		setColor(4);
		cout << "\t\t\tLoading: [";
		for (int i = 0; i < barWidth; ++i) 
		{
		setColor(6);
		cout << "=" << flush;
		Sleep(5); 
		setColor(4);
		}
		cout << "]" << endl;
		setColor(15);
	}
	//To generate one time password 
    bool OTP() 
	{
        ofstream F;
        A:
        F.open("MyFile.txt", ios::trunc);
        if (!F) {
            cout << "Unable to open the file " << endl;
        }
        // Seed the random number generator
        srand(time(0));
        // Generate a random number between 1 - 999
        int Random = (rand() % 1000) + 1000;

        // OTP added to file
        F << Random;
        F.close();

        // Enter the OTP
        int OTP;
        cout << "Enter the one time password " << endl;
        cin >> OTP;

        if (Random == OTP) 
		{
            cout << "==========================================" << endl;
		    cout << "         <<< Login Successful!!!! >>>         " << endl;
		    cout << "==========================================" << endl;
		    return true;
    
        } 
		else 
		{
            cout << "==========================================" << endl;
		    cout << "              <<< \aInvalid >>>         " << endl;
		    cout << "==========================================" << endl;
            timer();
            int ans;
            cout << "Do you want to resend OTP?" << endl;
            cout << "==========================================" << endl;
		    cout << "\t1 = Yes" << endl;
		    cout << "\t2 = No" << endl;
		    cout << "==========================================" << endl;
            cin >> ans;
            if(ans == 1)
            {
            	goto A;	
			}
			else
			{
				return false;
				cout << "==================================================EXITING=========================================================" << endl;
			}
        }
    }
};

int Bank::count = 0;

//Drived class
class User : public Bank 
{
public:
	double Electricity;
	double Gas;
	double Internet;
	double Water;
	//Constructor
	User()
	{
		// Seed the random number generator
	    srand(time(0));
	    // Generate random bill amounts
		Electricity = (rand() % 1000) + 1000;
	    Gas         = (rand() % 1000) + 1000;
	    Internet    = (rand() % 1000) + 100;
	    Water       = (rand() % 1000) + 100;
	}
	
	//To login 
    bool login(string us, string pss, User acc[], int *n) 
	{ 
		bool found;
        for (int i = 0; i <= count; i++) 
		{
            if (us == acc[i].username && pss == acc[i].password) 
			{
				Loading();
                cout << "==========================================" << endl;
			    cout << "   <<< User and Password Correct >>>         " << endl;
			    cout << "==========================================" << endl;
			    found = true;
				*n = i;
				if(OTP())
				{
					return true;
				}
				else
				{
					return false;
				}
            }
        }
        if(!found) 
			{
				Loading();
                cout << "==========================================" << endl;
			    cout << "  <<<  User and Password InCorrect  >>> " << endl;
			    cout << "==========================================" << endl;
			    return false;
            }
    }
    
    // Friend function declaration
    friend void updatePassword(User user[],  string newPassword, int n);
    
	//To get info 
    void Get_info() 
	{
        cout << "==========================================" << endl;
		cout << "          <<< Account Details >>>         " << endl;
	    cout << "==========================================" << endl;
        if(acc_type == 1)
        {
			{
			 cout << "Account number: " << Account_no << "\nUsername: " << username << "\nPassword: " << password << "\nAccount Type: " << (acc_type == 1 ? "Saving" : "Current") << "\nBalance: " << Balance << endl;
			}

		}
		else
		{
			cout << "Account number: " << Account_no << "\nUsername: " << username << "\nPassword: " << password << "\nAccount Type: " << (acc_type == 1 ? "Saving" : "Current") << "\nBalance: " << Balance << endl;
		}
    }
	//To deposit money
    void Deposit() 
	{
        double b;
        cout << "Enter the amount you want to deposit: ";
        cin >> b;
        Balance += b;
        cout << "New Balance: " << Balance << "$" << endl;
    }
	//To withdraw money
    void withdraw() 
	{
        double b;
        cout << "Enter the amount you want to withdraw: ";
        cin >> b;
        Balance -= b;
        cout << "===========================\n";
        cout << "New Balance: : " << Balance << "$\n";
        cout << "===========================" << endl;
    }
    //To display bill
    void display_bill()
{
    cout << "Bills:\t\tAmount\t\tStatus" << endl;

    // Electricity bill
    if (Electricity != 0)
    {
        cout << "Electricity:\t" << Electricity << "$";
        setColor(4);
		cout << "\t\tunpaid" << endl;
		setColor(15);
	}
    else
    {
        cout << "Electricity:\t" << Electricity << "$";
        setColor(2);
		cout << "\t\tpaid" << endl;
		setColor(15);
	}	

    // Gas bill
    if (Gas != 0)
    {
        cout << "Gas:\t\t" << Gas << "$";
        setColor(4);
		cout << "\t\tunpaid" << endl;
		setColor(15);
	}
    else
    {
        cout << "Gas:\t\t" << Gas << "$";
        setColor(2);
		cout << "\t\tpaid" << endl;
		setColor(15);
	}
    // Internet bill
    if (Internet != 0)
    {
        cout << "Internet:\t" << Internet << "$";
        setColor(4);
		cout << "\t\tunpaid" << endl;
		setColor(15);
	}
    else
    {
        cout << "Internet:\t" << Internet << "$";
        setColor(2);
		cout << "\t\tpaid" << endl;
		setColor(15);
	}

    // Water bill
    if (Water != 0)
    {
        cout << "Water:\t\t" << Water << "$";
        setColor(4);
		cout  << "\t\tunpaid" << endl;
		setColor(15);
	}
    else
    {
        cout << "Water:\t\t" << Water << "$";
        setColor(2);
		cout  << "\t\tpaid" << endl;
		setColor(15);
	}
}

	//To pay the bills	
	void pay_bill()
	{
	    
	    display_bill();
	    int ans, option;
	    cout << "Do you want to pay the bill?" << endl ;
	    cout << "==========================================" << endl;
		cout << "\t1 = Yes" << endl;
		cout << "\t2 = No" << endl;
		cout << "==========================================" << endl;
	    cin >> ans;
	
	    if(ans == 1)
	    {
		    cout << "Which bill do you want to pay?" << endl;
		    cout << "------------------------------------------" << endl;
		    cout << "   1. Electricity" << endl;
		    cout << "   2. Gas" << endl;
		    cout << "   3. Internet" << endl;
		    cout << "   4. Water" << endl;
		    cout << "------------------------------------------" << endl;
		    cout << "Press the number corresponding to your choice: ";
	        cin >> option;
	        
	        switch(option)
	        {
	            case 1:
	                cout << "==============================================" << endl;
					cout << "           Electricity bill: " << Electricity   << endl;
					cout << "==============================================" << endl;
	                if(Balance >= Electricity)
	                {
	                    
	                    Balance -= Electricity;
	                    Electricity = 0;
	                    cout << "==============================================" << endl;
						cout << "     <<< Bill Paid Successfully >>>  " << endl;
						cout << "==============================================" << endl;
	                }
	                else
	                {
	                    cout << "==============================================" << endl;
				        cout << "          \aInsufficient balance!                " << endl;
				        cout << "==============================================" << endl;
	                }
	                break;
	            
	            case 2:
	            	cout << "==============================================" << endl;
					cout << "         			 Gas bill: "     	 <<  Gas << endl;
					cout << "==============================================" << endl;
	                if(Balance >= Gas)
	                {
	                    Balance -= Gas;
	                    Gas = 0;
	                    cout << "==============================================" << endl;
						cout << "     <<< Bill Paid Successfully >>>  " << endl;
						cout << "==============================================" << endl;
	                }
	                else
	                {
	                    cout << "==============================================" << endl;
				        cout << "          \aInsufficient balance!                " << endl;
				        cout << "==============================================" << endl;
	                }
	                break;
	            
	            case 3:
		                cout << "==============================================" << endl;
						cout << "          Internet bill: " << Internet  << endl;
						cout << "==============================================" << endl;
		                if(Balance >= Internet)
	                {
	                    Balance -= Internet;
	                    Internet = 0;
	                    cout << "==============================================" << endl;
						cout << "     <<< Bill Paid Successfully >>>  " << endl;
						cout << "==============================================" << endl;
	                }
	                else
	                {
	                    cout << "==============================================" << endl;
				        cout << "          \aInsufficient balance!                " << endl;
				        cout << "==============================================" << endl;
	                }
	                break;
	            
	            case 4:
	                cout << "==============================================" << endl;
					cout << "               Water bill: " << Water  << endl;
					cout << "==============================================" << endl;
	                if(Balance >= Water)
	                {
	                    Balance -= Water;
	                    Water = 0;
	                    cout << "==============================================" << endl;
						cout << "     <<< Bill Paid Successfully >>>  " << endl;
						cout << "==============================================" << endl;
	                }
	                else
	                {
	                    cout << "==============================================" << endl;
				        cout << "          \aInsufficient balance!                " << endl;
				        cout << "==============================================" << endl;
	                }
	                break;
	            
	            default:
	                cout << "==============================================" << endl;
				    cout << "=             Invalid option!                  =" << endl;
				    cout << "==============================================" << endl;
	                break;
	        }
	    }
	    else
	    {
	    	cout << "==================================================EXISTING=========================================================" << endl;
		}
	}
	//Inherited Func
	bool login()
	{
		cout << "Username: " << username << endl;
		cout << "Password: " << password << endl;
		return true;
	}
};
//Friend Function definition
void updatePassword(User user[],  string newPassword, int n)
{
	string oldpass;
	oldpass = user[n].password;
	user[n].password = newPassword;
	cout << "Password for user " << user[n].username << " has been updated.\n";
	cout << "Old Password: " << oldpass << endl;
	cout << "New Password: " << newPassword << endl;
}

class Admin : public Bank 
{
public:
    bool login() 
	{
        string us;
        string pass;
        string line;
        bool found = false;
        Bank acc;
        cout << "Enter username: ";
        cin >> us;
        cout << "Enter password: ";
        cin >> pass;
        // Read from a file
        ifstream file("info.txt");
        // Error in opening
        if (!file.is_open()) 
		{
            cout << "Error opening file!" << endl;
        }
        while (getline(file, line)) 
		{
            istringstream i(line);
            if (i >> acc.username >> acc.password) 
			{
                if(acc.username == us && acc.password == pass) 
				{
					Loading();
	                cout << "==========================================" << endl;
				    cout << "   <<< User and Password Correct >>>         " << endl;
				    cout << "==========================================" << endl;
					if(OTP())
					{
						return true;
					}
					else
					{
						return false;
					}
	                    
                }
            }
        }

        if (!found) 
		{
           		Loading();
                cout << "==========================================" << endl;
			    cout << "  <<<  User and Password InCorrect  >>> " << endl;
			    cout << "==========================================" << endl;
			    return false;
        }

        file.close();
    }

    void add_account(User u[])
	{
		cout << "Enter Account Number : ";
        cin >> u[count].Account_no;
		cout << "Enter the username of the new account(No Spaces): ";
        cin >> u[count].username;
        cout << "Enter the password of the new account ";
        cin >> u[count].password;
        cout << "Enter the acc_type of the new account \n\t\t\t\t1.Saving  \n\t\t\t\t2.Current";
        cin >> u[count].acc_type;
        cout << "Enter the Balance of the new account $: ";
        cin >> u[count].Balance;
        Bank::count++;
    }

    void del_account(User u[],  string usernameToDelete) 
	{
        bool found = false;
        for (int i = 0; i < count; ++i) 
		{
            if (u[i].username == usernameToDelete)
			{
                // Shift remaining elements left to fill the gap
                for (int j = i; j < count - 1; ++j) 
				{
                    u[j] = u[j + 1];
                }
                count--;
                found = true;
                cout << "==============================================" << endl;
				cout << "          Account deleted successfully!        " << endl;
				cout << "==============================================" << endl;
                break;
            }
        }
        if (!found)
		{
            cout << "==============================================" << endl;
	        cout << "           \a Account not found!               " << endl;
	        cout << "==============================================" << endl;
        }
    }

    void show_all_accounts(User u[]) 
	{
        cout << "All Accounts:" << endl;
        for (int i = 0; i < count; ++i) 
		{
			cout << "Account number: " << u[i].Account_no << endl;
            cout << "Username: " << u[i].username << endl;
            cout << "Account Type: " << u[i].acc_type << endl;
            cout << "Balance: " << u[i].Balance << "$" << endl;
            cout << endl;
        }
    }

    void search_account(User u[],  string usernameToFind) 
	{
        bool found = false;
        for (int i = 0; i < count; ++i) 
		{
            if (u[i].username == usernameToFind) 
			{
                cout << "Account found:" << endl;
                cout << "Account number: " << u[i].Account_no << endl;
                cout << "Username: " << u[i].username << endl;
                cout << "Account Type: " << u[i].acc_type << endl;
                cout << "Balance: " << u[i].Balance << "$" << endl;
                found = true;
                break;
            }
        }
        if (!found) 
		{
            cout << "==============================================" << endl;
	        cout << "              \aAccount not found!               " << endl;
	        cout << "==============================================" << endl;
        }
    }
};

//Third Derived Class 
class Bank_services : public Bank
{
	public:
		void Consultancy()
		{
		cout<<" 1. What types of accounts do you offer (checking, savings, etc.)?"<<endl;
		cout<<" 2. What documents do I need to bring to open an account?"<<endl;
		cout<<" 3. Are there any monthly maintenance fees or other charges?"<<endl;
		cout<<" 4. What types of credit cards do you offer?"<<endl;
		cout<<" 5. What is the credit limit and how is it determined?"<<endl;
		cout<<" 6. What should I do if I lose my debit/credit card?"<<endl;
		cout<<" 7. Can I set up automatic bill payments?"<<endl;
		cout<<" 8. How do I transfer funds between accounts?"<<endl;
		cout<<" 9. What are your branch hours?"<<endl;
		cout<<" 10. Are there any ATMs in the area that don’t charge fees for withdrawals?"<<endl;
		cout<<" 11. Can I get a printed summary of my account activity?"<<endl;
		cout<<" 12. Who should I contact if I have questions about my account?"<<endl;
		int opt;
		cin>>opt;
		switch(opt)
		{
			case 1:
				cout<<" 1. Our bank offer checking accounts, savings accounts, money market accounts, and certificates of deposit "<<endl;
				break;
			case 2:
				cout<<" 2. You generally need a government-issued photo ID (like a driver’s license or passport), your Social Security number, and proof of address (such as a utility bill )"<<endl;
				break;
			case 3:
				cout<<" 3. Our bank charge monthly maintenance fees, typically ranging from $5 to $15. These fees can often be waived if you maintain a minimum balance "<<endl;
				break;
			case 4:
				cout<<" 4. Bank offer a variety of credit cards, including basic, rewards (cash back, travel), and premium cards with additional benefits."<<endl;
				break;
			case 5:
				cout<<" 5. Credit limits are determined based on your credit score, income, and existing debt."<<endl;
				break;
			case 6:
				cout<<" 6. Contact your bank immediately to report the lost card. They will block the card to prevent unauthorized use and issue a replacement."<<endl;
				break;
			case 7:
				cout<<" 7. Yes, You can schedule recurring payments for bills directly from your account."<<endl;
				break;
			case 8:
				cout<<" 8. You can transfer funds through online banking, mobile banking apps, or by visiting a branch. "<<endl;
				break;
			case 9:
				cout<<" 9. Branch hours typically range from 9 AM to 5 PM, Monday through Friday. "<<endl;
				break;
			case 10:
				cout<<" 10. Most banks provide a network of ATMs where you can withdraw money without fees."<<endl;
				break;
			case 11:
				cout<<" 11. Yes, you can request a printed summary at a branch "<<endl;
				break;
			case 12:
				cout<<" 12. Contact your bank’s customer service department for account-related inquiries. The contact information is usually available on your account statements."<<endl;
				break;
			default :
				cout<<" \aINVALID OPTION !!!"<<endl;

		}	
	}
	
		//Func to exchange money
		void Exchangemoney()
		{
		char option;
		do 
		{
        double pkr;
        int choice;

        cout << "Enter the amount in Pakistani Rupees (PKR): ";
        cin >> pkr;

        cout << "Choose the currency to convert to:" << endl;
        cout << "1. SAR (Saudi Riyal)" << endl;
        cout << "2. USD (US Dollar)" << endl;
        cout << "3. AED (UAE Dirham)" << endl;
        cout << "4. EUR (Euro)" << endl;
        cout << "5. CNY (Chinese Yuan)" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        double convertedAmount = 0.0;
        switch (choice)
		 {
            case 1:
                convertedAmount = pkr * 0.013;
                cout << "PKR " << pkr << " is equivalent to " << convertedAmount << " SAR (Saudi Riyal)" << endl;
                break;
            case 2:
                convertedAmount = pkr * 0.0035;
                cout << "PKR " << pkr << " is equivalent to " << convertedAmount << " USD (US Dollar)" << endl;
                break;
            case 3:
                convertedAmount = pkr * 0.0128;
                cout << "PKR " << pkr << " is equivalent to " << convertedAmount << " AED (UAE Dirham)" << endl;
                break;
            case 4:
                convertedAmount = pkr * 0.0032;
                cout << "PKR " << pkr << " is equivalent to " << convertedAmount << " EUR (Euro)" << endl;
                break;
            case 5:
                convertedAmount = pkr * 0.025;
                cout << "PKR " << pkr << " is equivalent to " << convertedAmount << " CNY (Chinese Yuan)" << endl;
                break;
            default:
                cout << "\aInvalid choice. Please select a valid option." << endl;
                break;
        }

        cout << "Do you want to convert again? \n\t\t\t\tY = yes \n\t\t\t\tN = NO: ";
        cin >> option;
    }while(option == 'y' || option == 'Y');

    cout << "Thank you for using the currency converter!" << endl;	   	
		}
		
		//To Register Complain
		void complain()
		{
			string com, mail;
		    cout << "Enter your Complain: " << endl;
		    cin.ignore(); // Ignore any remaining newline characters
		    getline(cin, com);
		
		    cout << "Enter your email: ______________ @gmail.com";
		    cin >> mail;
		
		    string filename = mail + ".txt";
		    ofstream file(filename.c_str());
		    if (!file.is_open()) 
			{
		        cout << "\aUnable to open the file " << filename << endl;

		    }
		
		    // Seed the random number generator
		    srand(time(0));
		    // Generate a random number between 1000 - 9999
		    int Random = (rand() % 9000) + 1000;
		
		    // Write complain and random number to file
		    file << "Complaint: " << com << endl;
		    file << "Complaint Number: " << Random << endl;
		
		    file.close();
		    cout << "Thank you for reaching out to us" << endl;
    		cout << "Your complaint number has been generated and emailed to you." << endl;
	}
	//Loan Management
	void Loan_Record()
	{
	ifstream f("loan.txt");
	string line;
	string name, Amount, duedate, Status;
	 //Error in opening 
		    if (!f.is_open())
			{
		        cout << "\aError opening file!" << endl;
		    }
		    Loading();
		    while (getline(f, line)) 
			{
				istringstream iss(line);
		        if (iss >> name >> Amount >> duedate >> ws) 
				{
		            getline(iss, Status);
			            if (Status == "unpaid") 
						{
			                cout << "Name: " << name << endl;
			                cout << "Amount: " << Amount << endl;
			                cout << "Due Date: " << duedate << endl;
			                cout << "Status: ";
			                setColor(4);
							cout << Status << endl;
			                setColor(15);
 			            }
 			            else
 			            {
 			            	cout << "Name: " << name << endl;
			                cout << "Amount: " << Amount << endl;
			                cout << "Due Date: " << duedate << endl;
			                cout << "Status: ";
			                setColor(2);
							cout << Status << endl;
							setColor(15);	
						 
						}
		        }
		}
		f.close();
}
		
};
//Function To Clear the screen
Clearscreen()
{
	system("cls");
}

int main() 
{
	//Declaring all the variables
	Admin admin;
    User user[100]; 
	Bank_services guest;
	int options1, options2, options3;
	int op;
   	
	//Welcome To banking system 
	for(int i = 0; i <= 15; i++) 
	{
        Clearscreen(); // Clear the screen
        Bank b;
		b.setColor(i);
		cout << "\n\n\n\n\n\n\t-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;
		cout << "\n\n\n";
        cout <<"\t\t\t\t   __      __        __\n";
		cout <<"\t\t\t\t  /  \\    /  \\ ____ |  | ____  ____    _____   ____ \n";										
		cout <<"\t\t\t\t  \\   \\/\\/   // __ \\|  |/ ___\\/  _ \\  /     \\ / __ \\\n";
		cout <<"\t\t\t\t   \\        /|  ___/|  |  \\__(  <_> )|  Y Y  | ___ /  \n";
		cout <<"\t\t\t\t    \\__/\\__/  \\____\\|__|\\_____>____/ |__|_|__|\\____\\\n";
		cout << "\n\n\n\n\t-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << endl;;
		
        
        Sleep(300); // Sleep 
        Clearscreen();
    }
    //Ban Name
	cout << "\t\t\t\t\tDDDDD     BBBBB   SSSSS \n";
    cout << "\t\t\t\t\tD    D    B    B  S     \n";
    cout << "\t\t\t\t\tD     D   BBBBB    SSSSS \n";
    cout << "\t\t\t\t\tD    D    B    B       S \n";
    cout << "\t\t\t\t\tDDDDD     BBBBB   SSSSS  \n";
    cout << "\t\t\t===========================================================" << endl;
    cout << "\t\t\t\t\t  DUSTY BANKING SYSTEM" << endl;
    cout << "\t\t\t===========================================================" << endl;
    
    //Do while to repeat
do{
	
	B:
	cout << "\n\nPress the corresponding number to make your selection." << endl;
	cout << "\t\t\t==================\t\t\t==================" << endl;
    cout << "\t\t\t||               ||\t\t\t||               ||" << endl;
    cout << "\t\t\t||  1. User      ||\t\t\t||  2. Admin     ||" << endl;
    cout << "\t\t\t||               ||\t\t\t||               ||" << endl;
    cout << "\t\t\t==================\t\t\t==================" << endl;
    cout << "\t\t\t==================\t\t\t==================" << endl;
    cout << "\t\t\t||               ||\t\t\t||               ||" << endl;
    cout << "\t\t\t||  3. Guest     ||\t\t\t||   4.Exit      ||" << endl;
    cout << "\t\t\t||               ||\t\t\t||               ||" << endl;
    cout << "\t\t\t==================\t\t\t==================" << endl;
    
    cin >> options1;
    switch(options1)
    {
    	case 1:
    		{ 
    			try
	    		{	
	    				
	    				int n = 0;
						string us, pass;
						User u;
		    			cout << "Enter the Username: ";
		    			cin >> us;
		    			cout << "Enter the Password: ";
		    			cin >> pass;
		    		if(u.login(us, pass, user, &n))
		    		{
		    				
			    		do
						{
							C:
		    				cout<<"\n\t\t\t\tBANK - USER "<<endl;
							cout<<"\t /////////////////////////////////////////////////////////////////"<<endl;
							cout<<"\t |\tShow Account Info   :------------------- |\tPress [1]|"<<endl;
							cout<<"\t |\tDeposite Money      :------------------- |\tPress [2]|"<<endl;
							cout<<"\t |\tWithdraw Money      :------------------- |\tPress [3]|"<<endl;
							cout<<"\t |\tDisplay bill        :------------------- |\tPress [4]|"<<endl;
							cout<<"\t |\tPay bill            :------------------- |\tPress [5]|"<<endl;
							cout<<"\t |\tUpdate Password     :------------------- |\tPress [6]|"<<endl;
							cout<<"\t |\tExit                :------------------- |\tPress [7]|"<<endl;
							cout<<"\t |_______________________________________________________________|"<<endl;
							cin >> op;
								switch(op)
				    			{
				    				case 1:
				    					{
				    						user[n].Get_info();
				    						cout << "\n\n\t\t==========================================================================" << endl;
				    						Sleep(4000);
				    						Clearscreen();
				    						break;
										}
									case 2:
				    					{
				    						user[n].Deposit();
				    						cout << "\n\n\t\t==========================================================================" << endl;
				    						Sleep(2000);
				    						Clearscreen();
				    						break;
										}
									case 3:
				    					{
				    						user[n].withdraw();
				    						cout << "\n\n\t\t==========================================================================" << endl;
				    						Sleep(2000);
				    						Clearscreen();
				    						break;
										}
									case 4:
				    					{
				    						user[n].display_bill();
				    						cout << "\n\n\t\t==========================================================================" << endl;
				    						Sleep(2000);
				    						Clearscreen();
				    						break;
										}
									case 5:
				    					{
				    						user[n].pay_bill();
				    						cout << "\n\n\t\t==========================================================================" << endl;
				    						Sleep(2000);
				    						Clearscreen();
				    						break;
										}
										case 6:
				    					{
				    						string newpss;
				    						cout << "Enter the New password: ";
				    						cin >> newpss;
				    						updatePassword(user, newpss, n);
				    						Sleep(2000);
				    						break;
										}
										case 7:
				    					{
				    						cout << "\n\n==================================================EXITING=========================================================" << endl;
				    						Sleep(1000);
				    						Clearscreen();
				    						break;
										}
										default:
										{
											cout << "\n\n==================================================Invalid Input=========================================================" << endl;
											Sleep(1000);
											Clearscreen();
											goto C;
										}
								}
						}while(op != 7);
					}
					else
						{
							throw "Could not login ";
						}
				}
				catch(const char * msg)
				{
						cout << "\aError: " << msg << endl;
				}
			
			//Main switch break 
			Sleep(2000);
			Clearscreen();
			break;		
			}
		case 2:
    		{
	    			int n = 0;
	    			try
	    			{
		    			if(admin.login())
		    			{
		    				
			    		do
						{	D:
			    			cout<<"\n\t\t\t\tBANK - ADMIN "<<endl;
							cout<<"\t ////////////////////////////////////////////////////////////////"<<endl;
							cout<<"\t |\tAdd Account      :------------------- |\tPress [1]\t|"<<endl;
							cout<<"\t |\tDelete Account   :------------------- |\tPress [2]\t|"<<endl;
							cout<<"\t |\tShow All Acounts :------------------- |\tPress [3]\t|"<<endl;
							cout<<"\t |\tSearch Acounts   :------------------- |\tPress [4]\t|"<<endl;
							cout<<"\t |\tExit             :------------------- |\tPress [5]\t|"<<endl;
							cout<<"\t |______________________________________________________________|"<<endl;
			    			cin >> op;
			    			switch(op)
			    			{
			    				case 1:
			    					{
			    						admin.add_account(user);
			    						Sleep(2000);
			    						Clearscreen();
			    						break;
									}
								case 2:
			    					{
			    						string us;
			    						cout << "Enter the user u want to Delete? ";
			    						cin >> us;
			    						admin.del_account(user, us);
			    						cout << "\n\n\t\t==========================================================================" << endl;
			    						Sleep(2000);
			    						Clearscreen();
			    						break;
									}
								case 3:
			    					{
			    						admin.show_all_accounts(user);
			    						cout << "\n\n\t\t==========================================================================" << endl;
			    						Sleep(6000);
			    						Clearscreen();
			    						break;
									}
								case 4:
			    					{
			    						string us;
			    						cout << "Enter the user u want to search? ";
			    						cin >> us;
			    						admin.search_account(user, us);
			    						cout << "\n\n\t\t==========================================================================" << endl;
			    						Sleep(2000);
			    						Clearscreen();
			    						break;
									}
								case 5:
									{
										cout << "\n\n==================================================EXITING=========================================================" << endl;
										Sleep(1000);
										Clearscreen();
										break;
									}
									default:
									{
										cout << "\n\n==================================================Invalid Input=========================================================" << endl;
										Sleep(1000);
										Clearscreen();
										goto D;
									}
							}
						}while(op != 5);
					}
					else
					{
						throw "Could not login ";
					}
			}
			catch(const char *  msg)
			{
				cout << "\aError: " << msg << endl;
			}
		cout << "\n\n==================================================EXITING=========================================================" << endl;
		Sleep(2000);
		Clearscreen();
		//Main switch break 
		break;	
		}
		case 3:
			{
				Clearscreen();
			do
			{
				E:
				cout<<"\n\t\t\t\tBANK - SERVICES "<<endl;
				cout<<"\t/////////////////////////////////////////////////////////////////"<<endl;
				cout<<"\t |\tInquiry        :------------------- |\tPress [1]\t|"<<endl;
				cout<<"\t |\tLoan           :------------------- |\tPress [2]\t|"<<endl;
				cout<<"\t |\tComplain       :------------------- |\tPress [3]\t|"<<endl;
				cout<<"\t |\tExchange Money :------------------- |\tPress [4]\t|"<<endl;
				cout<<"\t |\tExit           :------------------- |\tPress [5]\t|"<<endl;
				cout<<"\t ________________________________________________________________"<<endl;
				
				cin >> op;
			
				switch(op)
    			{
    				case 1:
    					{
    						guest.Consultancy();
    						cout << "\n\n\t\t==========================================================================" << endl;
    						Sleep(2000);
    						Clearscreen();
    						break;
						}
					case 2:
    					{
    					
    						guest.Loan_Record();
    						cout << "\n\n\t\t==========================================================================" << endl;
    						Sleep(6000);
    						Clearscreen();
    						break;
						}
					case 3:
    					{
    						guest.complain();
    						cout << "\n\n\t\t==========================================================================" << endl;
    						Sleep(2000);
    						Clearscreen();
    						break;
						}
					case 4:
    					{
    						guest.Exchangemoney();
    						cout << "\t\t==========================================================================" << endl;
    						Sleep(2000);
    						Clearscreen();
    						break;
						}
					case 5:
						{
							cout << "\n\n==================================================EXIING=========================================================" << endl;
							Sleep(1000);
										Clearscreen();
										break;
						}
						default:
						{
							cout << "\n\n==================================================Invalid Input=========================================================" << endl;
							Sleep(1000);
							Clearscreen();
							goto E;
						}
				}
			
			}while(op != 5);
		
			cout << "==================================================EXITING=========================================================" << endl;
			Sleep(1000);
			Clearscreen();
			break;
				
			}
	case 4:
		{
			cout << "\n\n==================================================EXITING=========================================================" << endl;
			break;
		}
	default:
	{
		cout << "\n\n==================================================Invalid Input=========================================================" << endl;
		Sleep(1000);
		Clearscreen();
		goto B;
	}
}
}while(options1 != 4);
for(int i = 0; i <= 15; i++) 
	{
        
        Bank b;
		b.setColor(i);
        cout << "\t\t\t\tTTTTT  H   H  AAAAA  N   N  K   K    U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  NN  N  K  K     U   U" << endl;
	    cout << "\t\t\t\t  T    HHHHH  AAAAA  N N N  K K      U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N  NN  KK       U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N   N  K  K     U   U" << endl;
	    cout << "\t\t\t\t  T    H   H  A   A  N   N  K   K    UUUUU" << endl;
        
        Sleep(300); 
    }
			

    return 0;
}


