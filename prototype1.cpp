#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#define MAX_USERS 100
//cd PC/Desktop/'NotesLabs 2019 Winter/CPS707_Project/CPS707_ByteCode/
using namespace std;
ifstream inFile;
string user [MAX_USERS], type [MAX_USERS];
int credit [MAX_USERS];
int userNumber = 0;

int login_checker(string username)//searches for if a username matches an existing username
{
  int jk = 0;
  while(jk < userNumber)
  {
	if(username == user[jk])
	{
		return jk;//returns where in the user array this user is
	}
	jk++;
  }
  return -1;
}

string logout()
{

}
string create() //allows an admin to create a new user
{
	string newuser, newusertype, money;

	cout << "Enter the new users name: "
	cin >> newuser
	if (login_checker(newuser) != -1) {
		cout << "that user already exits \n"
		return ""
	}
	if (newuser.length() > 15)
	{
		cout << "The name " << newuser << " exceeds the maximum number of characters for a username, user creation cancelled";
		return "";
	}

	cout << "Enter type: "
	cin >> newusertype;
	if (newusertype != "FS" || newusertype != "SS" || newusertype != "BS" || newusertype != "AA") {
		cout << "that type does not exist";
		return "";
	}

	cout << "Enter credit: "
	cin >> money;
	// This code converts from string to number safely.
	int newusercredits;
	stringstream myStream(money);
	if (myStream >> newusercredits)
	else
	{
		cout << "Invalid number" << endl;
		return "";
	}


	int remainingspace = newuser.length() - 15;
	string emptyspaces = "";
	for (i = 0; i < remainingspace; i++) emptyspaces += '_';

	string usersinfo = "00_" + newusername + emptyspaces + newusertype + newusercredits;
	return "done";
}

string refund() //allows an admin to refund a transaction 
{
	cout << "in refund \n";
	return "done";
}

string deleteuser() //allows an admin to delete an old user
{
	cout << "in delete\n";
	return "done";
}
string addcredit() //allows any user to addcredit to their account
{
	cout << "in addcredit\n";
	return "done";
}
string addcreditadmin() //allows an admin to addcredit to any account
{
	cout << "in addcreditadmin\n";
	return "done";
}
string sell() //allows a seller to post offers
{
	cout << "in sell\n";
	return "done";
}

string buy() //allows a buyer to buy tickets
{
	cout << "in sell\n";
	return "done";
}

int main() 
{
	string input = "", username = "", temp = "", str = "";
	inFile.open("currentUserAccounts.txt");

	bool loggedin = false; //remembers if the user is already logged in

	cout << endl;
	while (getline(inFile, temp))
	  {
	      user[userNumber] = temp.substr(0,7);
	      type[userNumber] = temp.substr(16,2);
	      credit[userNumber] = stoi(temp.substr(19,9));
	      //cout << "User number " << i << " is : " << user[i] << " with type " << type[i] << " and avaliable credits " << credit[i] << endl;
	      userNumber++;
	  }

	cout << "welcome to the ticket selling service!" << endl;
	while (true)
	{
		int userid = 0;
		cin >> input;
		//Testing the login command
		if (input == "login")
		{
			if (loggedin)
			{
				cout << "You are already logged in! \n"
					break;
			}
			cout << "Enter a username" << endl;
			cin >> input;
			userid = login_checker(input);
			if (userid == -1)
			{
				cout << "The user " << username << " does not exist!" << endl;
			}
			else
			{
				username = input;
				cout << "You are now logged on as \"" << username << "\"" << endl;
				loggedin = true;
				if(type[useridnumber] = "AA")
				{
					cout << "Welcome back " << username << " you now have access to special permissions"
				}
			}
		}
		else
		{
			cout << "You need to login into your account first" << endl;
		}

		while (loggedin) //after logged in you can use other commands
		{
			cin >> input;
			//Testing the logout command
			if (input == "logout")
			{
				logout();
				loggedin = false;
				cout << "logged out\n"
				cout << "welcome to the ticket selling service!\n"
			}
			else if (input == "create")
				if(type[userid] = "AA")
					create();
			else if (input == "addcredit")
				if (type[userid] = "AA")
					addcreditadmin();
				else addcredit();
			else if (input == "delete")
				if (admin)
					deleteuser();
			else if (input == "sell")
				if(type[userid] == "FS" || type[userid] == "SS")
					sell();
				else cout << "you must have a";
			else if (input == "buy")
				if (type[userid] == "FS" || type[userid] == "BS")
					buy();
				else cout << "you must have a";
			else if (input == "refund")
				if (type[userid] == "AA")
					refund();
			else
				cout << "invalid command";
		}
	}
 return 0;
}