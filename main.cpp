#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<sstream>
#include<vector>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int gcd(int a, int h)
{
    int temp;
    while (1) {
        temp = a % h;
        if (temp == 0)
            return h;
        a = h;
        h = temp;
    }
}

string RSA(string message) {
    double p = 17;
    double q = 19;

    string encryptedMessage;

    double n = p * q;

    double e = 2;
    double phi = (p - 1) * (q - 1);
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        else
            e++;
    }

    for(int i = 0; i < message.length(); i++) {

        double msg = static_cast<double>(message[i]);

        double c = pow(msg, e);
        c = fmod(c, n);

        char encryptedLetter = static_cast<char>(c);

        encryptedMessage.push_back(encryptedLetter);
    }

    return encryptedMessage;
}

bool isValidCity(string dep)
{
    bool found=false;
    ifstream cities;
    cities.open("orase.txt");
    string city;
    while(getline(cities,city))
    {
        if(!city.compare(dep))
            found=true;
    }
return found;
}

bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool isValidDate(int day, int month, int year) {
    if (year < 2024 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    return (day <= daysInMonth[month]);
}

bool isValidTime(int hour, int minute) {
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
}

bool isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool isValid(string email)
{
    if (!isChar(email[0])) {
        return 0;
    }
    int At = -1, Dot = -1;
    for (int i = 0;
         i < email.length(); i++) {

        if (email[i] == '@') {

            At = i;
        }

        else if (email[i] == '.') {

            Dot = i;
        }
    }

    if (At == -1 || Dot == -1)
        return 0;

    if (At > Dot)
        return 0;
    return !(Dot >= (email.length() - 1));
}

bool isStrongPassword(const string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
        } else if (islower(c)) {
            hasLowercase = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (ispunct(c) || c == ' ') {
            hasSpecialChar = true;
        }
    }

    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

class Bus
{
public:
string Bus_number;
string departure;
string destination;
string day,year,month,hour,minutes;
string seats;

void addBus()
{
    string Bus_number;
    string departure;
    string destination;
    int day,month,year,seats,minutes,hour;
    cout<<"Enter the Bus Number: "<<endl;
    cin>>Bus_number;
    bool dep=false,dest=false;
    cout<<"Please enter the departure city: ";
    while(dep==false)
    {
        cin>>departure;
        try
        {
           if (isValidCity(departure)==false)
           throw dep;
           dep=true;
        }

        catch(bool e)
        {
            cout<<"Departure city doesn't exist "<<endl;
            cout<<"Please enter an existing city "<<endl;
        }
    }

    cout<<"Please enter the destination city: ";
        while(dest==false)
    {
        cin>>destination;
        try
        {
           if (isValidCity(destination)==false)
           throw dest;
           dest=true;
        }

        catch(bool e)
        {
            cout<<"Destination city doesn't exist "<<endl;
            cout<<"Please enter an existing city "<<endl;
        }
    }

    cout<<"Please enter the date for the bus"<<endl;
    bool valid_date=false;
    while(valid_date==false)
    {
    cout<<"Enter the day: ";
    cin>>day;
    cout<<"Enter the month: ";
    cin>>month;
    cout<<"Enter the year(>=2024): ";
    cin>>year;
        try
        {
            if(isValidDate(day,month,year)==false)
                throw(valid_date);
                valid_date=true;
        }
        catch(bool e)
        {
            cout<<"please enter a valid date"<<endl;
        }
    }
    bool valid_time=false;
    cout<<"Please enter the time for the departure"<<endl;
    while(valid_time==false)
    {
        cout<<"Enter the hour: ";
        cin>>hour;
        cout<<"Enter the minutes: ";
        cin>>minutes;
        try
        {
            if(isValidTime(hour,minutes)==false)
                throw(valid_time);
                valid_time=true;

        }
    catch(bool e)
    {
        cout<<"Please enter a valid time"<<endl;
    }
    }
cout<<"enter the no of seats: ";
cin>>seats;
while(seats<1)
{
    cout<<"invalid no of seats. Please enter a valid number: ";
    cin>>seats;
}
 ofstream busoutput;
ifstream businput;
businput.open ("buses.csv");
busoutput.open ("buses.csv",ios::app);

    if(businput.is_open())
        busoutput<<Bus_number<<','<<departure<<','<<destination<<','<<day<<','<<month<<','<<year<<','<<hour<<','<<minutes<<','<<seats<<endl;
        cout<<"Bus has been added\n";

    businput.close();
    busoutput.close();
}

void removeBus()
{
    string busNumber;
    cout<<"Please enter the number of the bus you want to remove: ";
    cin>>busNumber;

    string busId, line;
    bool busFound = false;
    ifstream buses;
    ofstream temp;

    temp.open("temp.csv");
    buses.open("buses.csv");
    while(getline(buses, busId, ',')) {
        getline(buses, line);
        if(busId.compare(busNumber)) {
            temp<<busId<<','<<line<<endl;
                }
        else {
            busFound = true;
                }
            }

    temp.close();
    buses.close();
    remove("buses.csv");
    rename("temp.csv","buses.csv");

    if(busFound) {
        cout<<busNumber<<" bus has been removed\n";
            }
    else {
        cout<<busNumber<<" bus not found. Try again!\n\n";
        removeBus();
            }
}
int searchBus(vector<Bus> &availableBuses) {

int k = 0;
cout<<"Departure: ";
cin>>departure;
cout<<"Destination: ";
cin>>destination;
string depart, dest, busId, d, m, y, h, mi,s;
bool destFound = false, depFound = false;

ifstream buses;
buses.open("buses.csv");

    while(getline(buses, busId, ',')) {
    getline(buses, depart, ',');
    getline(buses, dest, ',');
    getline(buses, d, ',');
    getline(buses, m, ',');
    getline(buses, y, ',');
    getline(buses, h, ',');
    getline(buses, mi,',');
    getline(buses,s);
    if(!departure.compare(depart) && !destination.compare(dest)) {
        depFound = true;
        destFound = true;

        availableBuses[k].Bus_number = busId;
        availableBuses[k].departure = depart;
        availableBuses[k].destination = dest;
        availableBuses[k].day =d;
        availableBuses[k].month = m;
        availableBuses[k].year = y;
        availableBuses[k].hour = h;
        availableBuses[k].minutes =  mi;
        availableBuses[k].seats=s;

    cout<<"\nOption: "<<k+1;
    cout<<"\nBus number: " <<busId <<endl;
    cout<<"From: " <<departure <<"\nTo: " <<destination <<endl;
    cout<<"Date: " <<d <<'/'<<m<<'/'<<y<<' '<<h<<':'<<mi<<endl;
    cout<<"No of seats "<<s<<endl;

    k++;
                }
            }
            if(!depFound || !destFound) {

                cout<<"No Buses from " <<departure <<" to " <<destination <<". Try another route!\n\n";
                availableBuses.clear();
                return searchBus(availableBuses);
            }

            return k;
        }
};

class Operator {
public:
    string username, password;
    void login() {
        cout << "Username: ";
        cin >> username;
        ifstream operators("operators.csv");
        if (!operators.is_open()) {
            throw runtime_error("Error opening operators.csv");
        }
        string user, pass;
        bool opFound = false;

        while (getline(operators, user, ',')) {
            getline(operators, pass);
            if (!user.compare(username)) {
                opFound = true;
                cout << "Password: ";
                cin >> password;
                if (!pass.compare(password)) {
                    cout << "Login was successful!\n\n";
                    return;
                } else {
                    throw invalid_argument("Incorrect password!");
                }
            }
        }

        if (!opFound) {
            throw invalid_argument("Username not found!");
        }
    }

void removeBusParameters(string busNumber)
{


    string busId, line;
    bool busFound = false;
    ifstream buses;
    ofstream temp;

    temp.open("temp.csv");
    buses.open("buses.csv");
    while(getline(buses, busId, ',')) {
        getline(buses, line);
        if(busId.compare(busNumber)) {
            temp<<busId<<','<<line<<endl;
                }
        else {
            busFound = true;
                }
            }

    temp.close();
    buses.close();
    remove("buses.csv");
    rename("temp.csv","buses.csv");

}

void addBusNewSeats(const Bus&  B, string newSeats)
{


 ofstream busoutput;
ifstream businput;
businput.open ("buses.csv");
busoutput.open ("buses.csv",ios::app);

    if(businput.is_open())
        busoutput<<B.Bus_number<<','<<B.departure<<','<<B.destination<<','<<B.day<<','<<B.month<<','<<B.year<<','<<B.hour<<','<<B.minutes<<','<<newSeats<<endl;

    businput.close();
    busoutput.close();
}

};

class User
{public:
    string email,password;

void signUp() {
    string line, pass, em, passConfirm;
    bool userFound = false;

     try {

        ifstream userinput("users.csv");
        ofstream useroutput("users.csv", ios::app);

        if (!useroutput.is_open() || !userinput.is_open()) {
            throw runtime_error("Error opening user file.");
        }

        cout << "Enter username (email): ";
        cin >> email;
        bool valid_email=isValid(email);

        while(valid_email==false) {
            cout<<"Invalid email format. Enter email: ";
            cin>>email;
            valid_email=isValid(email);
        }

        while (getline(userinput, em, ',')) {
            getline(userinput, password);
            if (!em.compare(email)) {
                userFound = true;
                cout << "Existing email. Try another one!\nEnter email: ";
                cin >> email;
                userinput.clear();
                userinput.seekg(0, ios::beg);
            }
        }

        cout << "Enter password: ";
        cin >> password;
        while (!isStrongPassword(password)) {
            cout << "Weak password. Password must be at least 8 characters long and contain an uppercase letter, a lowercase letter, a digit and a special character.\n";
            cout << "Enter password: ";
            cin >> password;
        }
        cout << "Confirm password: ";
        cin >> passConfirm;

        while (password != passConfirm) {
            cout << "\nPasswords don't match.\n";
            cout << "\nEnter password: ";
            cin >> password;
            cout << "Confirm password: ";
            cin >> passConfirm;
        }

        if (useroutput.is_open())
            useroutput<<email<<','<< RSA(password) << endl;

        cout << "Sign up complete!\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
void login() {
        cout << "Email: ";
        cin >> email;
        ifstream users("users.csv");
        if (!users.is_open()) {
            throw runtime_error("Error opening users.csv");
        }
        string em, pass;
        bool userFound = false;

        while (getline(users, em, ',')) {
            getline(users, pass);
            if (!em.compare(email)) {
                userFound = true;
                cout << "Password: ";
                cin >> password;
                if (!pass.compare(RSA(password))) {
                    cout << "Login was successful!\n\n";
                    return;
                } else {
                    throw invalid_argument("Incorrect password!");
                }
            }
        }

        if (!userFound) {
            throw invalid_argument("Email not found!");
        }
    }




void reservation(string em) {
    string email = em;
    vector<Bus> buses(100);
    string busId,line;
    Bus bus,b;
    int n;
    int choice;

    n = bus.searchBus(buses);
    bool ok = false;
    while(!ok) {

        cout<<"\nChoose your bus\n";
        cin>>choice;
        choice--;
        if(choice > n-1||stoi(buses[choice].seats)==0) {

            cout<<choice+1 <<" is not a valid choice. Please select again!\n";
                }
        else {
            Operator op;
            b = buses[choice];
            string newSeats;
            int newSeatsInt = stoi(b.seats);
            newSeats =  to_string(newSeatsInt - 1);

            op.removeBusParameters(b.Bus_number);
            op.addBusNewSeats(b, newSeats);


            ofstream reservations;
            reservations.open("reservations.csv", ios::app);
            reservations<<email<<','<<buses[choice].Bus_number<<','<<buses[choice].departure<<','<<buses[choice].destination<<','<<buses[choice].day<<','<<buses[choice].month<<','<<buses[choice].year<<','<<buses[choice].hour<<','<<buses[choice].minutes<<endl;
            cout<<"Reservation was successful!\n\n";
            ok = true;
               }
            }

}
};
void Menu();
void opMenu();
void userMenu();
void opMenuLogged();
void userMenuLogged(string);
int validateOption(int opt)
{
   int option;
   cout<<"invalid option. Please choose again: ";
   cin>>option;
   return option;
}

void opMenuLogged()
{
system("cls");
int option;
Bus bus;
Operator op;
cout<<"<--------------------------->"<<endl;
cout<<"Operator-Logged"<<endl<<endl;
cout<<"> 1.Add bus"<<endl;
cout<<"> 2.Remove bus"<<endl;
cout<<"> 3.Return to operator menu"<<endl;
cout<<"> 4.Exit"<<endl<<endl;
cout<<"---------------------------->"<<endl<<endl;
cout<<"Your option: ";
cin>>option;
while(option<1||option>4)
    option=validateOption(option);

 switch(option)
{
    case 1: bus.addBus();
            cout<<"press enter to continue";
            getch();
            opMenuLogged();
            break;
    case 2: bus.removeBus();
            cout<<"press enter to continue";
            getch();
            opMenuLogged();
            break;
    case 3: opMenu();
            break;
    case 4: cout<<"Thank you for using my application!"<<endl;
            break;
}
}

void userMenuLogged(string email)
{
system("cls");
string em=email;
int option;
Bus bus;
vector<Bus> buses(100);
User user;
cout<<"<--------------------------->"<<endl;
cout<<"User-Logged"<<endl<<endl;
cout<<"> 1.Find bus"<<endl;
cout<<"> 2.Make reservation"<<endl;
cout<<"> 3.Return to user menu"<<endl;
cout<<"> 4.Exit"<<endl<<endl;
cout<<"---------------------------->"<<endl<<endl;
cout<<"Your option: ";
cin>>option;
while(option<1||option>4)
    option=validateOption(option);

 switch(option)
{
    case 1: bus.searchBus(buses);
            cout<<"press enter to continue";
            getch();
            userMenuLogged(em);
            break;
    case 2: user.reservation(em);
            cout<<"press enter to continue";
            getch();
            userMenuLogged(em);
            break;
    case 3: userMenu();
            break;
    case 4: cout<<"Thank you for using my application!"<<endl;
            break;
}
}
void opMenu()
{
system("cls");
Operator op;
int option;
cout<<"<--------------------------->"<<endl;
cout<<"Operator"<<endl<<endl;
cout<<"> 1.Login"<<endl;
cout<<"> 2.Return to Main Menu"<<endl;
cout<<"> 3.Exit"<<endl<<endl;
cout<<"---------------------------->"<<endl<<endl;
cout<<"Your option: ";
cin>>option;
while(option<1||option>3)
    option=validateOption(option);

 switch(option)
{
    case 1:{bool opLogged=false;
            while(opLogged==false){
            try {
            op.login();
            opLogged=true;
            } catch (const exception& e) {
            cerr << "Login failed: " << e.what() << endl;
    }
}
            cout<<"press enter to continue";
            getch();
            opMenuLogged();}
            break;
    case 2: Menu();
            break;
    case 3: cout<<endl<<"Thank you for using my application!"<<endl;
            break;
}
}

void userMenu()
{
system("cls");
User user;
string email;
int option;
cout<<"<--------------------------->"<<endl;
cout<<"User"<<endl<<endl;
cout<<"> 1.Sign up"<<endl;
cout<<"> 2.Login"<<endl;
cout<<"> 3.Return to Main Menu"<<endl;
cout<<"> 4.Exit"<<endl<<endl;
cout<<"---------------------------->"<<endl<<endl;
cout<<"Your option: ";
cin>>option;
while(option<1||option>4)
    option=validateOption(option);

 switch(option)
{
    case 1: cout<<endl;
            user.signUp();
            cout<<"press enter to continue";
            getch();
            userMenu();
            break;
    case 2: {cout<<endl;
            bool userLogged=false;
            while(userLogged==false){
            try {
            user.login();
            userLogged=true;
            } catch (const exception& e) {
            cerr << "Login failed: " << e.what() << endl;
                }
            }
            email=user.email;
            cout<<"press enter to continue";
            getch();
            userMenuLogged(email);}
            break;
    case 3: cout<<endl;
            Menu();
            break;
    case 4: cout<<endl<<"Thank you for using my application!"<<endl;
            break;

}}
void Menu()
{
system("cls");
int option;
cout<<"<--------------------------------------------------------------------------------------->"<<endl;
cout<<"Welcome to my bus application! Please Select if you want to continue as an user or operator:"<<endl<<endl;
cout<<"> 1.Operator"<<endl;
cout<<"> 2.User"<<endl;
cout<<"> 3.Exit"<<endl<<endl;
cout<<"<--------------------------------------------------------------------------------------->"<<endl<<endl;
cout<<"Your option: ";
cin>>option;
while(option<1||option>3)
    option=validateOption(option);
switch(option)
{
    case 1: opMenu();
            break;
    case 2: userMenu();
            break;
    case 3: cout<<endl<<"Thank you for using my application!"<<endl;
            break;
}
}

int main()
{
Menu();

}

