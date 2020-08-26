#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>

using namespace std;
struct Friend
{
	int ID;
	string name;
	string lastName;
	string phoneNumber;
	string mail_adress;
	string home_adress;	
};
void menu()
{
	system("cls");
	cout << "KSIAZKA ADRESOWA MENU" << endl;
	cout << "---------------------" << endl;
	cout << "1. Dodaj znajomych" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl kontakty" << endl;
	cout << "5. Usun kontakty" << endl;
	cout << "6. Zmodyfikuj kontakty" << endl;
	cout << "0. Koniec programu" << endl;
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
bool doesFriendAlreadyExist (vector<Friend> friendInBook, Friend friends)
{
	for (int i = 0; i< friendInBook.size(); i++)
	{
		if (friends.name == friendInBook[i].name && friends.lastName == friendInBook[i].lastName && friends.phoneNumber == friendInBook[i].phoneNumber &&
		friends.mail_adress == friendInBook[i].mail_adress && friends.home_adress == friendInBook[i].home_adress)
		{
			return true;
		}
		else continue;
	}
	return false;
}
void toFileOutput (fstream &file, vector<Friend> friendInBook)
{
	file.open("ksiazka_adresowa.txt", ios::out);
	for (int i = 0; i < friendInBook.size(); i++)
	{
		file << friendInBook[i].ID<< '|';
		file << friendInBook[i].name << '|';
		file <<	friendInBook[i].lastName<< '|';
		file <<	friendInBook[i].phoneNumber << '|';
		file <<	friendInBook[i].mail_adress << '|';
		file <<	friendInBook[i].home_adress << '|';
	
		file << endl;
	}
	file.close();
}
void addFriend (vector<Friend> &friendInBook, fstream &file, Friend friends, int &lastID)
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
		if (doesFriendAlreadyExist( friendInBook, friends) == true)
		{
			cout << "Taki znajomy juz istnieje w bazie danych!!!"<< endl;
			cout << "Powrot do wpisywania..." << endl;
			continue;
		}
		else
		{
			//friendsCount++;
			lastID++;
			friends.ID = lastID;
			friendInBook.push_back(friends);
			toFileOutput (file, friendInBook);
			cout << "Czy chcesz dodac kolejna osobe? T/N" << endl;
			cin >> koniec;

			if (koniec == 'T' || koniec == 't')
				continue;
			else
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
void findFriendByName (string firstName, vector<Friend> &friendInBook)
{
	bool foundIt = false;
	for (int i = 0; i< friendInBook.size(); i++)
	{
		if (friendInBook[i].name == firstName)
		{
			foundIt = true;
			displayFriends (friendInBook, i);
		}
		else if ((i == friendInBook.size() -1)&&foundIt == false)
		{
			cout << "W bazie brak osob o tym imieniu!" << endl;
			system ("pause");
		}
		else
		continue;
	}
}
void findFriendByLastName (string surname, vector<Friend> &friendInBook)
{
	bool foundIt = false;
	for (int i = 0; i< friendInBook.size(); i++)
	{
		if (friendInBook[i].lastName == surname)
		{
			foundIt = true;
			displayFriends (friendInBook, i);
		}
		else if ((i == friendInBook.size() -1)&& foundIt == false)
		{
			cout << "W bazie brak osob o tym nazwisku!" << endl;
			system ("pause");
		}
		else
			continue;
	}
}
int fromFileInput (Friend friends, fstream &file, vector<Friend> &friendInBook)
{
	string temp;
	int wordNumber = 1, nextFriend = 0;
	file.open("ksiazka_adresowa.txt", ios :: in);
	while (getline(file,temp,'|'))
	{
		switch (wordNumber)
		{
			case 1: friends.ID = atoi(temp.c_str());	 break;
			case 2: friends.name = temp; 				 break;
			case 3: friends.lastName = temp;			 break;
			case 4: friends.phoneNumber = temp; 		 break;
			case 5: friends.mail_adress = temp; 		 break;
			case 6: friends.home_adress = temp; 	 	 break;					
		}
		if (wordNumber == 6)
		{
			friendInBook.push_back(friends);
			wordNumber = 0;
			nextFriend++;
		}
			wordNumber++;
	}
		file.close();
		if (friendInBook.size() == 0)
			return 0;
		else
		{
			int lastID = friendInBook[nextFriend-1].ID;
			return lastID;
		}
}
void deleteFriend (vector<Friend> &friendInBook, int id, fstream &file)
{
	bool foundIt = false;
	for (int i = 0; i < friendInBook.size(); i++)
	{
		if (friendInBook[i].ID == id)
		{
			foundIt = true;
			auto it = friendInBook.begin() + i;
			friendInBook.erase(it);
			toFileOutput (file, friendInBook);
		}
		else if ((i == friendInBook.size() -1)&& foundIt == false)
		{
			cout << "Podano bledne ID uzytkownika" << endl;
			system ("pause");
		}
		else
			continue;
	}
}
void modifyFriend (vector<Friend> &friendInBook, int id, fstream &file)
{
	bool foundIt = false;
	system ("cls");
	for (int i = 0; i < friendInBook.size(); i++)
	{
		if (friendInBook[i].ID == id)
		{
			displayFriends (friendInBook, i);
			displayModificationMenu();
			foundIt = true;
			string modifiedText;
			auto it = friendInBook.begin() + i;
			int answer;
			cin >> answer;
			cout << "Wprowadz zmodyfikowane dane: " << endl;
			cin.ignore(256, '\n');
			getline (cin, modifiedText);
			switch (answer)
			{
				case 1: friendInBook[i].name = modifiedText; 				break;
				case 2: friendInBook[i].lastName = modifiedText;			break;
				case 3: friendInBook[i].phoneNumber = modifiedText; 		break;
				case 4: friendInBook[i].mail_adress = modifiedText; 		break;
				case 5: friendInBook[i].home_adress = modifiedText; 	 	break;
				case 6: break;
				default: cout << "Podana bledna wartosc, powrot..."; 		break;	 
			}
			toFileOutput (file, friendInBook);
		}
		else if ((i == friendInBook.size() -1)&& foundIt == false)
		{
			cout << "Podano bledne ID uzytkownika" << endl;
			system ("pause");
		}
		else
			continue;
	}
}

int main() 
{
  	Friend friends;
	vector<Friend> friendInBook;
	fstream file;
	char choice;
	if (!(file.good()))
	{
		file.open("ksiazka_adresowa.txt", ios :: out);
		file.close();
	}
	while (true)
	{
		friendInBook.clear();
		int lastID = fromFileInput (friends, file, friendInBook);
		menu();
		cin >> choice;
		switch (choice)
		{
			case '1':
				addFriend (friendInBook, file, friends, lastID);
				break;
			case '2':
				if (friendInBook.size() == 0)
				{
					displayEmptyBookInfo();
					break;	
				}	
				else
				{
					cout << "Podaj imie do znalezienia w ksiazce adresowej: ";
					string nameToFind;
					cin >> nameToFind;
					findFriendByName (nameToFind, friendInBook);		
				}
				cout << "Nacisnij enter aby kontynuowac: ";
				getchar(); getchar();
				break;	
			case '3':
				if (friendInBook.size() == 0)
				{
					displayEmptyBookInfo ();
					break;	
				}	
				else
				{
					cout << "Podaj nazwisko do znalezienia w ksiazce adresowej: ";
					string lastNameToFind;
					cin >> lastNameToFind;
					findFriendByLastName (lastNameToFind, friendInBook);
				}
				cout << "Nacisnij enter aby kontynuowac: ";
				getchar(); getchar();
				break;
			case '4':
				if (friendInBook.size() == 0)
				{
					displayEmptyBookInfo ();
					break;	
				}	
				else
				{
					for (int i = 0; i < friendInBook.size(); i++)
					{
						displayFriends (friendInBook, i);
					}
					cout << "Nacisnij enter aby kontynuowac: ";
					getchar(); getchar ();
					break;
				}
			case '5':
				if (friendInBook.size() == 0)
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
						deleteFriend (friendInBook, id, file);
						break;
					}
					else
						break;
				}
			case '6':
				if (friendInBook.size() == 0)
				{
					displayEmptyBookInfo ();
					break;	
				}
				else
				{
					int id;
					char answer;
					char continueAnswer;
						do
						{
							cout << "Podaj ID znajomego do modyfikacji: " << endl;
							cin >> id;
							cout << "Czy na pewno chcesz zmodyfikowac? (t/n)" << endl;
							cin >> answer;
							if (answer == 'T' || answer == 't')
							{
								modifyFriend(friendInBook, id, file);
								cout << "Czy chcesz kontynuowac? (t/n)" << endl;
								cin >> continueAnswer;
							}
							else
								break;
						}while (continueAnswer == 't' || continueAnswer == 'T');
						break;
					}					
			case '0':
				cout << "Do widzenia!" << endl;
				getchar(); getchar();
				exit (0);
			default:
				cout << "Bledny wybor, nacisnij enter aby powrocic do menu" << endl;
				getchar(); getchar();
				break;
		}
	}
	return 0;
}
