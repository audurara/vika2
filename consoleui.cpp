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
    subIntro(); //Prentar leiðbeiningar
    _service.openFiles();
    string command;

    do
    {
        cout << endl << "Enter a command to continue: ";
        cin >> command;
        cout << endl;

        if (command == "list")
        {
            {
                bool found = false;
                cin.ignore();
                cout << "List Computer Scientists choose '1'" << endl << "List Computers choose '2'" << endl;
                cout << "Choice:";
                do
                {
                    string choice;
                    getline(cin, choice);
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

                        cout << "Invalid choice, try again:";
                    }
                    else
                    {
                        cout << "Invalid choice, try again:";
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
                    cout << "Invalid choice" << endl;
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
                char choice;
                cout << "Remove Computer Scientist choose '1'" << endl << "Remove Computer choose '2'" << endl;
                cout << "Choice: ";
                cin >> choice;
                if(choice == '1')
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
                else if(choice == '2')
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
                    cout << "Invalid choice!" << endl;
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

    cout << endl;
    cout << "                      " << "---- List of all computer scientists in the system ----" << endl;
    cout << endl;

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
    char choice;

    cout << "Please type '1' for scientist." << endl;
    cout << "Please type '2' for computer." << endl;
    cin >> choice;

    if(choice == '1')
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

                        int a = val;

                        if(a == 'y')
                        {
                            commandAdd();
                        }
                        else if(a == 'n')
                        {
                            cout << "You can do this later" << endl;
                        }
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
         cout << "Enter the name of the computer: ";
         cin.ignore();
         getline(cin, input);
         QString name = QString::fromStdString(input);


         vector <computers> newVector = _service.searchcomputer(name);
         if(newVector.size() == 0)
         {
             char val;

             cout << endl;
             cout << "No match found in database." << endl;
             cout << endl;
             cout << "Do you want to add " << input << " to the database?(y/n): ";
             cin >> val;

                     int a = val;

                     if(a == 'y')
                     {
                         addComputer();
                     }
                     else if(a == 'n')
                     {
                            cout << "You can do this later" << endl;
                     }
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
    getline(cin, name);

    int nameLength = name.length();

    for(int i = 0;i < nameLength;i++)
     {
        while(!isalpha(name[i]) && name[i] != ' ') //Passar að inntak fyrir nafn sé ekki tala eða tómt
               {
                   cout << "Invalid input, please try again: ";
                   //cin.ignore();
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
    cout << "list   - Choose to list all Computer Scientists or all Computers" << endl;
    cout << "add    - Choose to add a Computer Scientist or to add a Computer" << endl;
    cout << "search - Searches for a given Computer Scientist or Computer" << endl;
    cout << "delete - To delete entry from Computer Scientists or Computers" << endl;
    cout << "join   - To add, list and remove joined Computers and Computer Scientists" << endl;
    cout << "help   - Displays list of commands" << endl;
    cout << "exit   - This will close the application" << endl;
    cout << "Note that the commands are case-sensitive!" << endl << endl;

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
void ConsoleUI::addComputer()
{
    string name, buildy, brand, constr;
    cout << "Enter name of computer: ";
    cin >> name;
    cout << "Enter build year of computer: ";
    cin >> buildy;
    cout << "Enter type of computer: ";
    cin >> brand;
    cout << "was it built or not?(Yes/No): ";
    cin >> constr;
    _service.addComputer(name, buildy, brand, constr);
}

void ConsoleUI::intro() //Fall sem útprentar upphafsskilaboð
{
    cout << endl;
    cout << "It is recommended to extend the console when using this program" << endl;
    cout << endl;
    cout << "This program is designed to keep track of some details on known computer scientists. " << endl;
    cout << "The user is able to enter known persons from the history of computer science into a database." << endl;
    cout << "The user can remove persons from the database." << endl;
    cout << "The program can display a list of the numbers that have been entered into the database." << endl;
    cout << "The user is able to enter known numbers from the history of computer science into a database." << endl;
    cout << "The program can display a list of the persons that have been entered into the database." << endl;
    cout << "The program can sort a list by the user's preferences" << endl;
    cout << "It is possible for the user to perform a search of a specific person from the list." << endl << endl;
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
         << "You can either search for any particular computer or some specific scientist" << endl;
    cout << "from computer history. Please feel free to make changes to update the database" << endl;
    cout << endl;
    cout << "Type 'search' to perform a thorough search of the database" << endl
         << "Type 'list' to display a complete list by categories in the database." << endl
         << "You are limited to the commands in the command list above"
         << "You can always type 'help' if you do not remember the commands ";
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
    displayTopComputers();

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
void ConsoleUI::displayTopComputers()
{
    cout << "ID" << "\t" << "Name" << "\t\t\t" << "build Year";
    cout << "\t\t" << "Brand" << "\t\t\t" << "Constructed" << endl;
    for (int i = 0; i < 46*2; ++i)
    {
        cout << "=";
    }
    cout << endl;
}
void ConsoleUI::sortComputers()
{
    cout << "Choose '1' to display a list sorted in alphabetical order" << endl;
    cout << "Choose '2' to display a list sorted by build year" << endl;
    cout << "Choose '3' to display a list sorted by brand" << endl;
    cout << "Choose '4' to display a list sorted by constructor" << endl;
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
        displayChoice();
        int number = checkInput(0,3);

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
        displayChoice();
        int number = checkInput(0,3);

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
        displayChoice();
        int number = checkInput(0,3);

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

    cout << "Choose '1' to display a list sorted in alphabetical order" << endl;
    cout << "Choose '2' to display a list sorted by gender" << endl;
    cout << "Choose '3' to display a list sorted by birth Year" << endl;
    cout << "Choose '4' to display a list sorted by death Year" << endl;
    cout << "Choose '5' to display a list sorted by nation" << endl;
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
            vector<Performer> pf = _data.sortScientists(name, ASC);
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string name = "name";
            vector<Performer> pf = _data.sortScientists(name, DESC);
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
            vector<Performer> pf = _data.sortScientists(gender, ASC);
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string gender = "gender";
            vector<Performer> pf = _data.sortScientists(gender, DESC);
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
            vector<Performer> pf = _data.sortScientists(bYear, ASC);
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string bYear = "byear";
            vector<Performer> pf = _data.sortScientists(bYear, DESC);
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
            vector<Performer> pf = _data.sortScientists(dYear, ASC);
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string dYear = "dyear";
            vector<Performer> pf = _data.sortScientists(dYear, DESC);
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
            vector<Performer> pf = _data.sortScientists(nation, ASC);
            displayListOfPerformers(pf);
        }
        if(number == 2)
        {
            string DESC = "DESC";
            string nation = "nation";
            vector<Performer> pf = _data.sortScientists(nation, DESC);
            displayListOfPerformers(pf);
        }
    }
}
void ConsoleUI::displayChoice()
{
    cout << "Choose '1' for ascending list." << endl;
    cout << "Choose '2' for descending list." << endl;
    cout << "Enter a number to continue: ";
}

void ConsoleUI::displayJoin()
{

    cout << "choose '1' to see connection from a Scientist to Computers." << endl;
    cout << "choose '2' to see connection from a Computer to Scientists" << endl << endl;
    cout << "Enter a number:";

    int number = checkInput(0,3);
    if(number == 1)
    {

        int counter = 1;
        tableLook(counter);
        string sId = "S.id";
        int id;
        cout << endl << endl;
        cout << "--- Please enter a ID of a Scientist to see connection with computers ---" << endl;
        cout << endl << "Enter Scientist ID: ";
        cin >> id;
        cout << endl;
        vector<Relations> pf = _service.startJoin(sId, id);
        if(pf.size() == 0)
        {
            cout << "no computer listed to this scientist!" << endl;
        }

        else
        {
            tableLook2();
            for(size_t i = 0; i < pf.size(); i++)
            {
                qDebug().noquote().nospace() << pf[i].getSName() << "\t\t" << pf[i].getCName();
            }
        }


    }
    else if(number == 2)
    {
        int counter = 2;
        tableLook(counter);
        string cId = "C.id";
        int id;
        cout << endl << endl;
        cout << "--- Please enter a ID of a Computer to see connection with Scientists ---" << endl;
        cout << endl << "Enter Computer ID: ";
        cin >> id;



        vector<RelationsTable2> S = _service.viewScientist(counter);
        if(id > static_cast<int>(S.size()) || id < 0)
        {
            cout << "Invalid ";
        }

        cout << endl;
        vector<Relations> pf = _service.startJoin(cId, id);
        if(pf.size() == 0)
        {
            cout << "Computer has no creator!" << endl;
        }
        else
        {
            tableLook2();
            for(size_t i = 0; i < pf.size(); i++)
            {
                qDebug().noquote().nospace() << pf[i].getSName() << "\t\t" << pf[i].getCName();
            }
        }

    }
}
void ConsoleUI::addJoin()
{
    int sId;
    int cId;
    cout << endl;
    cout << "--- Please choose the ID of a Scientist and a Computer to join them ---";
    cout << endl << endl;
    cout << "Enter ID of scientist: ";
    cin >> sId;
    cout << "Enter ID of computer: ";
    cin >> cId;
    _service.addRelations(sId, cId);
}
void ConsoleUI::removeJoin()
{
    vector<RelationsID> pf = _data.viewJoin();
    tableLook3();
    for(size_t i = 0; i < pf.size(); i++)
    {
        qDebug().noquote().nospace() << pf[i].get_id() << "\t\t" << pf[i].get_SName() << "\t\t" << pf[i].get_cName();
    }
    int id;
    cout << endl << "Enter ID of a connection to remove from the database: ";
    cin >> id;
    _data.removeJoin(id);


}

void ConsoleUI::displayTable()
{
    vector<RelationsTable> pf = _data.readData();

    cout << "ID\t\t\tNAME\t\t\t\tID\t\t\tNAME" << endl;
    for(int i = 0; i < 52 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
    for(size_t i = 0; i < pf.size(); i++)
    {
        qDebug().noquote().nospace() << pf[i].getSId() << "\t\t\t" << pf[i].getSName()  << "\t\t\t" << pf[i].getCId() << "\t\t\t" << pf[i].getCName();
    }
}
int ConsoleUI::checkInput(int val1, int val2)
{
    //cin.ignore();
    bool found = false;
    int value;


    do {
        string choice;
        getline(cin, choice);
        value = atoi(choice.c_str());

        if(choice.length() != 1)
        {
            cout << "Invalid input, try again:";
        }

        else if(value > val1 && value < val2)
        {
            found = true;
        }
        else {
            cout << "Invalid, try again:";
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
void ConsoleUI::tableLook2()
{
    cout << "NAME\t\tTYPE" << endl;
    for(int i = 0; i < 24 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
}
void ConsoleUI::tableLook3()
{
    cout << "ID\t\tNAME\t\t\tTYPE" << endl;
    for(int i = 0; i < 24 * 2; i++)
    {
        cout << "=";
    }
    cout << endl;
}
