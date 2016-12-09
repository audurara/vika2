#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
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
    subIntro(); //Prentar leiðbeiningar
    _service.openFiles();
    string command;

    do
    {
        cout << endl << "Enter a command to continue ('help' for list of commands): ";
        cin >> command;
        cout << endl;

        if (command == "list")
        {
            {
                bool found = false;
                cin.ignore();
                cout << "Do you want to display list of scientist or computers? " << endl;
                cout << "Type '1' for scientists" << endl << "Type '2' for computers" << endl << endl;
                cout << "Select: ";
                do
                {
                    string choice;
                    getline(cin, choice);
                    cout << endl;
                    int value = atoi(choice.c_str());

                    if(value == 1)
                    {
                        sortScientists();
                        found = true;
                        break;
                    }
                    else if(value == 2)
                    {
                        sortComputers();
                        found = true;
                        break;
                    }
                    if(choice.length() != 1)
                    {
                        cout << "Invalid input, please try again: ";
                    }
                    else
                    {
                        cout << "Invalid input, please try again: ";
                    }

                }while(!found);
            }
        }
        else if (command == "add")
        {
            cin.ignore();
            int counter = 0;
            string choice;

            do
            {
                cout << "Add Computer Scientist choose '1'" << endl << "Add Computer choose '2'" << endl;
                cout << "Choice: ";
                getline(cin, choice);

                if(choice.length() != 1)
                {
                    cout << "Invalid input, please try again: " << endl;
                }
                else{
                    char a = choice[0];

                    if(a == '1')
                    {
                        counter = 1;
                        commandAdd();
                    }
                    else if(a == '2')
                    {
                        counter = 1;
                        addComputer();
                    }
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
            int krona = 0;
            do
            {
                int choice;
                cout << "Remove Computer Scientist choose '1'" << endl << "Remove Computer choose '2'" << endl;
                cout << "Choice: ";
                cin.ignore();
                choice = checkInput(0,3);
                cout << endl;
                if(choice == 1)
                {
                    krona = 1;
                    tableLook(krona);
                    cout << endl;
                    cout << "--- Please enter ID to delete from database ---";
                    cout << endl << endl;
                    cout << "Input ID of a Scientist to delete: ";
                    namedel = deleteElement();
                    counter = 1;
                    _service.removeScientist(namedel); //Eyða völdu nafni með removeElement fallinu
                }
                else if(choice == 2)
                {
                    krona = 2;
                    tableLook(krona);
                    cout << endl;
                    cout << "--- Please enter ID to delete from database ---";
                    cout << endl << endl;
                    cout << "Input ID of a Computer to delete: ";
                    namedel = deleteElement();
                    counter = 1;

                    _service.removeComputer(namedel); //Eyða völdu nafni með removeElement fallinu
                }
                else
                {
                    cout << "Invalid input, please try again: " << endl;
                }

            }while(counter == 0);

            cout << "Delete succesfull." << endl;
        }
        else if (command == "help")
        {
            commandHelp();
        }
        else if (command == "exit")
        {
            cout << "Exiting!" << endl;
        }
        else if (command == "join")
        {
            cout << "Choose '1' To see list of joined Computer Scientists and Computers" << endl;
            cout << "Choose '2' To join a Computer Scientist and a Computer" << endl;
            cout << "Choose '3' To remove a joined connection" << endl << endl;
            cout << "Enter a number: ";
            cin.ignore();
            int choice = checkInput(0,4);
            cout << endl;

            if(choice == 1)
            {
                displayJoin();
            }
            if(choice == 2)
            {
                displayTable();
                addJoin();
            }
            if(choice == 3)
            {
                removeJoin();
            }
        }
        else
        {
            cout << "Invalid command." << endl;
            cout << "Enter 'help' to see list of commands" << endl;
        }

    }while (command != "exit");
}
void ConsoleUI::displayListOfPerformers(vector<Performer> pf) //Prentar lista af tölvunarfræðingum
{
    displayTopTable();

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
    cout << "Please type '1' for scientist." << endl;
    cout << "Please type '2' for computer." << endl;
    cin.ignore();
    int choice = checkInput(0,3);

    if(choice == 1)
    {
            cout << "Please type name of computer scientist to search for: ";
            cin.ignore();
            getline(cin, input);
            QString name = QString::fromStdString(input);

            vector <Performer> newVector = _service.searchpeople(name);
            if(newVector.size() == 0)
            {
                char val;

                cout << endl;
                cout << "No match found in database." << endl;
                cout << endl;
                cout << "Do you want to add " << input << " to the database?(y/n): ";
                cin >> val;

                         if(val == 'y' || val == 'Y')
                        {
                            commandAdd();
                        }
                        else if(val == 'n' || val == 'N')
                        {
                            cout << "You can do this later with 'add' command." << endl;
                        }
                        else
                        {
                            cout << "Invalid input, please try again (y/n): ";
                        }
                    }

            if(newVector.size() > 0)
            {
                cout << endl;
                cout << "                            " << "---- Result of your search in the system ----" << endl;
                cout << endl;

                displayListOfPerformers(newVector);
            }
    }
     if(choice == 2)
     {
         cout << "Enter name of computer: ";
         getline(cin, input);
         QString name = QString::fromStdString(input);

         vector <computers> newVector = _service.searchcomputer(name);
         if(newVector.size() == 0)
         {
             char val2;

             cout << endl;
             cout << "No match found in database." << endl;
             cout << endl;
             cout << "Do you want to add " << input << " to the database?(y/n): ";
             cin >> val2;

             if(val2 == 'y' || val2 == 'Y')
             {
                 addComputer();
             }
             else if(val2 == 'n' || val2 == 'N')
             {
                 cout << "You can do this later with 'add' command." << endl;
             }
             else
             {
                 cout << "Invalid input, please try again (y/n): ";
             }
             return;
         }

         if(newVector.size() > 0)
         {
             cout << endl;
             cout << "                            " << "---- Result of your search in the system ----" << endl;
             cout << endl;

         }
     }
}

string ConsoleUI::inputName() //Setur inn nafn
{
    string name;
    cout << "Enter full name: ";
    getline(cin, name);

    int nameLength = name.length();

    for(int i = 0;i < nameLength;i++)
     {
        while(!isalpha(name[i]) && name[i] != ' ') //Passar að inntak fyrir nafn sé ekki tala eða tómt
               {
                   cout << "Invalid input, please try again: ";
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
            cout << "Invalid input, please try again: " << endl;
            cout << "Enter gender (Male or Female): ";
        }
    }while(1 == 1);
    return gender;
}

int ConsoleUI::inputYear(int val1, int val2) //Setur inn ár
{
    //cin.ignore();
    bool found = false;
    int value;

    do {
        string choice;
        getline(cin, choice);
        value = atoi(choice.c_str());
        int length = static_cast<int>(choice.length());

        if(length < 0 || length > 4)
        {
            cout << "Invalid input, please try again: ";
        }
        else if(value > val1 && value < val2)
        {
            found = true;
        }
        else {
            cout << "Invalid input, please try again: ";
        }

    } while (!found);

        return value;
}
string ConsoleUI::inputDeath() //Setur inn dánarár
{
    string death;
    cout << "Enter year of death or enter '--' if person is alive: ";
    getline(cin, death);

    if(death == "--")
    {
        return death;
    }
    int value = atoi(death.c_str());
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
    cout << "-------- List of commands for the database --------" << endl << endl;
    cout << "Type   'list'   to display a complete list by categories in the database." << endl;
    cout << "Type   'add'    to add a Computer Scientist or a Computer" << endl;
    cout << "Type   'search' to perform a thorough search of the database" << endl;
    cout << "Type   'delete' to delete item from the database" << endl;
    cout << "Type   'join'   to see or update connetions between scientists and computers" << endl;
    cout << "Type   'help'   to displays list of commands" << endl;
    cout << "Type   'exit'   to close the application" << endl << endl;
    cout << "Note that the commands are case-sensitive!" << endl << endl;

}
void ConsoleUI::commandAdd() //Fall sem bætir við tölvunarfræðingum
{
    string name = inputName();
    string gender = inputGender();
    cout << "Enter year of birth: ";
    int birth = inputYear(0,2017);
    string death = inputDeath();
    int value = 0;
    int value2 = 0;
    string birthyear;
    ostringstream convert;
    convert << birth;
    birthyear = convert.str();

    if(death != "--")
    {
    value = atoi(birthyear.c_str()); // Breytir strengnum í birth í tölu
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
    _service.addPerformer(name, gender, birthyear, death, nation);
    cout << endl;
    cout << name << " has been added to the database!" << endl;
    cout << "Do you want to connect this scientist to a computer in the database?(Y/N): ";
        char yN;
        cin >> yN;
        if(yN == 'y' || yN == 'Y')
        {
            displayTable();
            addJoin();
        }
}

void ConsoleUI::addComputer()
{
    string brand, constr;
    string name = inputCname();
    cout << "Enter build year of computer: ";
    int buildy = inputYear(0,2017);
    string birthyear;
    ostringstream convert;
    convert << buildy;
    birthyear = convert.str();
    cout << "Enter type of computer: ";
    cin >> brand;
    cout << "was it built or not?(Yes/No): ";
    cin >> constr;
    _service.addComputer(name, birthyear, brand, constr);
}
void ConsoleUI::intro() //Fall sem útprentar upphafsskilaboð
{
    cout << endl;
    cout << "It is recommended to extend the console when using this program" << endl;
    cout << endl;
    cout << "This program is designed to keep track of some details from the history of the computer. " << endl;
    cout << "The user is able to enter known persons from the history of computer science into the database." << endl;
    cout << "The user can update the database by removing from or add to the database." << endl;
    cout << "The program can display a list of the numbers that have been entered into the database." << endl;
    cout << "The user is able to add computers from the history of computer science into the database." << endl;
    cout << "The program can display a list of items that have been entered into the database." << endl;
    cout << "The program can sort a list by the user's preferences" << endl;
    cout << "It is possible for the user to perform a search of a specific persons or computers in the database." << endl << endl;
    for (int i = 0; i < 54*2; ++i)
    {
        cout << "=";
    }
    cout << endl;
    cout << endl;
}

void ConsoleUI::subIntro() //Fall sem útprentar leiðbeiningar
{
    cout << endl << "This database contains two categories, computers and scientists. " << endl
         << "Please feel free to make changes to update the database." << endl
         << "To help us make it bigger and better." << endl;
    cout << endl;
    cout <<"You are limited to the commands from the command list above." << endl
         << "You can always type 'help' if you do not remember the commands. ";
    cout << endl;    cout << endl;
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
    cout << "ID" << "\t" << "Name" << "\t\t\t" << "build Year";
    cout << "\t\t" << "Brand" << "\t\t\t" << "Constructed" << endl;
    for (int i = 0; i < 46*2; ++i)
    {
        cout << "=";
    }
    cout << endl;

    for (size_t i = 0; i < pc.size(); ++i) //Prentar út listann miðað við lengd nafns svo það passi sem best
        {
            if(pc[i].getName().length() > 16)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t" << pc[i].getBuildy()
                                         << "\t\t\t" << pc[i].getBrand() << "\t\t" << pc[i].getConstr();
            }
            else if(pc[i].getName().length() < 16 && pc[i].getName().length() > 7)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t\t" << pc[i].getBuildy()
                                         << "\t\t\t" << pc[i].getBrand() << "\t\t" << pc[i].getConstr();
            }
            else if(pc[i].getName().length() <= 7)
            {
                qDebug().noquote().nospace() << i+1 << "\t" << pc[i].getName() << "\t\t\t" << pc[i].getBuildy()
                                         << "\t\t\t" << pc[i].getBrand() << "\t\t" << pc[i].getConstr();
            }
       }
}

