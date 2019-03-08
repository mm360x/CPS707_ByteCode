//Group Name: Byte Code
//Maitreya Meshram,  500792236
//Sean Riddell, 500691642
//Vivek Sehgal, 500753098

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#define MAX_USERS 100
#define MAX_EVENT 1000
using namespace std;
ifstream inFile;
ofstream outFile;
//arrays for the users information
string user [MAX_USERS], type [MAX_USERS];
int credit [MAX_USERS];
int userNumber = 0;
//arrays for the event information
string event [MAX_EVENT], seller [MAX_EVENT];
int numberTickets [MAX_EVENT], eventPrice [MAX_EVENT];
int eventNumber = 0;

string readAvalaibleTickets() //reads the available tickets from the available tickets file
{
    //EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP
    inFile.open("avaliableTicketsFile.txt");
    cout << endl;
    string temp, newDrone = "";
    while (getline(inFile, temp))
    {
        newDrone = temp.substr(0,19);
        event[eventNumber] = newDrone.substr(0,temp.find("__"));
        newDrone = temp.substr(20, 13);
        seller[eventNumber] = newDrone.substr(0,newDrone.find("_"));
        numberTickets[eventNumber] = stoi(temp.substr(35,3));
        eventPrice[eventNumber] = stoi(temp.substr(39,6));
        //cout << "Event number " << eventNumber << " is : " << event[eventNumber] << " with seller " << seller[eventNumber] << " numberofTickets " 
        //    << numberTickets[eventNumber] << " priceTicket " << eventPrice[eventNumber] << endl;
        eventNumber++;
    }
    return "done";
}
int event_checker(string eventName) //checks to see if an event already exists comparing the name
{
    int jk = 0;
  while(jk < eventNumber)
  {
    if(eventName == event[jk])
    {
      return jk;
    }
    jk++;
  }
  return -1;
}
int login_checker(string username)//searches for if a username matches an existing username which is read from the currentUserAccounts.txt
{
  int jk = 0;
  while(jk < userNumber)
  {
    if(username == user[jk])
    {
      return jk;
    }
    jk++;
  }
  return -1;
}
string logout(int userID) //writes to the daily transaction file the logouts of the session
{
    //00_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
    string newusername = user[userID], newusertype = type[userID];
    int newusercredits = credit[userID];
    int remainingspace = 15 - newusername.length();
	string emptyspaces = "_";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(newusercredits)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	string usersinfo = "00_" + newusername + emptyspaces + "_" + newusertype + "_" + emptyzeros + to_string(newusercredits) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "The user \"" << newusername << "\" has been logged out" << endl;
    return "";
}
string create() //allows an admin to create a new user
{
	string newuser, newusertype, money;

	cout << "Enter the new users name: ";
	cin >> newuser;
	if (login_checker(newuser) != -1) 
    {
		cout << "The user “" << newuser << "” already exists, user creation cancelled \n";
		return "";
	}
	if (newuser.length() > 15)
	{
		cout << "The name “" << newuser << "” exceeds the maximum number of characters (15) for a username, user creation cancelled" << endl;
		return "";
	}
	string newusername = newuser;

	cout << "Enter type: ";
	cin >> newusertype;
	if (newusertype == "FS" || newusertype == "SS" || newusertype == "BS" || newusertype == "AA") {
		
	}
    else
    {
        cout << "The entered type does not exist, user creation cancelled" << endl;
		return "";
    }

	cout << "Enter credit: ";
	cin >> money;
    int newusercredits = stoi(money);
    if(newusercredits > 999999)
    {
        cout << "The user being created exceeds the maximum number of credits a user can be allowed to have, user creation cancelled" << endl;
        return "";
    }
    else if(newusercredits < 0)
    { 
        cout << "The user being created cannot have credits in the negative, user creation cancelled" << endl;
        return "";
    }

	int remainingspace = 15 - newusername.length();
	string emptyspaces = "_";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(newusercredits)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	string usersinfo = "01_" + newusername + emptyspaces + "_" + newusertype + "_" + emptyzeros + to_string(newusercredits) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "The user \"" << newusername << "\" has been created" << endl;
    return "";
}

