#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include<stdio.h> 
#include <stdlib.h>

using namespace std;
struct Friend
{
	int ID;
	int userID;
	string name;
	string lastName;
	string phoneNumber;
	string mail_adress;
	string home_adress;	
};
struct User
{
	int ID;
	string userName;
	string userLastName;
	string login;
	string password;
};
void loginMenu ()
{
	cout << "Ksiazka adresowa logowanie" << endl;
	cout << "-------------------------" << endl;
	cout << "1. Logowanie" << endl;
	cout << "2. Rejestracja" << endl;
	cout << "3. Koniec programu" << endl;
}
void toFileOutputUser (fstream &userFile, vector<User> &userInBook)
{
	userFile.open("Uzytkownicy.txt", ios::out);
	for (int i = 0; i < userInBook.size(); i++)
	{
		userFile << userInBook[i].ID<< '|';
		userFile << userInBook[i].userName << '|';
		userFile <<	userInBook[i].userLastName<< '|';
		userFile << userInBook[i].login <<'|';
		userFile <<	userInBook[i].password << '|';
		userFile << endl;
	}
	userFile.close();	
}
int fromFileInputUser (fstream &userFile, vector<User> &userInBook, User users)
{
	string temp;
	int wordNumber = 1, nextUser = 0;
	userFile.open("Uzytkownicy.txt", ios :: in);
	while (getline(userFile,temp,'|'))
	{
		switch (wordNumber)
		{
			case 1: users.ID = atoi(temp.c_str());	 break;
			case 2: users.userName = temp; 			 break;
			case 3: users.userLastName = temp;		 break;
			case 4: users.login = temp;				 break;	
			case 5: users.password = temp;			 break;
		}
		if (wordNumber == 5)
		{
			userInBook.push_back(users);
			wordNumber = 0;
			nextUser++;
		}
			wordNumber++;
	}
		userFile.close();
		if (userInBook.size() == 0)
			return 0;
		else
		{
			int lastID = userInBook[nextUser-1].ID;
			return lastID;
		}
}
void userRegister (vector<User> &userInBook, fstream &userFile, User users, int &lastUserID)
{
	while (true)
	{
		string temp;
		cin.ignore(256,'\n');
		cout << "Podaj dane:" << endl;
		cout << "Imie: ";
		getline(cin, users.userName);
		cout << "Nazwisko: ";
		getline(cin, users.userLastName);
		cout << "Login: ";
		getline (cin, users.login);
		cout << "Haslo: ";
		getline(cin, users.password);
		cout << "Powtorz haslo: ";
		getline(cin, temp);
		if (temp != users.password)
		{
			cout << "Hasla nie pokrywaja sie"<< endl;
			cout << "Sproboj ponownie" << endl;
			continue;
		}
		else
		{
			lastUserID++;
			users.ID = lastUserID;
			userInBook.push_back(users);
			toFileOutputUser (userFile, userInBook);
			break;
		}
	}
}
int checkForCorrectPassLoginCombination (string login, string pass, vector<User> userInBook)
{
	for (int i = 0; i< userInBook.size(); i++)
	{
		if (login == userInBook[i].login && pass == userInBook[i].password)
			return userInBook[i].ID;
		else if (i+1 == userInBook.size())
			return 0;	
	}	
}
int logIn (vector<User> userInBook)
{
	string login;
	string pass;
	while (true)
	{
		cin.ignore(256,'\n');
		cout << "Podaj login: ";
		getline (cin, login);
		cout << "Podaj haslo: ";
		getline (cin, pass);
		if (checkForCorrectPassLoginCombination (login, pass, userInBook) != 0)
		{
			cout << "Zalogowano pomyslnie!" << endl;
			Sleep (1000);
			return checkForCorrectPassLoginCombination (login, pass, userInBook);
		}
		else
		{
			cout << "Niepoprawny login lub haslo!" << endl;
			cout << "Czy chcesz spobowac ponownie? (T/N)" << endl;
			char answer;
			cin >> answer;
			if (answer == 'T'|| answer == 't')
				continue;
			else
				exit (0);
		}
	}
}
void menu()
{
	system("cls");
	cout << "Aby zapisac zmiany poprawnie sie wyloguj" << endl;
	cout << "KSIAZKA ADRESOWA MENU" << endl;
	cout << "---------------------" << endl;
	cout << "1. Dodaj znajomych" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl kontakty" << endl;
	cout << "5. Usun kontakty" << endl;
	cout << "6. Zmodyfikuj kontakty" << endl;
	cout << "0. Wyloguj" << endl;
}
void displayModificationMenu()
{
	cout << "Podaj element do modyfikacji: " << endl;
	cout << "1. Imie" << endl;
	cout << "2. Nazwisko" << endl;
	cout << "3. Nr telefonu" << endl;
	cout << "4. Adres e-mail" << endl;
	cout << "5. Adres" << endl;
	cout << "0. Powrot do menu" << endl;
}
void displayEmptyBookInfo ()
{
	cout << "Ksiazka adresowa jest pusta! ";
	cout << "Nacisnij enter aby kontynuowac: " << endl;
	getchar(); getchar();
}
bool doesFriendAlreadyExist (vector<Friend> loggedUserFriends, Friend friends)
{
	for (int i = 0; i< loggedUserFriends.size(); i++)
	{
		if (friends.name == loggedUserFriends[i].name && friends.lastName == loggedUserFriends[i].lastName && friends.phoneNumber == loggedUserFriends[i].phoneNumber &&
		friends.mail_adress == loggedUserFriends[i].mail_adress && friends.home_adress == loggedUserFriends[i].home_adress)
		{
			return true;
		}
		else continue;
	}
	return false;
}
void fileOutput (Friend friends, fstream &tempFile)
{
	tempFile << friends.ID << '|';
	tempFile << friends.userID << '|';
	tempFile << friends.name << '|';
	tempFile <<	friends.lastName<< '|';
	tempFile <<	friends.phoneNumber << '|';
	tempFile <<	friends.mail_adress << '|';
	tempFile <<	friends.home_adress << '|';
	tempFile << endl;
}
void toFileOutput (fstream &file, vector<Friend> loggedUserFriends, Friend friends, int loggedUser)
{
	fstream tempFile;
	tempFile.open("ksiazka tymczasowa.txt", ios::out | ios::app);
	file.open("ksiazka_adresowa.txt", ios::in);
	string temp;
	int wordNumber = 1;
	while (getline(file,temp,'|'))
	{
		switch (wordNumber)
		{
			case 1: friends.ID = atoi(temp.c_str());	 break;
			case 2: friends.userID = atoi(temp.c_str()); break;
			case 3: friends.name = temp; 				 break;
			case 4: friends.lastName = temp;			 break;
			case 5: friends.phoneNumber = temp; 		 break;
			case 6: friends.mail_adress = temp; 		 break;
			case 7: friends.home_adress = temp; 	 	 break;					
		}
		if (wordNumber == 7)
		{
			if (friends.userID != loggedUser)
			{
				fileOutput (friends, tempFile);
			}
			wordNumber = 0;
		}
			wordNumber++;
	}
	tempFile.close();
	tempFile.open("ksiazka tymczasowa.txt", ios::out | ios::app);
	for (int i = 0; i<loggedUserFriends.size(); i++)
	{
		fileOutput (loggedUserFriends[i], tempFile);
	}
	file.close(); tempFile.close();
	remove("ksiazka_adresowa.txt");
	rename ("ksiazka tymczasowa.txt","ksiazka_adresowa.txt");
}
void addFriend (vector<Friend> &loggedUserFriends, fstream &file, Friend friends, int &lastID, int loggedUser)
{
//	string imie, nazwisko, nrTel, mail, adresDomowy;
	char koniec = 'a';
	while (true)
	{
		cin.ignore(256,'\n');
		cout << "Podaj dane:" << endl;
		cout << "Imie: ";
		getline(cin, friends.name);
		cout << "Nazwisko: ";
		getline(cin, friends.lastName);
		cout << "Nr telefonu: ";
		getline(cin, friends.phoneNumber);
		cout << "Adres e-mail: ";
		getline(cin, friends.mail_adress);
		cout << "Adres domowy: ";
		getline (cin, friends.home_adress);
		if (doesFriendAlreadyExist( loggedUserFriends, friends) == true)
		{
			cout << "Taki znajomy juz istnieje w bazie danych!!!"<< endl;
			cout << "Powrot do wpisywania..." << endl;
			continue;
		}
		else
		{
			lastID++;
			friends.ID = lastID;
			friends.userID = loggedUser;
			loggedUserFriends.push_back(friends);
			cout << "Czy chcesz dodac kolejna osobe? T/N" << endl;
			cin >> koniec;

			if (koniec == 'T' || koniec == 't')
				continue;
			else
				toFileOutput ( file, loggedUserFriends, friends, loggedUser);
				break;
		}
	}
}
void displayFriends (vector<Friend> &friendInBook, int index)
{
	cout << "ID: " << friendInBook[index].ID << endl;
	cout << "Imie: " << friendInBook[index].name << endl;
	cout << "Nazwisko: " << friendInBook[index].lastName << endl;
	cout << "Nr telefonu: " << friendInBook[index].phoneNumber << endl;
	cout << "Adres e-mail: " << friendInBook[index].mail_adress << endl;
	cout << "Adres domowy: " << friendInBook[index].home_adress << endl;
	cout << endl;
}
void findFriendByName (vector<Friend> &loggedUserFriends)
{
	bool foundIt = false;
	cout << "Podaj imie do znalezienia w ksiazce adresowej: ";
	string nameToFind;
	cin >> nameToFind;
	for (int i = 0; i< loggedUserFriends.size(); i++)
	{
		if (loggedUserFriends[i].name == nameToFind)
		{
			foundIt = true;
			displayFriends (loggedUserFriends, i);
		}
		else if ((i == loggedUserFriends.size() -1)&&foundIt == false)
		{
			cout << "W bazie brak osob o tym imieniu!" << endl;
			system ("pause");
		}
		else
		continue;
	}
}
void findFriendByLastName (vector<Friend> &loggedUserFriends)
{
	bool foundIt = false;
	cout << "Podaj nazwisko do znalezienia w ksiazce adresowej: ";
	string lastNameToFind;
	cin >> lastNameToFind;
	for (int i = 0; i< loggedUserFriends.size(); i++)
	{
		if (loggedUserFriends[i].lastName == lastNameToFind)
		{
			foundIt = true;
			displayFriends (loggedUserFriends, i);
		}
		else if ((i == loggedUserFriends.size() -1)&& foundIt == false)
		{
			cout << "W bazie brak osob o tym nazwisku!" << endl;
			system ("pause");
		}
		else
			continue;
	}
}
void deleteFriend (fstream &file, vector<Friend> &loggedUserFriends, int id, int loggedUser)
{
	bool foundIt = false;
	for (int i = 0; i < loggedUserFriends.size(); i++)
	{
		if (loggedUserFriends[i].ID == id && loggedUserFriends[i].userID == loggedUser)
		{
			foundIt = true;
			auto it = loggedUserFriends.begin() + i;
			loggedUserFriends.erase(it);
		}
		else if ((i == loggedUserFriends.size() -1)&& foundIt == false)
		{
			cout << "Podano bledne ID uzytkownika" << endl;
			system ("pause");
		}
		else
			continue;
	}
}
void modifyFriend (vector<Friend> &loggedUserFriends, int id, fstream &file, int loggedUser, char &continueAnswer)
{
	bool foundIt = false;
	system ("cls");
	for (int i = 0; i < loggedUserFriends.size(); i++)
	{
		if (loggedUserFriends[i].ID == id && loggedUserFriends[i].userID == loggedUser)
		{
			displayFriends (loggedUserFriends, i);
			displayModificationMenu();
			foundIt = true;
			string modifiedText;
			int answer;
			cin >> answer;
			if (answer == 0)
				return;
			cout << "Wprowadz zmodyfikowane dane: " << endl;
			cin.ignore(256, '\n');
			getline (cin, modifiedText);
			switch (answer)
			{
				case 1: loggedUserFriends[i].name = modifiedText; 				break;
				case 2: loggedUserFriends[i].lastName = modifiedText;			break;
				case 3: loggedUserFriends[i].phoneNumber = modifiedText; 		break;
				case 4: loggedUserFriends[i].mail_adress = modifiedText; 		break;
				case 5: loggedUserFriends[i].home_adress = modifiedText; 	 	break;
				case 0: break;
				default: cout << "Podana bledna wartosc, powrot..."; 		break;	 
			}
		}
		else if ((i == loggedUserFriends.size() -1)&& foundIt == false)
		{
			cout << "Podano bledne ID uzytkownika" << endl;
			break;
		}
		else
			continue;
	}
	cout << "Czy chcesz kontynuowac? (t/n)" << endl;
	cin >> continueAnswer;
}
void rewriteUserFriends (Friend friends, fstream &file, vector<Friend> &loggedUserFriends, int loggedUser)
{
	loggedUserFriends.clear();
	int wordNumber = 1;
	string temp;
	file.open("ksiazka_adresowa.txt", ios::in);
	while (getline(file,temp,'|'))
	{
		switch (wordNumber)
		{
			case 1: friends.ID = atoi(temp.c_str());	; break;
			case 2: friends.userID = atoi(temp.c_str()); break;
			case 3: friends.name = temp; 				; break;
			case 4: friends.lastName = temp;			; break;
			case 5: friends.phoneNumber = temp; 		; break;
			case 6: friends.mail_adress = temp; 		; break;
			case 7: friends.home_adress = temp; 
				if (friends.userID == loggedUser)
					{
						loggedUserFriends.push_back(friends);
					}
					wordNumber = 0;	
					break;					
		}
		wordNumber++;
	}
	file.close();
}
int findMaxID (Friend friends, fstream &file)
{
	int wordNumber = 1;
	int max = 0;
	string temp;
	file.open("ksiazka_adresowa.txt", ios::in);
	while (getline(file,temp,'|'))
	{
		switch (wordNumber)
		{
			case 1: friends.ID = atoi(temp.c_str());	; break;
			case 2: friends.userID = atoi(temp.c_str()); break;
			case 3: friends.name = temp; 				; break;
			case 4: friends.lastName = temp;			; break;
			case 5: friends.phoneNumber = temp; 		; break;
			case 6: friends.mail_adress = temp; 		; break;
			case 7: friends.home_adress = temp; 
				if (friends.ID > max)
					{
						max = friends.ID;
					}
					wordNumber = 0;	
					break;					
		}
		wordNumber++;
	}
	file.close();
	return max;
}
int main() 
{
  	Friend friends;
  	User users;
	vector<User> userInBook;
	vector<Friend> loggedUserFriends;
	fstream file;
	fstream tempFile; 
	fstream userFile;
	int loggedUser;
	int logChoice;
	int lastUserID = fromFileInputUser (userFile, userInBook, users);
	while (true)
	{
		loginMenu ();
		cin >> logChoice;
		
		switch (logChoice)
		{
			case 1: loggedUser = logIn (userInBook);							break;
			case 2: userRegister (userInBook, userFile, users, lastUserID);		break;
			case 3: exit (0);
		}
		char choice;
		rewriteUserFriends (friends, file, loggedUserFriends, loggedUser);
		int maxID = findMaxID (friends, file);
		while (loggedUser != 0)
		{
			menu();
			cin >> choice;
			switch (choice)
			{
				case '1':
					addFriend (loggedUserFriends, file, friends, maxID, loggedUser);
					break;
				case '2':
					if (loggedUserFriends.size() == 0)
					{
						displayEmptyBookInfo();
						break;	
					}	
					else
					{
						findFriendByName (loggedUserFriends);		
					}
					cout << "Nacisnij enter aby kontynuowac: ";
					getchar(); getchar();
					break;	
				case '3':
					if (loggedUserFriends.size() == 0)
					{
						displayEmptyBookInfo ();
						break;	
					}	
					else
					{
						findFriendByLastName (loggedUserFriends);
					}
					cout << "Nacisnij enter aby kontynuowac: ";
					getchar(); getchar();
					break;
				case '4':
					if (loggedUserFriends.size() == 0)
					{
						displayEmptyBookInfo ();
						break;	
					}	
					else
					{
						for (int i = 0; i < loggedUserFriends.size(); i++)
						{
							displayFriends (loggedUserFriends, i);
						}
						cout << "Nacisnij enter aby kontynuowac: ";
						getchar(); getchar ();
						break;
					}
				case '5':
					if (loggedUserFriends.size() == 0)
					{
						displayEmptyBookInfo ();
						break;	
					}	
					else
					{
						int id;
						char answer;
						cout << "Podaj ID znajomego do usuniecia: " << endl;
						cin >> id;
						cout << "Czy na pewno chcesz usunac? (t/n)" << endl;
						cin >> answer;
						if (answer == 'T' || answer == 't')
						{
							deleteFriend (file, loggedUserFriends, id, loggedUser);
							toFileOutput (file, loggedUserFriends, friends, loggedUser);
							break;
						}
						else
							break;
					}
				case '6':
					if (loggedUserFriends.size() == 0)
					{
						displayEmptyBookInfo ();
						break;	
					}
					else
					{
						int id;
						char answer;
						char continueAnswer;
						cout << "Podaj ID znajomego do modyfikacji: " << endl;
						cin >> id;
						cout << "Czy na pewno chcesz zmodyfikowac? (t/n)" << endl;
						cin >> answer;
						do
						{
							if (answer == 'T' || answer == 't')
							{
								modifyFriend(loggedUserFriends, id, file, loggedUser, continueAnswer);
								toFileOutput (file, loggedUserFriends, friends, loggedUser);
							}
							else
								break;
						}while (continueAnswer == 't' || continueAnswer == 'T');
						break;
					}					
				case '0':
					cout << "Do widzenia!" << endl;
					getchar(); getchar();
					toFileOutput (file, loggedUserFriends, friends, loggedUser);
					loggedUser = 0;
					break;
				default:
					cout << "Bledny wybor, nacisnij enter aby powrocic do menu" << endl;
					getchar(); getchar();
					break;
			}
		}
	}
	return 0;
}
