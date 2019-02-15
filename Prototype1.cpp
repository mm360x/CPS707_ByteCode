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

string login_checker(string username)//searches for if a username matches an existing username
{
  int jk = 0;
  while(jk < userNumber)
  {
    if(username == user[jk])
    {
      return username;
    }
    jk++;
  }
  return "invalid";
}

int main() 
{
  string input = "", username = "", temp = "", str = "";
  inFile.open("currentUserAccounts.txt");
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
 //Testing the login command
 cin >> input;
 if( input == "login")
 {
    cout << "Enter a username" << endl;
    cin >> input;
    username = login_checker(input);
    if(username == "invalid")
    {
      cout << "The user " << username << " does not exist!" << endl;
    }
    else
    {
      cout << "You are now logged on as \"" << username << "\"" << endl;
    }
 }
 else
 {
   cout << "You need to login into your account first" << endl;
 }

 // How to get a number.
 int myNumber = 0;
/*
 while (true) {
   cout << "Please enter a valid number: ";
   getline(cin, input);

   // This code converts from string to number safely.
   stringstream myStream(input);
   if (myStream >> myNumber)
     break;
   cout << "Invalid number, please try again" << endl;
 }
 cout << "You entered: " << myNumber << endl << endl;

 // How to get a single char.
 char myChar  = {0};

 while (true) {
   cout << "Please enter 1 char: ";
   getline(cin, input);

   if (input.length() == 1) {
     myChar = input[0];
     break;
   }

   cout << "Invalid character, please try again" << endl;
 }
 cout << "You entered: " << myChar << endl << endl;
*/
 cout << "All done. And without using the >> operator" << endl;

 return 0;
}