string refund() //allows an admin to refund a transaction 
{
    string buyeruser, selleruser;
    int buyerID, sellerID, amountCredit;
	cout << "Enter the username of the buyer" << endl;
    cin>> buyeruser;
    if(login_checker(buyeruser) == -1)
    {
        cout << "Sorry, the user “" << buyeruser << "” does not exists, refund cancelled" << endl;
        return "";
    }
    buyerID = login_checker(buyeruser);
    cout << "Enter the username of the seller" << endl;
    cin >> selleruser;
    if(login_checker(selleruser) == -1)
    {
        cout << "Sorry, the user “" << selleruser << "” does not exists, refund cancelled" << endl;
        return "";
    }
    sellerID = login_checker(selleruser);
    cout << "Enter the amount of credit to be transferred" << endl;
    cin >> amountCredit;
    if(amountCredit < 0)
    {
        cout << "Negative credit cannot be refunded, refund cancelled" << endl;
    }
    if(amountCredit > credit[sellerID])
    {
        cout << "The avaliable credit in the sellers account \"" << selleruser << "\" is less than the amount entered, refund cancelled" << endl;
    }
    //XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
    int buyerspace = 15 - buyeruser.length();
	string emptyspaces = "";
	for (int i = 0; i < buyerspace; i++) emptyspaces = emptyspaces + "_";
    string usersinfo = "05_" + buyeruser + emptyspaces + "_";
    int sellerspace = 15 - selleruser.length();
	emptyspaces = "";
	for (int i = 0; i < sellerspace; i++) emptyspaces = emptyspaces + "_";
    usersinfo = usersinfo + selleruser + emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(amountCredit)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	usersinfo = usersinfo + emptyzeros + to_string(amountCredit) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "Credits \"" << amountCredit << "$ have been transferred to the buyer \"" << buyeruser << " from the seller \"" << selleruser << "\"" << endl;
    return "";
}