void ConsoleUI::sortComputers()
{
    cout << "Please set your prefernces of displaying the list" << endl;
    cout << endl;
    cout << "Type '1' to display a list sorted in alphabetical order" << endl;
    cout << "Type '2' to display a list sorted by build year" << endl;
    cout << "Type '3' to display a list sorted by brand" << endl;
    cout << "Type '4' to display a list sorted by constructor" << endl;
    cout << endl;
    cout << "Enter a number to continue: ";

    int choice = checkInput(0,5);

    if(choice == 1)
    {
        displayChoice();
        int number = checkInput(0,3);


        if(number == 1)
        {
            string ASC = "ASC";
            string name = "name";
            vector <computers> pf = _service.sortComputers(name,ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string name = "name";
            vector <computers> pf = _service.sortComputers(name,DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 2)
    {
        displayChoice();
        int number = checkInput(0,3);

        if(number == 1)
        {
            string ASC = "ASC";
            string buildY = "buildy";
            vector <computers> pf = _service.sortComputers(buildY,ASC);
            displayComputers(pf);

        }
        if(number == 2)
        {
            string DESC = "DESC";
            string buildY = "buildy";
            vector <computers> pf = _service.sortComputers(buildY,DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 3)
    {
        displayChoice();
        int number = checkInput(0,3);

        if(number == 1)
        {
            string ASC = "ASC";
            string brand = "type";
            vector <computers> pf = _service.sortComputers(brand,ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string brand = "type";
            vector <computers> pf = _service.sortComputers(brand,DESC);
            displayComputers(pf);
        }
    }
    else if(choice == 4)
    {
        displayChoice();
        int number = checkInput(0,3);

        if(number == 1)
        {
            string ASC = "ASC";
            string constr = "constr";
            vector <computers> pf = _service.sortComputers(constr,ASC);
            displayComputers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string constr = "constr";
            vector <computers> pf = _service.sortComputers(constr,DESC);
            displayComputers(pf);
        }
    }

}

void ConsoleUI::sortScientists()
{
    cout << "Please set your prefernces of displaying the list" << endl;
    cout << endl;
    cout << "Type '1' to display a list sorted in alphabetical order" << endl;
    cout << "Type '2' to display a list sorted by gender" << endl;
    cout << "Type '3' to display a list sorted by birth Year" << endl;
    cout << "Type '4' to display a list sorted by death Year" << endl;
    cout << "Type '5' to display a list sorted by nation" << endl << endl;
    cout << "Enter a number to continue: ";
    int choice = checkInput(0,6);

    if(choice == 1)
    {
        displayChoice();
        int number = checkInput(0,3);

        if(number == 1)
        {
            string ASC = "ASC";
            string name = "name";
            vector<Performer> pf = _service.sortScientists(name, ASC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string name = "name";
            vector<Performer> pf = _service.sortScientists(name, DESC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 2)
    {
        displayChoice();
        int number = checkInput(0,3);

        if(number == 1)
        {
            string ASC = "ASC";
            string gender = "gender";
            vector<Performer> pf = _service.sortScientists(gender, ASC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string gender = "gender";
            vector<Performer> pf = _service.sortScientists(gender, DESC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 3)
    {
        displayChoice();
        int number = checkInput(0,3);
        if(number == 1)
        {
            string ASC = "ASC";
            string bYear = "byear";
            vector<Performer> pf = _service.sortScientists(bYear, ASC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string bYear = "byear";
            vector<Performer> pf = _service.sortScientists(bYear, DESC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 4)
    {
        displayChoice();
        int number = checkInput(0,3);
        if(number == 1)
        {
            string ASC = "ASC";
            string dYear = "dyear";
            vector<Performer> pf = _service.sortScientists(dYear, ASC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string dYear = "dyear";
            vector<Performer> pf = _service.sortScientists(dYear, DESC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
    }
    else if(choice == 5)
    {
        displayChoice();
        int number = checkInput(0,3);
        if(number == 1)
        {
            string ASC = "ASC";
            string nation = "nation";
            vector<Performer> pf = _service.sortScientists(nation, ASC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string nation = "nation";
            vector<Performer> pf = _service.sortScientists(nation, DESC);
            displayTopInfo();
            displayListOfPerformers(pf);
        }
    }
}

void ConsoleUI::displayChoice()
{
    cout << "Please set your prefernces of displaying the list" << endl;
    cout << endl;
    cout << "Type '1' for ascending list." << endl;
    cout << "Type '2' for descending list." << endl << endl;
    cout << "Enter a number to continue: ";
}

void ConsoleUI::displayJoin()
{
    cout << "Please set your prefernces of displaying the list" << endl;
    cout << endl;
    cout << "choose '1' to see connection from a Scientist to Computers." << endl;
    cout << "choose '2' to see connection from a Computer to Scientists" << endl;
    cout << "choose '3' to see all connections" << endl << endl;
    cout << "Enter a number:";

    int number = checkInput(0,4);
    if(number == 1)
    {
        vector<RelationsTable2> S = _service.viewScientist(1);
        int counter = 1;
        tableLook(counter);
        string sId = "S.id";
        int id;
        cout << endl << endl;
        cout << "--- Please enter a ID of a Scientist to see connection with computers ---" << endl;
        cout << endl << "Enter Scientist ID: ";
        id = checkID(S);
        cout << endl;
        vector<Relations> pf = _service.startJoin(sId, id);
        if(pf.size() == 0)
        {
            cout << "no computer listed to this scientist!" << endl;
        }

        else
        {
            tableLook2(pf);
        }
    }
    else if(number == 2)
    {
        vector<RelationsTable2> C = _service.viewScientist(2);
        int counter = 2;
        tableLook(counter);
        string cId = "C.id";
        int id;
        cout << endl << endl;
        cout << "--- Please enter a ID of a Computer to see connection with Scientists ---" << endl;
        cout << endl << "Enter Computer ID: ";
        id = checkID(C);

        vector<RelationsTable2> S = _service.viewScientist(counter);
        if(id > static_cast<int>(S.size()) || id < 0)
        {
            cout << "Invalid input, please try again: ";
        }

        cout << endl;
        vector<Relations> pf = _service.startJoin(cId, id);
        if(pf.size() == 0)
        {
            cout << "Computer has no creator!" << endl;
        }
        else
        {
            tableLook2(pf);
        }

    }
    else if(number == 3)
    {
        tableLook3();
    }
}

void ConsoleUI::addJoin()
{
    vector<RelationsTable2> S = _service.viewScientist(1);
    vector<RelationsTable2> C = _service.viewScientist(2);
    int sId;
    int cId;
    cout << endl;
    cout << "--- Please choose the ID of a Scientist and a Computer to join them ---";
    cout << endl << endl;
    cout << "Enter ID of scientist: ";
    sId = checkID(S);
    cout << "Enter ID of computer: ";
    cId = checkID(C);
    _service.addRelations(sId, cId);
}
void ConsoleUI::removeJoin()
{
    tableLook3();
    vector<RelationsID> R = _service.viewJoin();
    int id;
    cout << endl << "Enter ID of a connection to remove from the database: ";
    id = checkRID(R);
    _service.removeJoin(id);
}

void ConsoleUI::displayTable()
{
    vector<RelationsTable> pf = _service.readData();
    cout << "ID\t\t\tNAME\t\t\t\tID\t\t\tNAME" << endl;
    for(int i = 0; i < 52 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
    for(size_t i = 0; i < pf.size(); i++)
    {
        if(pf[i].getSName().length() > 16)
        {
            qDebug().noquote().nospace() << pf[i].getSId() << "\t\t\t" << pf[i].getSName()  << "\t\t" << pf[i].getCId() << "\t\t\t" << pf[i].getCName();
        }
        else if(pf[i].getSName().length() < 16 && pf[i].getSName().length() > 7)
        {
            qDebug().noquote().nospace() << pf[i].getSId() << "\t\t\t" << pf[i].getSName()  << "\t\t\t" << pf[i].getCId() << "\t\t\t" << pf[i].getCName();
        }
        else if(pf[i].getSName().length() <= 7)
        {
            qDebug().noquote().nospace() << pf[i].getSId() << "\t\t\t" << pf[i].getSName()  << "\t\t\t\t" << pf[i].getCId() << "\t\t\t" << pf[i].getCName();
        }
    }
}

int ConsoleUI::checkInput(int val1, int val2)
{
    bool found = false;
    int value;

    do {
        string choice;
        getline(cin, choice);
        value = atoi(choice.c_str());

        if(choice.length() != 1)
        {
            cout << "Invalid input, please try again: ";
        }

        else if(value > val1 && value < val2)
        {
            found = true;
        }
        else {
            cout << "Invalid input, please try again: ";
        }

    } while (!found);

        return value;
}

int ConsoleUI::checkID(vector<RelationsTable2> info)
{
    //cin.ignore();
    bool found = false;
    bool found2 = false;
    int value;

    do {
        string choice;
        getline(cin, choice);
        value = atoi(choice.c_str());

        for(size_t i = 0; i < info.size(); i++)
        {
            if(info[i].getSId() == value)
            {
                found = true;
                found2 = true;
            }
        }

        if(choice.length() > 2)
        {
            cout << "Invalid input, please try again: ";
        }
        else if(!found2) {

            cout << "Invalid input, please try again: ";
        }


    } while (!found);

        return value;
}

int ConsoleUI::checkRID(vector<RelationsID> info)
{
    bool found = false;
    bool found2 = false;
    int value;

    do {
        string choice;
        getline(cin, choice);
        value = atoi(choice.c_str());

        for(size_t i = 0; i < info.size(); i++)
        {
            if(info[i].get_id() == value)
            {
                found = true;
                found2 = true;
            }
        }

        if(choice.length() > 2)
        {
            cout << "Invalid input, please try again: ";
        }
        else if(!found2) {

            cout << "Invalid input, please try again: ";
        }
    } while (!found);

        return value;
}

void ConsoleUI::tableLook(int counter)
{
    vector<RelationsTable2> S = _service.viewScientist(counter);
    cout << "ID\t\tNAME" << endl;
    for(int i = 0; i < 24 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
    for(size_t i = 0; i < S.size(); i++)
    {
        qDebug().noquote().nospace() << S[i].getSId() << "\t\t" << S[i].getSName();
    }
}

void ConsoleUI::tableLook2(vector<Relations> pf)
{
    cout << "NAME\t\tTYPE" << endl;
    for(int i = 0; i < 24 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
    for(size_t i = 0; i < pf.size(); i++)
    {
        qDebug().noquote().nospace() << pf[i].getSName() << "\t\t" << pf[i].getCName();
    }
}

string ConsoleUI::inputCname()
{
    string name;
    cout << "Enter name/type of Computer: ";
    cin.ignore();
    getline(cin, name);

    if(name[0] == ' ')
    {
        cout << "Invalid input, please try again: ";
        cin.ignore();
        getline(cin, name);
    }
    return name;
}

void ConsoleUI::tableLook3()
{
    vector<RelationsID> pf = _service.viewJoin();
    cout << "ID\t\tNAME\t\t\tTYPE" << endl;
    for(int i = 0; i < 24 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
    for(size_t i = 0; i < pf.size(); i++)
    {
        if(pf[i].get_SName().length() > 16)
        {
            qDebug().noquote().nospace() << pf[i].get_id() << "\t\t" << pf[i].get_SName() << "\t" << pf[i].get_cName();
        }
        else if(pf[i].get_SName().length() < 16 && pf[i].get_SName().length() > 7)
        {
            qDebug().noquote().nospace() << pf[i].get_id() << "\t\t" << pf[i].get_SName() << "\t\t" << pf[i].get_cName();
        }
        else if(pf[i].get_SName().length() <= 7)
        {
            qDebug().noquote().nospace() << pf[i].get_id() << "\t\t" << pf[i].get_SName() << "\t\t\t" << pf[i].get_cName();
        }

    }
}

void ConsoleUI::displayTopInfo()// einfalt fall sem þarf að endurtaka oft!
{
    cout << endl;
    cout << "                      " << "---- List of all computer scientists in the system ----" << endl;
    cout << endl;
}
