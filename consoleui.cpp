#include <iostream>
#include "consoleui.h"
#include "performer.h"
#include "dataaccess.h"
#include <QtSql>

using namespace std;

ConsoleUI::ConsoleUI()
{

}

void ConsoleUI::run()
{
    intro(); // Prentar upphafsskilaboð
    commandHelp(); // Prentar lista yfir skipanir
    _service.openFiles();
    string command;

    do
    {

        cout << endl << "Enter a command ('help' for list of commands): ";
        cin >> command;
        cout << endl;

        if (command == "list")
        {
            {
                int counter = 0;
                do
                {
                    char choice;
                    cout << "List Computer Scientists choose '1'" << endl << "List Computers choose '2'" << endl;
                    cout << "choice: ";
                    cin >> choice;
                    cout << endl;
                    if(choice == '1')
                    {
                        counter = 1;
                        sortScientists();
                    }
                    else if(choice == '2')
                    {
                        counter = 1;
                        sortComputers();
                    }
                    else
                    {
                        cout << "invalid choice!" << endl;
                    }
                }while(counter == 0);

            }

        }
        else if (command == "add")
        {
            int counter = 0;
            do
            {
                char choice;
                cout << "Add Computer Scientist choose '1'" << endl << "Add Computer choose '2'" << endl;
                cout << "choice: ";
                cin >> choice;
                if(choice == '1')
                {
                    counter = 1;
                    _data.writeData();
                }
                else if(choice == '2')
                {
                    counter = 1;
                    _data.addCpu();
                }
                else
                {
                    cout << "invalid choice!" << endl;
                }
            }while(counter == 0);

        }
        else if (command == "search")
        {
            displaySearch();
        }
        else if (command == "delete")
        {            
            string namedel; //Ná í strenginn sem á að eyða
            int counter = 0;
            do
            {
                char choice;
                cout << "Remove Computer Scientist choose '1'" << endl << "Remove Computer choose '2'" << endl;
                cout << "choice: ";
                cin >> choice;
                if(choice == '1')
                {
                    cout << "Input name of scientist: ";
                    namedel = deleteElement();
                    counter = 1;
                    _service.removeScientist(namedel); //Eyða völdu nafni með removeElement fallinu
                }
                else if(choice == '2')
                {
                    cout << "Input name of computer: ";
                    namedel = deleteElement();
                    counter = 1;
                    _service.removeComputer(namedel); //Eyða völdu nafni með removeElement fallinu
                }
                else
                {
                    cout << "invalid choice!" << endl;
                }
            }while(counter == 0);
            cout << namedel << " has been deleted from database." << endl;
        }
        else if (command == "help")
        {
            commandHelp();
        }
        else if (command == "exit")
        {
            cout << "exiting" << endl;
        }
        else if (command == "join")
        {
           int number;
           cout << "choose '1' to see wich Scientist made wich Computer." << endl;
           cout << "choose '2' to see wich computer was made by wich Scientist" << endl;
           cin >> number;
           cout << endl;
           if(number == 1)
           {
               string sId = "S.id";
               int id;
               cout << "Enter Scientist ID: ";
               cin >> id;
               cout << endl;
               vector<Relations> pf = _service.startJoin(sId, id);

               for(size_t i = 0; i < pf.size(); i++)
               {
                   qDebug().noquote().nospace() << pf[i].getSName() << "\t\t" << pf[i].getCName();
               }
           }
           else if(number == 2)
           {
               string cId = "C.id";
               int id;
               cout << "Enter Scientist ID: ";
               cin >> id;
               cout << endl;
               vector<Relations> pf = _service.startJoin(cId, id);

               for(size_t i = 0; i < pf.size(); i++)
               {
                   qDebug().noquote().nospace() << pf[i].getSName() << "\t\t" << pf[i].getCName();
               }
           }
        }
        else
        {
            cout << "invalid command." << endl;
            cout << "Enter 'help' to see list of commands" << endl;
        }

    }while (command != "exit");
}
void ConsoleUI::displayListOfPerformers(vector<Performer> pf) //Prentar lista af tölvunarfræðingum
{
    /*
    cout << endl;
    cout << "                      " << "---- List of all computer scientists in the system ----" << endl;
    cout << endl;

    displayTopTable();

    vector<Performer> pf = _service.getPerformers();
    */

    for (size_t i = 0; i < pf.size(); ++i) //Prentar út listann miðað við lengd nafns svo það passi sem best
        {



            if(pf[i].getName().length() > 16)
            {
            qDebug().noquote().nospace() << pf[i].getId() << "\t" << pf[i].getName() << "\t" << pf[i].getGender()
                                         << "\t\t" << pf[i].getbYear() << "\t\t\t" << pf[i].getdYear()
                                         << "\t\t\t" << pf[i].getNation();
            }
            else if(pf[i].getName().length() < 16 && pf[i].getName().length() > 7)
            {
            qDebug().noquote().nospace() << pf[i].getId() << "\t" << pf[i].getName() << "\t\t" << pf[i].getGender()
                                         << "\t\t" << pf[i].getbYear() << "\t\t\t" << pf[i].getdYear()
                                         << "\t\t\t" << pf[i].getNation();
            }
            else if(pf[i].getName().length() <= 7)
            {
            qDebug().noquote().nospace() << pf[i].getId() << "\t" << pf[i].getName() << "\t\t\t" << pf[i].getGender()
                                         << "\t\t" << pf[i].getbYear() << "\t\t\t" << pf[i].getdYear()
                                         << "\t\t\t" << pf[i].getNation();
            }

        }
}
void ConsoleUI::displaySearch() //Prentar út leitarniðurstöður
{
    string input;
    char choice;

    cout << "To search for computer scientist press 1" << endl;
    cout << "To search for computer press 2" << endl;
    cin >> choice;

    if(choice == '1')
    {
            cout << "Enter full name of computer scientist (the search is case-sensitive): ";
            cin.ignore();
            getline(cin, input);
            QString name = QString::fromStdString(input);


            vector <Performer> newVector = _service.searchpeople(name);
            if(newVector.size() == 0)
            {
                cout << "Nothing was found! Please enter 'search' to try again" << endl;
            }
            if(newVector.size() > 0)
            {
                cout << endl;
                cout << "                            " << "---- Result of your search in the system ----" << endl;
                cout << endl;

                displayTopTable();
            }

            for(size_t i = 0; i < newVector.size(); i++) //Forlykkja prentar niðurstöður miðað við lengd nafns svo það passi sem best
            {
                if(newVector[i].getName().length() > 16)
                {
                qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t" << newVector[i].getGender()
                                             << "\t\t" << newVector[i].getbYear() << "\t\t\t" << newVector[i].getdYear()
                                             << "\t\t\t" << newVector[i].getNation();
                }
                else if(newVector[i].getName().length() < 16 && newVector[i].getName().length() > 8)
                {
                qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t\t" << newVector[i].getGender()
                                             << "\t\t" << newVector[i].getbYear() << "\t\t\t" << newVector[i].getdYear()
                                             << "\t\t\t" << newVector[i].getNation();
                }
                else if(newVector[i].getName().length() <= 8)
                {
                qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t\t\t" << newVector[i].getGender()
                                             << "\t\t" << newVector[i].getbYear() << "\t\t\t" << newVector[i].getdYear()
                                             << "\t\t\t" << newVector[i].getNation();
                }
            }
    }
     if(choice == '2')
     {
         cout << "Enter the name of the computer (the search is case-sensitive): ";
         cin.ignore();
         getline(cin, input);
         QString name = QString::fromStdString(input);


         vector <computers> newVector = _service.searchcomputer(name);
         if(newVector.size() == 0)
         {
             cout << "Nothing was found! Please enter 'search' to try again" << endl;
         }
         if(newVector.size() > 0)
         {
             cout << endl;
             cout << "                            " << "---- Result of your search in the system ----" << endl;
             cout << endl;
             displayTopComputers();

         }
         for(size_t i = 0; i < newVector.size(); i++) //Forlykkja prentar niðurstöður miðað við lengd nafns svo það passi sem best
         {
             if(newVector[i].getName().length() > 16)
             {
             qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t" << newVector[i].getBuildy()
                                          << "\t\t" << newVector[i].getBrand() << "\t\t\t" << newVector[i].getConstr();
             }
             else if(newVector[i].getName().length() < 16 && newVector[i].getName().length() > 8)
             {
             qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t\t" << newVector[i].getBuildy()
                                          << "\t\t" << newVector[i].getBrand() << "\t\t\t" << newVector[i].getConstr();
             }
             else if(newVector[i].getName().length() <= 8)
             {
             qDebug().noquote().nospace() << i+1 << "\t" << newVector[i].getName() << "\t\t\t" << newVector[i].getBuildy()
                                          << "\t\t" << newVector[i].getBrand() << "\t\t\t" << newVector[i].getConstr();
             }
         }
     }
}
string ConsoleUI::inputName() //Setur inn nafn
{
    string name;
    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, name);

    int nameLength = name.length();

    for(int i = 0;i < nameLength;i++)
     {
        while(!isalpha(name[i]) && name[i] != ' ') //Passar að inntak fyrir nafn sé ekki tala eða tómt
               {
                   cout << "Invalid input, please try again: ";
                   cin.ignore();
                   getline(cin, name);
                   nameLength = name.length();
                }
    }
    return name;
}
string ConsoleUI::inputGender() //Setur inn kyn
{
    string gender;
    cout << "Enter gender (Male or Female): ";
    do //Passar að öll prentuð kyn séu annaðhvort "Male" eða "Female"
    {
        getline(cin, gender);
        if(gender == "Male")
        {
            return gender;
        }
        else if (gender == "male")
        {
            gender = "Male";
            return gender;
        }
        else if(gender == "Female")
        {
            return gender;
        }
        else if (gender == "female")
        {
            gender = "Female";
            return gender;
        }
        else
        {
            cout << "Invalid input, please try again." << endl;
            cout << "Enter gender (Male or Female): ";
        }
    }while(1 == 1);
    return gender;
}
string ConsoleUI::inputBirth() //Setur inn fæðingarár
{
    string birth;
    cout << "Enter year of birth: ";
    getline(cin, birth);
    int value = atoi(birth.c_str());
    int birthLength = birth.length();

    for(int i = 0;i < birthLength;i++)
     {
        while(!isdigit(birth[i])) //Ef fæðingarár er ekki tala fæst villa
               {
                   cout << "Invalid input, please try again: ";
                   getline(cin, birth);
                   birthLength = birth.length();
               }
    }

    while(value < 0 || value > 2016) //Ef fæðingarár er undir 0 eða yfir 2016 fæst villa
    {
        cout << "That is not a valid year" << endl;
        cout << "Enter year of birth: ";
        getline(cin, birth);
        value = atoi(birth.c_str()); //Breytir strengnum fyrir fæðingarár í tölu.
    }
    return birth;
}
string ConsoleUI::inputDeath() //Setur inn dánarár
{
    string death;
    cout << "Enter year of death or enter '--' if person is alive: ";
    getline(cin, death);
    int value = atoi(death.c_str());
    if(death == "--")
    {
        return death;
    }
    int deathLength = death.length();

    for(int i = 0;i < deathLength;i++)
     {
        while(!isdigit(death[i])) //Ef dánarár er ekki tala fæst villa
               {
                   cout << "Invalid input, please try again: ";
                   getline(cin, death);
                   deathLength = death.length();
               }
    }
    while(value < 0 || value > 2016) //Ef dánarár er undir 0 eða yfir 2016 fæst villa
    {
        cout << "That's not a valid year" << endl;
        cout << "Enter year of death: ";
        getline(cin, death);
        value = atoi(death.c_str());
    }

    return death;
}
string ConsoleUI::inputNation() //Setur inn þjóðerni
{
    string nation;
    cout << "Enter Nationality: ";
    getline(cin, nation);

    int nationLength = nation.length();

    for(int i = 0;i < nationLength;i++)
     {
        while(!isalpha(nation[i])) //Ef þjóðerni er ekki bókstafur fæst villa
               {
                   cout << "Invalid input, please try again: ";
                   getline(cin, nation);
                   nationLength = nation.length();
               }
    }

    return nation;
}
void ConsoleUI::commandHelp()
{
    cout << "-------- The commands are case-sensitive! --------" << endl << endl;
    cout << "list   - Choose to list all Computer Scientist or all Computers" << endl;
    cout << "add    - Choose to add a Computer Scientist or to add a Computer" << endl;
    cout << "search - Searches for a given computer scientist" << endl;
    cout << "delete - This will remove the entry from the list" << endl;
    cout << "help   - Displays list of commands" << endl;
    cout << "exit   - This will close the application" << endl;
}
void ConsoleUI::commandAdd() //Fall sem bætir við tölvunarfræðingum
{
    string name = inputName();
    string gender = inputGender();
    string birth = inputBirth();
    string death = inputDeath();
    int value = 0;
    int value2 = 0;

    if(death != "--")
    {
    value = atoi(birth.c_str()); // Breytir strengnum í birth í tölu
    value2 = atoi(death.c_str()); // Breytir strengnum í death í tölu
    }
    while(value2 < value) //Passar að talan í dánarári getur ekki verið minni en í fæðingarári
    {
        cout << "Death year can not be less than birth year! Please try again. " << endl;
        death = inputDeath();
        if(death == "--") //Ef tölvunarfræðingur er á lífi heldur fallið áfram
        {
            break;
        }
        value2 = atoi(death.c_str());

    }
    string nation = inputNation();
    _service.addPerformer(name, gender, birth, death, nation);
    cout << endl;
    cout << name << " has been added to the database!" << endl;
}
void ConsoleUI::intro() //Fall sem útprentar upphafsskilaboð
{
    cout << endl;
    cout << "It is recommended to extend the console when using this program" << endl;
    cout << endl;
    cout << "This program is designed to keep track of some details on known computer scientists. " << endl;
    cout << "The user is able to enter known persons from the history of computer science into a database." << endl;
    cout << "The user can remove persons from the database." << endl;
    cout << "The program can display a list of the characters that have been entered into the database." << endl;
    cout << "The user is able to enter known characters from the history of computer science into a database." << endl;
    cout << "The program can display a list of the persons that have been entered into the database." << endl;
    cout << "The program can sort a list by the user's preferences" << endl;
    cout << "It is possible for the user to perform a search of a specific person from the list." << endl << endl;
    for (int i = 0; i < 54*2; ++i)
    {
        cout << "=";
    }
    cout << endl;
    cout << endl;
    cout << "Please enter one of the following commands to continue:" << endl;
    cout << endl;
}
void ConsoleUI::displayTopTable() //Fall sem prentar lista yfir alla tölvunarfræðinga í skránni
{
    cout << "ID" << "\t" << "Name" << "\t\t\t" << "Gender";
    cout << "\t\t" << "Birth year" << "\t\t" << "Deceased" << "\t\t" <<"Nationality" << endl;
    for (int i = 0; i < 54*2; ++i)
    {
        cout << "=";
    }
    cout << endl;
}
string ConsoleUI::deleteElement()
{
    string name;
    cin.ignore();
    getline(cin, name);

    return name;
}
void ConsoleUI::displayComputers(vector<computers> pc)
{

    displayTopComputers();


    for (size_t i = 0; i < pc.size(); ++i) //Prentar út listann miðað við lengd nafns svo það passi sem best
        {



            if(pc[i].getName().length() > 16)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t" << pc[i].getBuildy()
                                         << "\t\t" << pc[i].getBrand() << "\t\t\t" << pc[i].getConstr();
            }
            else if(pc[i].getName().length() < 16 && pc[i].getName().length() > 7)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t\t" << pc[i].getBuildy()
                                         << "\t\t" << pc[i].getBrand() << "\t\t\t" << pc[i].getConstr();
            }
            else if(pc[i].getName().length() <= 7)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t\t\t" << pc[i].getBuildy()
                                         << "\t\t" << pc[i].getBrand() << "\t\t\t" << pc[i].getConstr();
            }

        }
}
void ConsoleUI::displayTopComputers()
{
    cout << "ID" << "\t" << "Name" << "\t\t\t" << "build Year";
    cout << "\t\t" << "Brand" << "\t\t" << "Constr" << endl;
    for (int i = 0; i < 42*2; ++i)
    {
        cout << "=";
    }
    cout << endl;
}
void ConsoleUI::sortComputers()
{
    int choice;
    cout << "Choose '1' to display a list sorted in alphabetical order" << endl;
    cout << "Choose '2' to display a list sorted by build year" << endl;
    cout << "Choose '3' to display a list sorted by Brand" << endl;
    cout << "Choose '4' to display a list sorted by Constr" << endl;
    cout << "Enter a number to continue: ";
    cin >> choice;
    cout << endl;
    if(choice == 1)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string name = "name";
            vector <computers> pf = _data.sortCpu(name, ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string name = "name";
            vector <computers> pf = _data.sortCpu(name, DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 2)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string buildY = "buildy";
            vector <computers> pf = _data.sortCpu(buildY, ASC);
            displayComputers(pf);

        }
        if(number == 2)
        {
            string DESC = "DESC";
            string buildY = "buildy";
            vector <computers> pf = _data.sortCpu(buildY, DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 3)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string brand = "type";
            vector <computers> pf = _data.sortCpu(brand, ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string brand = "type";
            vector <computers> pf = _data.sortCpu(brand, DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 4)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string constr = "constr";
            vector <computers> pf = _data.sortCpu(constr, ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string constr = "constr";
            vector <computers> pf = _data.sortCpu(constr, DESC);
            displayComputers(pf);
        }
    }
}
void ConsoleUI::sortScientists()
{
    int choice;
    cout << "Choose '1' to display a list sorted in alphabetical order" << endl;
    cout << "Choose '2' to display a list sorted by gender" << endl;
    cout << "Choose '3' to display a list sorted by birth Year" << endl;
    cout << "Choose '4' to display a list sorted by death Year" << endl;
    cout << "Choose '5' to display a list sorted by nation" << endl;
    cout << "Enter a number to continue: ";
    cin >> choice;
    cout << endl;
    if(choice == 1)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string name = "name";
            vector<Performer> pf = _data.sortScientists(name, ASC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string name = "name";
            vector<Performer> pf = _data.sortScientists(name, DESC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 2)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string gender = "gender";
            vector<Performer> pf = _data.sortScientists(gender, ASC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string gender = "gender";
            vector<Performer> pf = _data.sortScientists(gender, DESC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 3)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string bYear = "byear";
            vector<Performer> pf = _data.sortScientists(bYear, ASC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string bYear = "byear";
            vector<Performer> pf = _data.sortScientists(bYear, DESC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 4)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string dYear = "dyear";
            vector<Performer> pf = _data.sortScientists(dYear, ASC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string dYear = "dyear";
            vector<Performer> pf = _data.sortScientists(dYear, DESC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 5)
    {
        int number;
        cout << "choose '1' for Ascending list." << endl;
        cout << "choose '2' for Descending list." << endl;
        cout << "Enter a number to continue: ";
        cin >> number;
        if(number == 1)
        {
            string ASC = "ASC";
            string nation = "nation";
            vector<Performer> pf = _data.sortScientists(nation, ASC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string nation = "nation";
            vector<Performer> pf = _data.sortScientists(nation, DESC);
            displayTopTable();
            displayListOfPerformers(pf);
        }
    }

}
