#include <iostream>  
#include <list>      
#include <string>    
#include <algorithm> // sort
#include <iomanip>   // setw

using namespace std;

struct Contact {
    string name;   
    string phone1;  
    string phone2;  
};

const int ALPHABET_SIZE = 26;

class PhoneBook {
private:
    list<Contact> contacts;   
    list<string> globalNames;



    void bubbleSortGlobalNames() {
        for (auto it1 = globalNames.begin();     it1 != globalNames.end(); ++it1) {
            for (auto it2 = globalNames.begin(); next(it2) != globalNames.end(); ++it2) {
                if (*it2 > *next(it2)) {
                    iter_swap(it2, next(it2));
                }
            }
        }
    }



    int linearSearchGlobalNames(const string& name) {
        int index = 0;
        for (const auto& globalName : globalNames) {
            if (globalName == name) {
                return index; 
            }
            ++index;
        }
        return -1;
    }



public:
    PhoneBook() {}

    void addContact(const string& name, const string& phone1, const string& phone2) {
        Contact newContact{name, phone1, phone2};
        contacts.push_back(newContact);
        globalNames.push_back(name);
        bubbleSortGlobalNames();
    }



    bool editContact(const string& name, const string& newPhone1, const string& newPhone2) {
        for (auto& contact : contacts) {
            if (contact.name == name) {
                contact.phone1 = newPhone1;
                contact.phone2 = newPhone2;
                return true;
            }
        }
        return false;
    }



    bool deleteContact(const string& name) {
        auto it = find_if(contacts.begin(), contacts.end(), [&name](const Contact& c) { return c.name == name; });
        if (it != contacts.end()) {
            contacts.erase(it);
            globalNames.remove(name);
            return true;
        }
        return false;
    }


    Contact* searchContact(const string& name) {
        for (auto& contact : contacts) {
            if (contact.name == name) {
                return &contact;
            }
        }
        return nullptr;
    }






    void printContacts() {
        cout << "_______________________________________________________________________________________________\n";
        cout << "|             Name                |            Phone1            |             Phone2         |\n";
        cout << "_______________________________________________________________________________________________\n";

        for (const string& name : globalNames) {
            Contact* contact = searchContact(name);
            if (contact) {
                cout << "| " << setw(30) << left << contact->name
                     << "| " << setw(28) << left << contact->phone1
                     << "| " << setw(28) << left << contact->phone2 << "|\n";
            }
        }
        cout << "_______________________________________________________________________________________________\n";
    }




    void countContactsPerLetter() {
        int count[ALPHABET_SIZE] = {0};
        for (const auto& contact : contacts) {
            int index = tolower(contact.name[0]) - 'a';
            if (index >= 0 && index < ALPHABET_SIZE) {
                count[index]++;
            }
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            cout << char('A' + i) << ": " << count[i] << " contacts" << endl;
        }
    }
};

int main() {
    PhoneBook phoneBook;
    int choice;
    string name, phone1, phone2;

    do {
        cout << " ___________________________\n";
        cout << "/           .__             \\\n";
        cout << "| _________________________ |\n";
        cout << "||       Main Menu         ||\n";
        cout << "|| ------------------------||\n";
        cout << "|| 1. Add Contact          ||\n";
        cout << "|| 2. Edit Contact         ||\n";
        cout << "|| 3. Delete Contact       ||\n";
        cout << "|| 4. Search Contact       ||\n";
        cout << "|| 5. Number of Contacts   ||\n";
        cout << "|| 6. Print All Contacts   ||\n";
        cout << "|| 7. Exit                 ||\n";
        cout << "| --------------------------|   \n";
        cout << "|___________________________|\n";
        cout << "\\___________________________/\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone1: ";
                getline(cin, phone1);
                cout << "Enter phone2: ";
                getline(cin, phone2);
                phoneBook.addContact(name, phone1, phone2);
                break;

            case 2:
                cout << "Enter name of the contact to edit: ";
                getline(cin, name);
                cout << "Enter new phone1: ";
                getline(cin, phone1);
                cout << "Enter new phone2: ";
                getline(cin, phone2);
                if (phoneBook.editContact(name, phone1, phone2)) {
                    cout << "Contact updated successfully.\n";
                } else {
                    cout << "Contact not found.\n";
                }
                break;

            case 3:
                cout << "Enter name of the contact to delete: ";
                getline(cin, name);
                if (phoneBook.deleteContact(name)) {
                    cout << "Contact deleted successfully.\n";
                } else {
                    cout << "Contact not found.\n";
                }
                break;

            case 4:
                cout << "Enter name to search: ";
                getline(cin, name);
                if (Contact* contact = phoneBook.searchContact(name)) {
                    cout << "_______________________________________________________________________________________________\n";
                    cout << "|             Name                |            Phone1            |             Phone2         |\n";
                    cout << "_______________________________________________________________________________________________\n";
                    cout << "| " << setw(30) << left << contact->name
                         << "| " << setw(28) << left << contact->phone1
                         << "| " << setw(28) << left << contact->phone2 << "|\n";
                    cout << "_______________________________________________________________________________________________\n";
                } else {
                    cout << "Contact not found.\n";
                }
                break;

            case 5:
                phoneBook.countContactsPerLetter();
                break;

            case 6:
                phoneBook.printContacts();
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