string deleteuser() //allows an admin to delete a user
{
    string deleteusername;
	cout << "Enter the name of the user to be deleted\n";
    cin >> deleteusername;
    if(login_checker(deleteusername) == -1)
    {
        cout << "The user “" << deleteusername << "” does not exists, user deletion cancelled" << endl;
        return "";
    }
    int userID = login_checker(deleteusername);
    //remaining : to add code to delete the user from the CURRENTUSERSFILE for backend
    string newusername = user[userID], newusertype = type[userID];
    int newusercredits = credit[userID];
    int remainingspace = 15 - newusername.length();
	string emptyspaces = "_";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(newusercredits)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	string usersinfo = "02_" + newusername + emptyspaces + "_" + newusertype + "_" + emptyzeros + to_string(newusercredits) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "The user \"" << newusername << "\" has been deleted" << endl;
    return "";
}
string addcredit(int userID) //allows any user to addcredit to their account
{
    int numbercredit;
    cout << "Enter the amount of credit to be added\n";
    cin >> numbercredit;
    if(numbercredit > 1000 )
    {
        cout << "Credits more than 1000 cannot be added, add credit cancelled\n";
        return "";
    }
    else if(numbercredit < 0)
    {
        cout << "Negative credit cannot be added, add credit cancelled\n";
        return "";
    }
    if(numbercredit + credit[userID] > 1000000)
    {
        cout << "The credits entered plus the existing credits added exceeds the maximum amount of credit your account can contain, add credit cancelled\n";
        return "";
    }

    string newusername = user[userID], newusertype = type[userID];
    int newusercredits = numbercredit;
    int remainingspace = 15 - newusername.length();
	string emptyspaces = "_";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(newusercredits)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	string usersinfo = "06_" + newusername + emptyspaces + "_" + newusertype + "_" + emptyzeros + to_string(newusercredits) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "Credits " << newusercredits << "$ have been added to your acccount"<< endl;
    return "";
}
string addcreditadmin() //allows an admin to addcredit to any account
{
	string creditreceiver;
    int numbercredit, userID;
	cout << "Enter the username of the credit receiver\n";
    cin >> creditreceiver;
    if(login_checker(creditreceiver) == -1)
    {
        cout << "The user “" << creditreceiver << "” does not exists, add credit cancelled" << endl;
        return "";
    }
    userID = login_checker(creditreceiver);
    cout << "Enter the amount of credit to be added\n";
    cin >> numbercredit;
    if(numbercredit > 1000 )
    {
        cout << "Credits more than 1000 cannot be added, add credit cancelled\n";
        return "";
    }
    else if(numbercredit < 0)
    {
        cout << "Negative credit cannot be added, add credit cancelled\n";
        return "";
    }
    if(numbercredit + credit[userID] > 1000000)
    {
        cout << "The credits entered plus the existing credits added exceeds the maximum amount of credit a user can contain, add credit cancelled\n";
        return "";
    }

    string newusername = user[userID], newusertype = type[userID];
    int newusercredits = numbercredit;
    int remainingspace = 15 - newusername.length();
	string emptyspaces = "_";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    int remainingcreditspace = 7 - (to_string(newusercredits)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
	string usersinfo = "06_" + newusername + emptyspaces + "_" + newusertype + "_" + emptyzeros + to_string(newusercredits) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
	cout << "Credits " << newusercredits << "$ have been added to the user \"" << newusername << "\""<< endl;
    return "";

	return "done";
}
string sell(int sellerID) //allows a seller to post offers
{
    string eventTitle;
    int amountTicket, amountPrice;
	cout << "Enter the name of the event for which you want to sell tickets\n";
    cin >> eventTitle;
    if(eventTitle.length() > 19) //it was stated as 25 characters but the daily transaction file output is only 19 characters so we chose 19 to be consistent with the buy transaction
    {
        cout << "Sorry, the event title you have entered exceeds the maximum number of characters(19), sell transaction cancelled" << endl;
        return "";
    }
    else if(eventTitle.length() < 4)
    {
        cout << "Sorry, the event title you have entered is too short (less than 4 characters), sell transaction cancelled" << endl;
        return "";
    }
    cout << "Enter the amount of tickets to sell" << endl;
    cin >> amountTicket;
    if(amountTicket > 100)
    {
        cout << "Sorry, the maximum amount of tickets to be sold cannot exceed 100, selling transaction cancelled" << endl;
        return "";
    }
    else if(amountTicket < 0)
    {
        cout << "Sorry, the amount of tickets cannot be negative, sell transaction cancelled" << endl;
        return "";
    }
    cout << "Enter the price per ticket to sell (no more than the buying price)" << endl;
    cin >> amountPrice;
    if(amountPrice > 999) 
    {
        cout << "Sorry, the maximum price per ticket cannot exceed 999$, selling transaction cancelled" << endl;
        return "";
    }
    else if(amountPrice < 0)
    {
        cout << "Sorry, the price of tickets cannot be negative, sell transaction cancelled" << endl;
        return "";
    }
    //03_EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP
    int remainingspace = 19 - eventTitle.length();
	string emptyspaces = "";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    string usersinfo = "03_" + eventTitle + emptyspaces + "_";
    string buyerName = user[sellerID];
    remainingspace = 15 - buyerName.length();
	emptyspaces = "";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    usersinfo = usersinfo + buyerName + emptyspaces + "_";
    int remainingTicketSpace = 3 - (to_string(amountTicket)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingTicketSpace; i++) emptyzeros = emptyzeros + "0";
    usersinfo = usersinfo + emptyzeros + to_string(amountTicket) + "_";
    int remainingcreditspace = 4 - (to_string(amountPrice)).length();
    emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
    usersinfo = usersinfo + emptyzeros + to_string(amountPrice) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
    cout << "Congratulations, you have " << amountTicket << " tickets on sale for the event ‘" << eventTitle << "’ for the price per ticket " << amountPrice << endl;
    return "";

	return "done";
}

string buy(int buyerID) //allows a buyer to buy tickets
{
    string eventTitle, confirm;
    int ticketNumber, eventID;
	cout << "Enter the event title\n";
    cin >> eventTitle;
    if(event_checker(eventTitle) == -1)
    {
        cout << "Invalid Event title, buy event tickets transaction cancelled" << endl;
        return "";
    }
    eventID = event_checker(eventTitle);
    cout << "Enter the number of tickets to buy" << endl;
    cin >> ticketNumber;
    if(ticketNumber > 4)
    {
        cout << "Sorry, the maximum amount of tickets can be purchased is 4, buy event tickets transaction cancelled" << endl;
    }
    if(ticketNumber < 0)
    {
        cout << "Negative tickets cannot be bought, buy event tickets transaction cancelled" << endl;
    }
    int price = eventPrice[eventID] * ticketNumber;
    int availableCredit = credit[buyerID] / 100;
    if(price > (availableCredit))
    {
        cout << "Sorry, you have insufficient funds avaliable, buy event tickets transaction cancelled" << endl;
        return "";
    }
    cout << ticketNumber << " tickets for " << price << "$ (Price per ticket " << eventPrice[eventID] << ") from seller ‘" << seller[eventID] << "’,\n Enter yes to buy, no to cancel" << endl;
	cin >> confirm;
    if(confirm == "no")
    {
        return "";
    }
    else if(confirm != "yes")
    {
        cout << "Invalid input, buy event tickets transaction cancelled" << endl;
        return "";
    }
    cout << "Congratulations, you have purchased the " << ticketNumber << " tickets for " << event[eventID] << endl;
    //04_EEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP
    int remainingspace = 19 - eventTitle.length();
	string emptyspaces = "";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    string usersinfo = "04_" + eventTitle + emptyspaces + "_";
    string buyerName = user[buyerID];
    remainingspace = 15 - buyerName.length();
	emptyspaces = "";
	for (int i = 0; i < remainingspace; i++) emptyspaces = emptyspaces + "_";
    usersinfo = usersinfo + buyerName + emptyspaces + "_00" + to_string(ticketNumber) + "_";
    int remainingcreditspace = 4 - (to_string(price)).length();
    string emptyzeros = "";
    for (int i = 0; i < remainingcreditspace; i++) emptyzeros = emptyzeros + "0";
    usersinfo = usersinfo + emptyzeros + to_string(price) + "00";
    outFile.open("dailyTransactionFile.txt", std::ios_base::app);
    outFile << usersinfo << endl;;
    outFile.close();
    return "";
}
//so as soon as the program is run the currentUserAccounts file is read and it starts taking in commands after the welcome message
//after the login command it asks the user to input a username found in the currentUserAccounts file and as soon as the user
//enters the correct username they are taken to the main commands where they can perform transactions according to their priveledge
//there is also a quit command added to stop execution which is conformed by the message "All done. Exiting..."
int main() 
{
  string input = "", temp = "", str = ""; //temporary variables
  int tempInt = 0;
  string username = ""; //permenant vars
  bool loggedIn = false, adminLogin = false; //remembers if the user is already logged in

  inFile.open("currentUserAccounts.txt");
  cout << endl;

  while (getline(inFile, temp))
    {
        user[userNumber] = temp.substr(0,temp.find("_"));
        type[userNumber] = temp.substr(16,2);
        credit[userNumber] = stoi(temp.substr(19,9));
        //cout << "User number " << i << " is : " << user[i] << " with type " << type[i] << " and avaliable credits " << credit[i] << endl;
        userNumber++;
    }

    inFile.close();

    while(input != "quit")
    {
        cout << "welcome to the ticket selling service!" << endl;
        //Testing the login command
        //cin >> input;
		getline(cin, input);
		if (input.empty()){cout << "\n ERROR EMPTY INPUT \n"; break;}
        if(input == "login" && !loggedIn )
        {
            cout << "Enter a username" << endl;
            cin >> input;
            tempInt = login_checker(input);
            if(tempInt == -1)
            {
            cout << "The user \"" << input << "\" does not exist!" << endl;
            }
            else
            {
                username = user[tempInt];
                if(type[tempInt] == "AA")
                {
                    adminLogin = true;
                    loggedIn = true;
                    cout << "Welcome back admin \"" << username << "\", you now have special permissions" << endl;
                }
                else
                {
                    cout << "You are now logged on as \"" << username << "\"" << endl;
                    loggedIn = true;
                }
            }
        }
        else if(!loggedIn && input != "quit")
        {
            cout << "You need to login into your account first" << endl;
        }

        while(loggedIn && input != "quit") //after logged in you can use other commands
        {
            readAvalaibleTickets();
            cin >> input;
			if (input.empty()){cout << "\n ERROR EMPTY INPUT \n"; break;}
			if (input == "logout")
			{
                if(type[tempInt] == "AA")
                {
                    adminLogin = false;
                }
				logout(tempInt);
				loggedIn = false;
				cout << "Logged out\n";
			}
            else if (input == "create")
				if (adminLogin)
                    create();
                else
                    cout << "Create is for ADMINS ONLY" << endl;                    
			else if (input == "addcredit")
				if (adminLogin)
					addcreditadmin();
				else 
                    addcredit(tempInt);
			else if (input == "delete")
                if (adminLogin)
					deleteuser();
                else 
                    cout << "Delete is for ADMINS ONLY" << endl;
			else if (input == "sell")
				if(type[tempInt] == "FS" || type[tempInt] == "SS")
					sell(tempInt);
                else if(adminLogin)
                    cout << "Sorry, this is an admin account" << endl;
				else cout << "Sorry, you do not have the ability of selling tickets because this is a buy-standard account" << endl;
			else if (input == "buy")
				if (type[tempInt] == "FS" || type[tempInt] == "BS")
					buy(tempInt);
                else if(adminLogin)
                    cout << "Sorry, this is an admin account" << endl;
				else cout << "Sorry, you do not have the ability of buying tickets because this is a sell-standard account" << endl;
			else if (input == "refund")
				if (adminLogin)
					refund();
                else 
                    cout << "Refund is for ADMINS ONLY" << endl;
			else
				cout << "invalid command" << endl;
        }

    }

 cout << "All done. Exiting..." << endl;
 return 0;
}
