#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>

using namespace std;

/** TODO:
  * ? add static? -> DONE.
  * ? getters -> DONE.
  * ? setters -> DONE.
  * ? 2 param constructors -> DONE.
  * ? copy constructor -> DONE.
  * ? operator= -> DONE
  * ? destructor -> DONE.
  * ? generic methods per class, at least 2 -> DONE.
  * ? << + >> -> DONE.
  * ? index operator [] -> DONE -> only in Order class -> only here makes sense.
  * ? minimum +,-,*,/ -> DONE.
  * ? cast explicit or implicit -> DONE.
  * ? negation ! -> DONE -> only in Wine class -> set price to minPrice.
  * ? conditional operator <, >, <=, >= -> DONE. <= + <
  * ? operator== -> DONE.
  * ? test classes -> DONE.
  * ?
  * ? Menu -> DONE.
  * ? Save app data in txt -> DONE.
  * ? Reports -> DONE.
  * ? Composition -> DONE.
  * ? Inheritance -> DONE.
*/

/**
 * ? Default behaviour:
 * ? -> makeID:
 * ?    * create a file to store last ID
 * ?    * on call:
 * ?    *   read value from id.txt file. (0 by default)
 * ?    *   increment ID by 1
 * ?    *   write ID in id.txt file.
 * ?    *   return ID
 * ?
 * ? -> application data:
 * ?    * data is stored in maps;
 * ?    * data: Wines, Employees, Clients, Orders
 * ?
 * ? -> classes with ID:
 * ?    * on default constructor generate new ID;
 * ?    * on copy -> copy ID.
*/

/**
 * ? INFO:
 * ? >> Declared here in order to use them in maps.
 * ? >> In C++ in order to use a variable, class, function etc it has to be declared before
 * ? so the compiler knows it exists.
 * ? >> We use:
 * ?    the classes in maps and
 * ?    the maps in classes.
*/
class Wine;
class Employee;
class Client;
class Order;

/**
 * ? INFO:
 * ? Application data.
*/
map<int, Wine> data_Wines;
map<int, Employee> data_Employees;
map<int, Client> data_Clients;
map<int, Order> data_Orders;

/**
 * ? INFO:
 * ? create a file to store last ID
 * ? on call:
 * ?   read value from id.txt file. (0 by default)
 * ?   increment ID by 1
 * ?   write ID in id.txt file.
 * ?   return ID
 * @return new ID
*/
int makeID() {
    ifstream f("id.txt");
    int id = 0;
    f >> id;
    f.close();

    id = id + 1;

    ofstream g("id.txt");
    g << id;
    g.close();

    return id;
}

/**
 * ? Simple struct to manage date.
*/
struct Date {
    int day;
    int month;
    int year;

    // default constructor
    Date() {
        this->day = 1;
        this->month = 1;
        this->year = 1978;
    }

    // params constructor
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    // compares 2 dates.
    bool operator<(const Date& date) const {
        if ((this->year < date.year) ||
            (this->year == date.year && this->month < date.month) ||
            (this->year == date.year && this->month == date.month && this->day < date.day))
            return true;

        return false;
    }

    /**
     * @return string formatted to output in text file.
     * ? format: dat month year
    */
    string forTextFile() const {
        string str = "" + to_string(this->day) + " " + to_string(this->month) + " " + to_string(this->year);

        return str;
    }

    /**
     * @return string formatted to output in console
     * ? format: dat/month/year
    */
    string forConsole() const {
        string str = "" + to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);

        return str;
    }

    // reads date from console.
    friend istream& operator>>(istream& in, Date& date) {
        cout << " >> day: ";
        in >> date.day;
        cout << " >> month: ";
        in >> date.month;
        cout << " >> year: ";
        in >> date.year;

        return in;
    }
};

enum class WineType {
    Red,
    White,
    Rose
};

// converts WineType to string variant.
string wineTypeToString(WineType type) {
    switch (type) {
    case WineType::Red:
        return "red";
    case WineType::White:
        return "white";
    default:
        return "rose";
    }
}

// converts string to WineType variant.
WineType stringToWineType(string type) {
    for (int i = 0; i < type.length(); i++)
        type[i] = tolower(type[i]);

    if (type == "red")
        return WineType::Red;

    if (type == "white")
        return WineType::White;

    if (type == "rose")
        return WineType::Rose;

    throw "Invalid wine type";
}

class Wine {
private:
    int id = -1;
    char* name = NULL;
    string description = "";
    WineType type = WineType::Red;
    float minPrice = -1;
    float price = -1;
    Date bottlingDate = Date();

public:
    // >> Getters.
    int getID() const {
        return this->id;
    }

    const char* getName() const {
        return this->name;
    }

    string getDescription() const {
        return this->description;
    }

    WineType getWineType() const {
        return this->type;
    }

    float getMinPrice() const {
        return this->minPrice;
    }

    float getPrice() const {
        return this->price;
    }

    Date getBottlingDate() const {
        return this->bottlingDate;
    }

    // >> Setters.
    void setName(const char* newName) {
        if (newName == NULL)
            throw "Name cannot be null";

        if (this->name != NULL) {
            delete[] this->name;
            this->name = NULL;
        }

        this->name = new char[strlen(newName) + 1];
        strcpy(this->name, newName);
    }

    void setDescription(string newDescription) {
        if (newDescription == "")
            throw "Description cannot be empty";

        this->description = newDescription;
    }

    void setMinPrice(float newMinPrice) {
        if (newMinPrice < 0)
            throw "New min price cannot be negative";

        if (newMinPrice > this->price)
            throw "New min price cannot be grater than current price";

        this->minPrice = newMinPrice;
    }

    void setPrice(float newPrice) {
        if (newPrice < 0)
            throw "New price cannot be negative";

        if (newPrice < this->minPrice)
            throw "New price cannot be less than current min price";

        this->price = newPrice;
    }

    // >> Constructors.
    Wine() {
        this->id = makeID();
        this->setName("none");
        this->setDescription("none");
        this->type = WineType::Red;
        this->minPrice = 0;
        this->price = 0;
        this->bottlingDate = Date();
    }

    Wine(const char* name, float minPrice, WineType type, Date bottlingDate) {
        this->id = makeID();
        this->description = "Unspecified";
        this->type = type;
        this->setPrice(minPrice);
        this->setMinPrice(minPrice);
        this->setName(name);
        this->bottlingDate = bottlingDate;
    }

    Wine(const char* name, float minPrice, Date bottlingDate, string description, float price, WineType type) {
        this->id = makeID();
        this->setDescription(description);
        this->type = type;
        this->setPrice(price);
        this->setMinPrice(minPrice);
        this->setName(name);
        this->bottlingDate = bottlingDate;
    }

    // >> Copy constructor.
    Wine(const Wine& wine) {
        this->id = wine.id;
        this->setDescription(wine.description);
        this->type = wine.type;
        this->setPrice(wine.price);
        this->setMinPrice(wine.minPrice);
        this->setName(wine.name);
        this->bottlingDate = wine.bottlingDate;
    }

    // >> Operator=.
    Wine& operator=(const Wine& wine) {
        if (this == &wine)
            return *this;

        this->id = wine.id;
        this->setDescription(wine.description);
        this->type = wine.type;
        this->setPrice(wine.price);
        this->setMinPrice(wine.minPrice);
        this->setName(wine.name);
        this->bottlingDate = wine.bottlingDate;

        return *this;
    }

    // >> Destructor.
    ~Wine() {
        if (this->name != NULL) {
            delete[] this->name;
            this->name = NULL;
        }
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputWine here).
     * ? We use try because user input can be invalid.
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here wine to inputWine)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, Wine& wine) {
        // try to read input.
        Wine inputWine;

        string aux;

        cout << "Enter wine name: ";
        getline(in, aux);
        inputWine.setName(aux.c_str());

        cout << "Enter wine description: ";
        getline(in, aux);
        inputWine.setDescription(aux);

        cout << "Enter wine type (red, white, rose): ";
        getline(in, aux);
        inputWine.type = stringToWineType(aux);

        float price = 0;
        cout << "Enter price: ";
        in >> price;
        inputWine.setPrice(price);

        price = 0;
        cout << "Enter minimum price: ";
        in >> price;
        inputWine.setMinPrice(price);

        cout << "Enter bottling date: \n";
        in >> inputWine.bottlingDate;

        // set input.
        wine = inputWine;
        cout << "[INFO] Wine ID: " << wine.id << '\n';

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const Wine& wine) {
        out << "ID: " << wine.id << '\n';

        out << "Name: ";
        if (wine.name != NULL)
            out << wine.name;
        out << '\n';

        out << "Description: " << wine.description << '\n';
        out << "Type: " << wineTypeToString(wine.type) << '\n';
        out << "Min Price: " << wine.minPrice << "\n";
        out << "Price: " << wine.price << '\n';
        out << "Bottling date: " << wine.bottlingDate.forConsole();

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const Wine& wine) {
        out << wine.id << '\n';

        if (wine.name != NULL)
            out << wine.name;
        out << '\n';
        out << wine.description << '\n';
        out << wineTypeToString(wine.type) << '\n';
        out << wine.minPrice << " " << wine.price << '\n';
        out << wine.bottlingDate.forTextFile();

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, Wine& wine) {
        in >> wine.id;
        in.get();

        string aux;
        getline(in, aux);
        wine.setName(aux.c_str());

        getline(in, aux);
        wine.setDescription(aux);

        getline(in, aux);
        wine.type = stringToWineType(aux);

        in >> wine.minPrice >> wine.price;

        Date date;
        in >> date.day >> date.month >> date.year;
        wine.bottlingDate = date;

        return in;
    }

    // >> Generic methods.
    bool bottledBefore(Date date) const {
        if (this->bottlingDate < date)
            return true;

        return false;
    }

    /**
     * @return difference between actual price and min price.
    */
    float getValueAdded() const {
        return this->price - this->minPrice;
    }

    // >> Operator +, -.
    /**
     * ? INFO:
     * ? add value to wine price.
    */
    Wine operator+(float price) const {
        Wine copy = *this;
        copy.price = copy.price + price;

        return copy;
    }

    /**
     * ? INFO:
     * ? subtract value from price.
    */
    Wine operator-(float price) const {
        Wine copy = *this;
        copy.price = copy.price - price;

        return copy;
    }

    // >> Cast operator.
    explicit operator string() const {
        return this->name;
    }

    operator WineType() const {
        return this->type;
    }

    // >> Operator !.
    /**
     * ? INFO:
     * ? Sets price to minPrice. (resets price back to minimum)
    */
    Wine& operator! () {
        this->price = this->minPrice;

        return *this;
    }

    // >> Operator <=, <.
    bool operator<=(const Wine& wine) const {
        if (this->price <= wine.price)
            return true;
        return false;
    }

    bool operator<=(float price) const {
        if (this->price <= price)
            return true;
        return false;
    }

    bool operator<(const Wine& wine) const {
        if (this->price < wine.price)
            return true;
        return false;
    }

    bool operator<(float price) const {
        if (this->price < price)
            return true;
        return false;
    }

    // >> Operator==.
    /**
     * ? compares by id
     * @return boolean -> true if wines are equale, false otherwise
    */
    bool operator==(const Wine& wine) const {
        if (this->id == wine.id)
            return true;
        return false;
    }

    /**
     * @return negated operator==
    */
    bool operator!=(const Wine& wine) const {
        return !this->operator==(wine);
    }
};

enum class Gender {
    Male, Female, Other
};

// convert Gender to string variant.
string genderToString(Gender gender) {
    switch (gender) {
    case Gender::Male:
        return "male";
    case Gender::Female:
        return "female";
    default:
        return "other";
    }
}

// convert string to Gender variant.
Gender stringToGender(string gender) {
    for (int i = 0; i < gender.length(); i++)
        gender[i] = tolower(gender[i]);

    if (gender == "male")
        return Gender::Male;

    if (gender == "female")
        return Gender::Female;

    if (gender == "other")
        return Gender::Other;

    throw "Unknwon gender";
}

class Person {
private:
    int id = -1;
    char* firstName = NULL;
    char* lastName = NULL;
    string email = "";
    string phone = "";
    Gender gender = Gender::Other;
    Date birthDate = Date();

public:
    // >> Getters.
    int getID() const {
        return this->id;
    }

    const char* getFirstName() const {
        return this->firstName;
    }

    const char* getLastName() const {
        return this->lastName;
    }

    string getEmail() const {
        return this->email;
    }

    string getPhone() const {
        return this->phone;
    }

    Gender getGender() const {
        return this->gender;
    }

    Date getBirthDate() const {
        return this->birthDate;
    }

    // >> Setters.
    void setFirstName(const char* newFirstName) {
        if (newFirstName == NULL)
            throw "First name cannot be null";

        if (this->firstName != NULL) {
            delete[] this->firstName;
            this->firstName = NULL;
        }

        this->firstName = new char[strlen(newFirstName) + 1];
        strcpy(this->firstName, newFirstName);
    }

    void setLastName(const char* newLastName) {
        if (newLastName == NULL)
            throw "Last name cannot be null";

        if (this->lastName != NULL) {
            delete[] this->lastName;
            this->lastName = NULL;
        }

        this->lastName = new char[strlen(newLastName) + 1];
        strcpy(this->lastName, newLastName);
    }

    void setEmail(string newEmail) {
        if (newEmail == "")
            throw "Email cannot be empty";

        this->email = newEmail;
    }

    void setPhone(string newPhone) {
        if (newPhone.length() != 10)
            throw "Invalid phone number";

        this->phone = newPhone;
    }

    // >> Constructors.
    Person() {
        this->id = makeID();
        this->setFirstName("none");
        this->setLastName("none");
        this->email = "none";
        this->phone = "none";
        this->gender = Gender::Other;
        this->birthDate = Date();
    }

    Person(const char* firstName, const char* lastName, string email, string phone, Gender gender, Date birthDate) {
        this->id = makeID();
        this->setFirstName(firstName);
        this->setLastName(lastName);
        this->setEmail(email);
        this->setPhone(phone);
        this->gender = gender;
        this->birthDate = birthDate;
    }

    // >> Copy constructor.
    Person(const Person& person) {
        this->id = person.id;
        this->setFirstName(person.firstName);
        this->setLastName(person.lastName);
        this->setEmail(person.email);
        this->setPhone(person.phone);
        this->gender = person.gender;
        this->birthDate = person.birthDate;
    }

    // >> Operator=.
    Person& operator=(const Person& person) {
        if (this == &person)
            return *this;

        this->id = person.id;
        this->setFirstName(person.firstName);
        this->setLastName(person.lastName);
        this->setEmail(person.email);
        this->setPhone(person.phone);
        this->gender = person.gender;
        this->birthDate = person.birthDate;

        return *this;
    }

    // >> Destructor.
    ~Person() {
        if (this->firstName != NULL) {
            delete[] this->firstName;
            this->firstName = NULL;
        }

        if (this->lastName != NULL) {
            delete[] this->lastName;
            this->lastName = NULL;
        }
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputPerson here).
     * ? We use try because user input can be invalid.
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here person to inputPerson)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, Person& person) {
        // try to read input.
        Person inputPerson;

        string aux;

        cout << "Enter first name: ";
        getline(in, aux);
        inputPerson.setFirstName(aux.c_str());

        cout << "Enter last name: ";
        getline(in, aux);
        inputPerson.setLastName(aux.c_str());

        cout << "Enter email: ";
        getline(in, aux);
        inputPerson.setEmail(aux);

        cout << "Enter phone (10 digits): ";
        getline(in, aux);
        inputPerson.setPhone(aux);

        cout << "Enter gender (male, female, other): ";
        getline(in, aux);
        inputPerson.gender = stringToGender(aux);

        cout << "Enter birth date: " << '\n';
        in >> inputPerson.birthDate;

        // set input.
        person = inputPerson;
        cout << "[INFO] Person ID: " << person.id << '\n';

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const Person& person) {
        out << "ID: " << person.id << '\n';
        out << "First name: " << person.firstName << '\n';
        out << "Last name: " << person.lastName << '\n';
        out << "Email: " << person.email << '\n';
        out << "Phone: " << person.phone << '\n';
        out << "Gender: " << genderToString(person.gender) << '\n';
        out << "Birth date: " << person.birthDate.forConsole();

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const Person& person) {
        out << person.id << '\n';
        out << person.firstName << '\n';
        out << person.lastName << '\n';
        out << person.email << '\n';
        out << person.phone << '\n';
        out << genderToString(person.gender) << '\n';
        out << person.birthDate.forTextFile();

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, Person& person) {
        in >> person.id;
        in.get();

        string aux;
        getline(in, aux);
        person.setFirstName(aux.c_str());

        getline(in, aux);
        person.setLastName(aux.c_str());

        getline(in, aux);
        person.email = aux;

        getline(in, aux);
        person.phone = aux;

        getline(in, aux);
        person.gender = stringToGender(aux);

        in >> person.birthDate.day >> person.birthDate.month >> person.birthDate.year;

        return in;
    }

    // >> Generic methods.
    /**
     * @return lastName + " " + firstName
    */
    string getFullName() const {
        string fullName = this->lastName;
        fullName += " ";
        fullName += this->firstName;

        return fullName;
    }

    bool bornBefore(const Date& date) const {
        if (this->birthDate < date)
            return true;

        return false;
    }

    // >> Cast operator.
    explicit operator string() const {
        return this->getFullName();
    }

    // >> Operator <=, <.
    bool operator<=(const Person& person) {
        if (this->id <= person.id)
            return true;
        return false;
    }

    bool operator<(const Person& person) {
        if (this->id < person.id)
            return true;
        return false;
    }

    // >> Operator==.
    /**
     * ! same as Wine operator== and operator!=
    */
    bool operator==(const Person& person) const {
        if (this->id == person.id)
            return true;
        return false;
    }

    bool operator!=(const Person& person) const {
        return !this->operator==(person);
    }
};

enum class EmployeeFunction {
    Operator,
    Manager,
    Courier,
    Technician
};

// convert EmployeeFunction to string variant.
string employeeFunctionToString(EmployeeFunction function) {
    switch (function) {
    case EmployeeFunction::Operator:
        return "operator";
    case EmployeeFunction::Manager:
        return "manager";
    case EmployeeFunction::Courier:
        return "courier";
    default:
        return "technician";
    }
}

// convert string to EmployeeFunction variant.
EmployeeFunction stringToEmployeeFunction(string function) {
    for (int i = 0; i < function.length(); i++)
        function[i] = tolower(function[i]);

    if (function == "operator")
        return EmployeeFunction::Operator;

    if (function == "manager")
        return EmployeeFunction::Manager;

    if (function == "courier")
        return EmployeeFunction::Courier;

    if (function == "technician")
        return EmployeeFunction::Technician;

    throw "Unknown employee function";
}

class Employee : public Person {
private:
    float salary = 0;
    Date employmentDate = Date();
    EmployeeFunction function = EmployeeFunction::Courier;

public:
    // >> Getters.
    float getSalary() const {
        return this->salary;
    }

    Date getEmploymentDate() const {
        return this->employmentDate;
    }

    EmployeeFunction getFunction() const {
        return this->function;
    }

    // >> Setters.
    void setSalary(float newSalary) {
        if (newSalary < 0)
            throw "Salary cannot be negative";

        this->salary = newSalary;
    }

    void setFunction(EmployeeFunction newFunction) {
        this->function = newFunction;
    }

    // >> Constructors.
    Employee() : Person() {
        this->salary = 0;
        this->employmentDate = Date();
        this->function = EmployeeFunction::Courier;
    }

    Employee(const char* firstName, const char* lastName, string email, string phone, Gender gender, Date birthDate,
        float salary, Date employmentDate, EmployeeFunction function) :
        Person(firstName, lastName, email, phone, gender, birthDate) {
        this->setSalary(salary);
        this->employmentDate = employmentDate;
        this->function = function;
    }

    // >> Copy constructor.
    Employee(const Employee& employee) : Person(employee) {
        this->setSalary(employee.salary);
        this->employmentDate = employee.employmentDate;
        this->function = employee.function;
    }

    // >> Operator=.
    Employee& operator=(const Employee& employee) {
        if (this == &employee)
            return *this;

        Person::operator=(employee);
        this->setSalary(employee.salary);
        this->employmentDate = employee.employmentDate;
        this->function = employee.function;

        return *this;
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputEmployee here).
     * ? We use try because user input can be invalid.
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here employee to inputEmployee)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, Employee& employee) {
        // try to read input.
        Employee inputEmployee;

        // make a cast to Person type and use Person operator>> to read its attributes.
        Person& inputEmployeeAsPerson = inputEmployee;
        in >> inputEmployeeAsPerson;

        // read Employee attributes.
        float salary;
        cout << "Enter salary: ";
        in >> salary;
        inputEmployee.setSalary(salary);

        cout << "Enter employment date: \n";
        in >> inputEmployee.employmentDate;
        in.get();

        string aux;
        cout << "Enter function (operator, manager, courier, technician): ";
        getline(in, aux);
        inputEmployee.setFunction(stringToEmployeeFunction(aux));


        employee = inputEmployee;

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const Employee& employee) {
        const Person& employeeAsPerson = employee;
        out << employeeAsPerson << '\n';

        out << "Salary: " << employee.salary << '\n';
        out << "Employment date: " << employee.employmentDate.forConsole() << '\n';
        out << "Function: " << employeeFunctionToString(employee.function);

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const Employee& employee) {
        const Person& employeeAsPerson = employee;
        out << employeeAsPerson << '\n';

        out << employee.salary << '\n';
        out << employee.employmentDate.forTextFile() << '\n';
        out << employeeFunctionToString(employee.function);

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, Employee& employee) {
        Person& employeeAsPerson = employee;
        in >> employeeAsPerson;

        in >> employee.salary;
        in >> employee.employmentDate.day >> employee.employmentDate.month >> employee.employmentDate.year;
        in.get();

        string aux;
        getline(in, aux);
        employee.function = stringToEmployeeFunction(aux);

        return in;
    }

    // >> Generic methods.
    bool employedBefore(const Date& date) const {
        if (this->employmentDate < date)
            return true;

        return false;
    }

    // >> Operator +, -.
    /**
     * ? Create employee copy
     * ? Add value to copy salary
     * ? Return copy
     * @return new employee with increased salary.
    */
    Employee operator+(float value) const {
        Employee copy = *this;
        copy.salary = copy.salary + value;

        return copy;
    }

    /**
     * ? Create employee copy
     * ? Subtract value from copy salary
     * ? Return copy
     * @return new employee with decreased salary.
    */
    Employee operator-(float value) const {
        Employee copy = *this;
        copy.salary = copy.salary - value;

        return copy;
    }
};

class Client : public Person {
private:
    float incomeLevel = 0;

public:
    // >> Getters.
    float getIncomeLevel() const {
        return this->incomeLevel;
    }

    // >> Setters.
    void setIncomeLevel(float newIncomeLevel) {
        if (newIncomeLevel < 0)
            throw "Income level cannot be less than 0";

        this->incomeLevel = newIncomeLevel;
    }

    // >> Constructors.
    Client() : Person() {
        this->incomeLevel = 0;
    }

    Client(const char* firstName, const char* lastName, string email, string phone, Gender gender, Date birthDate,
        float incomeLevel) :
        Person(firstName, lastName, email, phone, gender, birthDate) {
        this->setIncomeLevel(incomeLevel);
    }

    // >> Copy constructor.
    Client(const Client& client) : Person(client) {
        this->setIncomeLevel(client.incomeLevel);
    }

    // >> Operator=.
    Client& operator=(const Client& client) {
        if (this == &client)
            return *this;

        Person::operator=(client);
        this->incomeLevel = client.incomeLevel;

        return *this;
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputClient here).
     * ? We use try because user input can be invalid.
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here client to inputClient)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, Client& client) {
        // try to read input.
        Client inputClient;

        // make a cast to Person type and use Person operator>> to read its attributes
        Person& inputClientAsPerson = inputClient;
        in >> inputClientAsPerson;

        // read client attributes.
        float income;
        cout << "Enter income level: ";
        in >> income;
        inputClient.setIncomeLevel(income);

        client = inputClient;

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const Client& client) {
        const Person& clientAsPerson = client;
        out << clientAsPerson << '\n';

        out << "Income level: " << client.incomeLevel;

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const Client& client) {
        const Person& clientAsPerson = client;
        out << clientAsPerson << '\n';

        out << client.incomeLevel;

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, Client& client) {
        Person& clientAsPerson = client;
        in >> clientAsPerson;

        in >> client.incomeLevel;

        return in;
    }

    // >> Operator +, -.
    /**
     * ? Create client copy
     * ? Add value to copy incomeLevel
     * ? Return copy
     * @return new client with increased incomeLevel.
    */
    Client operator+(float value) const {
        Client copy = *this;
        copy.incomeLevel = copy.incomeLevel + value;

        return copy;
    }

    /**
     * ? Create client copy
     * ? Add value to copy incomeLevel
     * ? Return copy
     * @return new client with increased incomeLevel.
    */
    Client operator-(float value) const {
        Client copy = *this;
        copy.incomeLevel = copy.incomeLevel - value;

        return copy;
    }
};

class OrderedWine {
private:
    static int OrderedWinesCount;
    int wineID = -1;
    float amount = 0;

public:
    // >> Getters.
    static int getOrderedWinesCount() {
        return OrderedWine::OrderedWinesCount;
    }

    int getWineID() const {
        return this->wineID;
    }

    float getAmount() const {
        return this->amount;
    }

    // >> Setters.
    void setWineID(const int newWineID) {
        bool valid = false;
        if (data_Wines.find(newWineID) != data_Wines.end())
            valid = true;

        if (!valid)
            throw "New wine ID is invalid";

        this->wineID = newWineID;
    }

    void setAmount(float newAmount) {
        if (newAmount <= 0)
            throw "New amount cannot be <= 0";

        this->amount = newAmount;
    }

    // >> Constructors.
    OrderedWine() {
        OrderedWine::OrderedWinesCount++;
        this->wineID = -1;
        this->amount = -1;
    }

    OrderedWine(int wineID, float amount) {
        OrderedWine::OrderedWinesCount++;

        this->setWineID(wineID);
        this->setAmount(amount);
    }

    // >> Copy constructor.
    OrderedWine(const OrderedWine& orderedWine) {
        OrderedWine::OrderedWinesCount++;

        this->wineID = orderedWine.wineID;
        this->amount = orderedWine.amount;
    }

    // >> Operator=.
    OrderedWine& operator=(const OrderedWine& orderedWine) {
        if (this == &orderedWine)
            return *this;

        this->wineID = orderedWine.wineID;
        this->amount = orderedWine.amount;

        return *this;
    }

    // >> Destructor.
    ~OrderedWine() {
        OrderedWine::OrderedWinesCount--;
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputOrderedWine here).
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here orderedWine to inputOrderedWine)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, OrderedWine& orderedWine) {
        // try to read input.
        OrderedWine inputOrderedWine;

        int wineID = 0;
        cout << "Enter wineID: ";
        in >> wineID;
        inputOrderedWine.setWineID(wineID);

        float amount = 0;
        cout << "Enter amount: ";
        in >> amount;
        inputOrderedWine.setAmount(amount);

        // set input
        orderedWine = inputOrderedWine;

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const OrderedWine& orderedWine) {
        out << "[Amount]: " << orderedWine.amount << '\n';
        out << "[Wine]: \n";
        if (data_Wines.find(orderedWine.wineID) != data_Wines.end())
            out << data_Wines[orderedWine.wineID];

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const OrderedWine& orderedWine) {
        out << orderedWine.wineID << ' ' << orderedWine.amount;

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, OrderedWine& orderedWine) {
        in >> orderedWine.wineID;
        in >> orderedWine.amount;

        return in;
    }

    // >> Operator +, -.
    /**
     * ? Create ordered wine copy
     * ? Add value to copy amount
     * ? Return copy
     * @return new ordered wine with increased amount.
    */
    OrderedWine operator+(float value) const {
        OrderedWine copy = *this;
        copy.amount = copy.amount + value;

        return copy;
    }

    /**
     * ? Create ordered wine copy
     * ? Subtract value from copy amount
     * ? Return copy
     * @return new ordered wine with decreased amount.
    */
    OrderedWine operator-(float value) const {
        OrderedWine copy = *this;
        copy.amount = copy.amount - value;

        return copy;
    }

    // >> Generic methods.
    /**
     * @return price * amount
    */
    float getOrderPrice() const {
        float winePrice = 0;

        // find wine price in application data.
        if (data_Wines.find(this->wineID) != data_Wines.end())
            winePrice = data_Wines[this->wineID].getPrice();

        return winePrice * amount;
    }

    // >> Cast operator.
    operator float() const {
        return this->amount;
    }

    // >> Operator <=, <.
    bool operator<=(const OrderedWine& orderedWine) const {
        if (this->amount <= orderedWine.amount)
            return true;
        return false;
    }

    bool operator<(const OrderedWine& orderedWine) const {
        if (this->amount < orderedWine.amount)
            return true;
        return false;
    }

    // >> Operator==.
    bool operator==(const OrderedWine& orderedWine) const {
        if (this->wineID == orderedWine.wineID && this->amount == orderedWine.amount)
            return true;
        return false;
    }

    bool operator!=(const OrderedWine& orderedWine) const {
        return !this->operator==(orderedWine);
    }
};

int OrderedWine::OrderedWinesCount = 0;

class Order {
private:
    int id = -1;
    int clientID = -1;
    int employeeID = -1;

    int orderedWinesLength = 0;
    OrderedWine* orderedWines = NULL;

public:
    // >> Getters.
    int getID() const {
        return this->id;
    }

    int getClientID() const {
        return this->clientID;
    }

    int getEmployeeID() const {
        return this->employeeID;
    }

    int getOrderedWinesLength() const {
        return this->orderedWinesLength;
    }

    // return ordered wine at given index
    OrderedWine getOrderedWine(int index) const {
        if (index >= 0 && index < this->orderedWinesLength)
            return this->orderedWines[index];

        throw "Index out of bounds";
    }

    // >> Setters.
    void setClientID(const int newClientID) {
        bool valid = false;
        if (data_Clients.find(newClientID) != data_Clients.end())
            valid = true;

        if (!valid)
            throw "New wine ID is invalid";

        this->clientID = newClientID;
    }

    void setEmployeeID(const int newEmployeeID) {
        bool valid = false;
        if (data_Employees.find(newEmployeeID) != data_Employees.end())
            valid = true;

        if (!valid)
            throw "New wine ID is invalid";

        this->employeeID = newEmployeeID;
    }

    void setOrderedWines(int newLength, const OrderedWine* wines) {
        if (wines == NULL || newLength <= 0)
            throw "Invalid input";

        if (this->orderedWines != NULL) {
            delete[] this->orderedWines;
            this->orderedWines = NULL;
        }

        this->orderedWinesLength = newLength;
        this->orderedWines = new OrderedWine[newLength];

        for (int i = 0; i < newLength; i++)
            this->orderedWines[i] = wines[i];
    }

    // >> Constructors.
    Order() {
        this->id = makeID();
        this->clientID = -1;
        this->employeeID = -1;
        this->orderedWinesLength = 0;
        this->orderedWines = NULL;
    }

    Order(int clientID, int employeeID, int orderedWinesLength, OrderedWine* orderedWines) {
        this->id = makeID();
        this->setClientID(clientID);
        this->setEmployeeID(employeeID);
        this->setOrderedWines(orderedWinesLength, orderedWines);
    }

    // >> Copy constructor.
    Order(const Order& order) {
        this->id = order.id;
        this->clientID = order.clientID;
        this->employeeID = order.employeeID;
        this->setOrderedWines(order.orderedWinesLength, order.orderedWines);
    }

    // >> Operator=.
    Order& operator=(const Order& order) {
        if (this == &order)
            return *this;

        this->id = order.id;
        this->clientID = order.clientID;
        this->employeeID = order.employeeID;
        this->setOrderedWines(order.orderedWinesLength, order.orderedWines);

        return *this;
    }

    // >> Destructor.
    ~Order() {
        if (this->orderedWines != NULL) {
            delete[] this->orderedWines;
            this->orderedWines = NULL;
        }
    }

    // Operator >> istream.
    /**
     * ? INFO:
     * ? Try to read input in auxiliar variable (inputOrder here).
     * ? We use try because user input can be invalid.
     * ? We validate user input using setters.
     * ? If one setter fails (throws exception aka input invalid), abort user input.
     * ? If the input is valid -> set variable to inputVariable (here order to inputOrder)
     * @throws const char* errorMessage if input fails
    */
    friend istream& operator>>(istream& in, Order& order) {
        // try to read input.
        Order inputOrder;

        int id;

        cout << "Enter client ID: ";
        in >> id;
        inputOrder.setClientID(id);

        cout << "Enter employee ID: ";
        in >> id;
        inputOrder.setEmployeeID(id);

        if (inputOrder.orderedWines != NULL) {
            delete[] inputOrder.orderedWines;
            inputOrder.orderedWines = NULL;
        }

        inputOrder.orderedWinesLength = 0;

        int length;
        cout << "Enter wines count: ";
        in >> length;
        if (length <= 0)
            throw "Length cannot be <= 0";

        for (int i = 0; i < length; i++) {
            OrderedWine wine;
            cout << ">> Enter wine " << i + 1 << ": \n";
            in >> wine;

            inputOrder.addWine(wine);
        }

        // set input
        order = inputOrder;

        return in;
    }

    // Operator << ostream.
    friend ostream& operator<<(ostream& out, const Order& order) {
        out << "Order ID: " << order.id << '\n';

        out << "[Client]: \n";
        if (data_Clients.find(order.clientID) != data_Clients.end())
            out << data_Clients[order.clientID] << '\n';

        out << "\n";

        out << "[Employee]: \n";
        if (data_Employees.find(order.employeeID) != data_Employees.end())
            out << data_Employees[order.employeeID] << '\n';

        out << '\n';

        out << "[Wines]: \n";
        for (int i = 0; i < order.orderedWinesLength; i++)
            out << ">> Wine " << i + 1 << ":\n" << order.orderedWines[i] << "\n\n";

        return out;
    }

    // Operator << ofstream.
    friend ofstream& operator<<(ofstream& out, const Order& order) {
        out << order.id << " " << order.clientID << ' ' << order.employeeID << ' ' << order.orderedWinesLength << '\n';
        for (int i = 0; i < order.orderedWinesLength; i++)
            out << order.orderedWines[i] << '\n';

        return out;
    }

    // Operator >> ifstream.
    friend ifstream& operator>>(ifstream& in, Order& order) {
        Order inputOrder;

        in >> inputOrder.id >> inputOrder.clientID >> inputOrder.employeeID;

        int length;
        in >> length;
        for (int i = 0; i < length; i++) {
            OrderedWine wine;
            in >> wine;
            inputOrder.addWine(wine);
        }

        order = inputOrder;

        return in;
    }

    // >> Generic methods.
    /**
     * @return total price of order. Sum(ordered wine price)
    */
    float calculateOrderPrice() const {
        float total = 0;
        for (int i = 0; i < this->orderedWinesLength; i++)
            total = total + this->orderedWines[i].getOrderPrice();

        return total;
    }

    // adds wine to order
    void addWine(const OrderedWine& wine) {
        OrderedWine* aux = new OrderedWine[this->orderedWinesLength + 1];

        for (int i = 0; i < this->orderedWinesLength; i++)
            aux[i] = this->orderedWines[i];
        aux[this->orderedWinesLength] = wine;

        if (this->orderedWines != NULL) {
            delete[] this->orderedWines;
            this->orderedWines = NULL;
        }

        this->orderedWinesLength++;
        this->orderedWines = aux;
    }

    // removes wine from order
    void removeWine(const OrderedWine& wine) {
        if (this->orderedWinesLength == 0)
            return;

        int wineIndex = -1;
        for (int i = 0; i < this->orderedWinesLength; i++)
            if (this->orderedWines[i] == wine) {
                wineIndex = i;
                break;
            }

        if (wineIndex == -1)
            return;

        OrderedWine* aux = new OrderedWine[this->orderedWinesLength - 1];
        for (int i = 0; i < wineIndex; i++)
            aux[i] = this->orderedWines[i];

        for (int i = wineIndex + 1; i < this->orderedWinesLength; i++)
            aux[i - 1] = this->orderedWines[i];

        this->orderedWinesLength--;

        if (this->orderedWines != NULL) {
            delete[] this->orderedWines;
            this->orderedWines = NULL;
        }

        this->orderedWines = aux;
    }

    // >> Operator +, -.
    // adds wine to order
    Order operator+(const OrderedWine& wine) const {
        Order copy = *this;
        copy.addWine(wine);

        return copy;
    }

    // removes wines from order
    Order operator-(const OrderedWine& wine) const {
        Order copy = *this;
        copy.removeWine(wine);

        return copy;
    }

    // >> Operator index[].
    // returns wine at given index
    OrderedWine operator[](int index) const {
        return this->getOrderedWine(index);
    }

    // >> Operator cast.
    operator int() const {
        return this->orderedWinesLength;
    }

    // >> Operator <=, <.
    /**
     * ? Compares by ordered wines length (OWL)
     * @return boolean -> true if this order OWL <= given order OWL, false otherwise
    */
    bool operator<=(const Order& order) const {
        if (this->orderedWinesLength <= order.orderedWinesLength)
            return true;
        return false;
    }

    /**
     * ? Compares by ordered wines length (OWL)
     * @return boolean -> true if this order OWL < given order OWL, false otherwise
    */
    bool operator<(const Order& order) const {
        if (this->orderedWinesLength < order.orderedWinesLength)
            return true;
        return false;
    }

    // >> Operator==.
    /**
     * 2 orders are equal if:
     *  clientIDs     are equal
     *  employeeIDs   are equal
     *  ordered wines are equal
     * @return boolean -> true if orders are equals, false otherwise
    */
    bool operator==(const Order& order) const {
        if (this->clientID == order.clientID && this->employeeID == order.clientID && this->orderedWinesLength == order.orderedWinesLength)
            for (int i = 0; i < this->orderedWinesLength; i++)
                if (this->orderedWines[i] != order.orderedWines[i])
                    return false;
        return true;
    }

    bool operator!=(const Order& order) const {
        return !this->operator==(order);
    }
};

void testWine() {
    // Test wine class
    Wine wine1; // default constructor
    Wine wine2("Wine2", 100, WineType::Red, Date({ 1, 4, 2001 }));                      // params constructor
    Wine wine3("Wine3", 250, Date({ 1, 5, 1997 }), "Old wine", 300, WineType::Rose);
    Wine wine4(wine3); // copy constructor
    Wine wine5;
    wine5 = wine2; // operator=

    cout << wine1 << '\n' << wine2 << '\n' << wine3 << '\n' << wine4 << '\n' << wine5 << '\n';

    Wine wine6;    // operator >> and << for istream and ostream (console)
    try {
        cin >> wine6;
        cout << wine6 << '\n';
    }
    catch (const char* errorMessage) {
        cout << "error: " << errorMessage << '\n';
    }

    ofstream g("test.txt");
    g << wine3 << '\n';
    g << wine2 << '\n';
    cout << wine3 << '\n';
    cout << wine2 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Wine wine7;
    Wine wine8;
    f >> wine7;
    f >> wine8;
    f.close();
    cout << wine7 << '\n';
    cout << wine8 << '\n';

    if (wine2.bottledBefore(Date({ 5, 6, 2005 })))
        cout << "Wine2 was bottled before 5/6/2005\n";

    cout << "Wine3 has " << wine3.getValueAdded() << "lei value added\n";
}

void testPerson() {
    Person p1;
    Person p2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gender::Male, Date({ 5, 2, 1995 }));
    Person p3(p2);
    Person p4;
    p4 = p2;

    Person p5;
    try {
        cin >> p5;
        cout << p5 << '\n';
    }
    catch (const char* errorMessage) {
        cout << "error: " << errorMessage << '\n';
    }

    ofstream g("test.txt");
    g << p2 << '\n';
    g << p3 << '\n';
    cout << p2 << '\n';
    cout << p3 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Person p6;
    Person p7;
    f >> p6;
    f >> p7;
    f.close();
    cout << p6 << '\n';
    cout << p7 << '\n';

    cout << "Second person full name: " << p2.getFullName() << '\n';
}

void testEmployee() {
    Employee e1;
    Employee e2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gender::Male, Date({ 5, 2, 1995 }), 3000, Date({ 5, 3, 2019 }), EmployeeFunction::Courier);
    Employee e3(e2);
    Employee e4;
    e4 = e2;

    Employee e5;
    try {
        cin >> e5;
        cout << e5 << '\n';
    }
    catch (const char* errorMessage) {
        cout << "error: " << errorMessage << '\n';
    }

    ofstream g("test.txt");
    g << e2 << '\n';
    g << e3 << '\n';
    cout << e2 << '\n';
    cout << e3 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Employee e6;
    Employee e7;
    f >> e6;
    f >> e7;
    f.close();
    cout << e6 << '\n';
    cout << e7 << '\n';

    cout << "Second client full name: " << e2.getFullName() << '\n';
}

void testClient() {
    Client c1;
    Client c2("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gender::Male, Date({ 5, 2, 1995 }), 4500);
    Client c3(c2);
    Client c4;
    c4 = c2;

    Client c5;
    try {
        cin >> c5;
        cout << c5 << '\n';
    }
    catch (const char* errorMessage) {
        cout << "error: " << errorMessage << '\n';
    }

    ofstream g("test.txt");
    g << c2 << '\n';
    g << c3 << '\n';
    cout << c2 << '\n';
    cout << c3 << '\n';
    g.close();

    cout << '\n';

    ifstream f("test.txt");
    Client c6;
    Client c7;
    f >> c6;
    f >> c7;
    f.close();
    cout << c6 << '\n';
    cout << c7 << '\n';

    cout << "Second employee full name: " << c2.getFullName() << '\n';
}

void testOrderedWine() {
    Wine wine("Wine", 250, Date({ 1, 5, 1997 }), "Old wine", 300, WineType::Rose);
    data_Wines.insert(make_pair(wine.getID(), wine));

    OrderedWine o1;
    OrderedWine o2(wine.getID(), 20);

    cout << "Order 2 total: " << o2.getOrderPrice() << '\n';
}

void testOrder() {
    Client client("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gender::Male, Date({ 5, 2, 1995 }), 4500);
    int clientID = client.getID();
    cout << "ClientID: " << clientID << '\n';
    data_Clients.insert(make_pair(clientID, client));

    Employee employee("Andrei", "Popescu", "popescu.andrei@gmail.com", "0743940387", Gender::Male, Date({ 5, 2, 1995 }), 3000, Date({ 5, 3, 2019 }), EmployeeFunction::Courier);
    int employeeID = employee.getID();
    cout << "EmployeeID: " << employeeID << '\n';
    data_Employees.insert(make_pair(employeeID, employee));

    Wine wine("Wine", 250, Date({ 1, 5, 1997 }), "Old wine", 300, WineType::Rose);
    int wineID = wine.getID();
    cout << "WineID: " << wineID << '\n';
    data_Wines.insert(make_pair(wineID, wine));


    OrderedWine orderedWines[] = { OrderedWine(wineID, 20) , OrderedWine(wineID, 40) };
    Order order(clientID, employeeID, 2, orderedWines);

    cout << order << '\n';

    Order order2;
    order2.setClientID(clientID);
    order2.setEmployeeID(employeeID);
    order2.addWine(orderedWines[0]);
    order2.addWine(orderedWines[1]);

    cout << order2 << '\n';

    Order order3;
    try {
        cin >> order3;
        cout << order3 << '\n';
    }
    catch (const char* errorMessage) {
        cout << "error: " << errorMessage << '\n';
    }
}

void testClass() {
    testWine();
    testPerson();
    testEmployee();
    testClient();
    testOrderedWine();
    testOrder();
}


void loadApplicationData() {
    cout << "[Info] Loading application data...\n";
    // load wines
    cout << "[Info] Loading wines...\n";
    ifstream winesFile("wines.txt");
    int winesCount = 0;
    winesFile >> winesCount;

    for (int i = 0; i < winesCount; i++) {
        Wine wine;
        winesFile >> wine;
        data_Wines.insert(make_pair(wine.getID(), wine));
    }

    // load clients
    cout << "[Info] Loading clients...\n";
    ifstream clientsFile("clients.txt");
    int clientsCount = 0;
    clientsFile >> clientsCount;

    for (int i = 0; i < clientsCount; i++) {
        Client client;
        clientsFile >> client;
        data_Clients.insert(make_pair(client.getID(), client));
    }

    // load employees
    ifstream employeesFile("employees.txt");
    cout << "[Info] Loading employees...\n";
    int employeesCount = 0;
    employeesFile >> employeesCount;

    for (int i = 0; i < employeesCount; i++) {
        Employee employee;
        employeesFile >> employee;
        data_Employees.insert(make_pair(employee.getID(), employee));
    }

    // load orders
    ifstream ordersFile("orders.txt");
    cout << "[Info] Loading orders...\n";
    int ordersCount = 0;
    ordersFile >> ordersCount;

    for (int i = 0; i < ordersCount; i++) {
        Order order;
        ordersFile >> order;
        data_Orders.insert(make_pair(order.getID(), order));
    }

    cout << "[Info] Application Data Loaded!\n";
}

void saveApplicationData() {
    // save wines
    ofstream winesFile("wines.txt");

    winesFile << data_Wines.size() << '\n';

    for (map<int, Wine>::iterator it = data_Wines.begin(); it != data_Wines.end(); it++)
        winesFile << it->second << '\n';

    winesFile.close();

    // save clients
    ofstream clientsFile("clients.txt");

    clientsFile << data_Clients.size() << '\n';

    for (map<int, Client>::iterator it = data_Clients.begin(); it != data_Clients.end(); it++)
        clientsFile << it->second << '\n';

    clientsFile.close();

    // save employees
    ofstream employeesFile("employees.txt");

    employeesFile << data_Employees.size() << '\n';

    for (map<int, Employee>::iterator it = data_Employees.begin(); it != data_Employees.end(); it++)
        employeesFile << it->second << '\n';

    employeesFile.close();

    // save wines
    ofstream ordersFile("orders.txt");

    ordersFile << data_Orders.size() << '\n';

    for (map<int, Order>::iterator it = data_Orders.begin(); it != data_Orders.end(); it++)
        ordersFile << it->second << '\n';

    ordersFile.close();
}

class Menu {
private:
    void showMenu() {
        cout << "\nMenu\n";
        cout << "Choose option: \n";
        cout << "1) Add Wine\n";
        cout << "2) Add Client\n";
        cout << "3) Add Employee\n";
        cout << "4) Add Order\n";
        cout << '\n';
        cout << "5) List Wines\n";
        cout << "6) List Clients\n";
        cout << "7) List Employees\n";
        cout << "8) List Orders\n";
        cout << '\n';
        cout << "9)  Delete Wine\n";
        cout << "10) Delete Client\n";
        cout << "11) Delete Employee\n";
        cout << "12) Delete Order\n";
        cout << '\n';
        cout << "13) List Wines in price range\n";
        cout << "14) List Wines bottled before given date\n";
        cout << "15) List Employees with salary within given range\n";
        cout << "16) List Orders with price within given range\n";
        cout << '\n';
        cout << "17) Save Data\n";
        cout << "18) Exit\n";

        cout << "\n";
    }
public:
    void run() {
        this->showMenu();

        while (true) {

            int option = 0;
            cout << "Enter option (0 to show menu): ";
            cin >> option;
            cout << "\n";

            try {
                switch (option) {
                case 0: {
                    this->showMenu();
                    break;
                }
                case 1: { // add wine
                    cin.get();

                    Wine wine;
                    cout << ">> Enter wine data:\n";
                    cin >> wine;

                    data_Wines.insert(make_pair(wine.getID(), wine));
                    cout << "[Success] Wine data inserted\n";

                    break;
                }
                case 2: { // add client
                    cin.get();

                    Client client;
                    cout << ">> Enter client data:\n";
                    cin >> client;

                    data_Clients.insert(make_pair(client.getID(), client));
                    cout << "[Success] Client data inserted\n";

                    break;
                }
                case 3: {// add employee
                    cin.get();

                    Employee employee;
                    cout << ">> Enter employee data:\n";
                    cin >> employee;

                    data_Employees.insert(make_pair(employee.getID(), employee));
                    cout << "[Success] Employee data inserted\n";

                    break;
                }
                case 4: {// add order
                    Order order;
                    cout << ">> Enter order data:\n";
                    cin >> order;

                    data_Orders.insert(make_pair(order.getID(), order));
                    cout << "[Success] Order data inserted\n";

                    break;
                }
                case 5: {// list wines
                    if (data_Wines.empty()) {
                        cout << "[Info] No wines in database.\n";
                        break;
                    }

                    cout << "---------------------- Wines ----------------------\n";
                    for (map<int, Wine>::iterator it = data_Wines.begin(); it != data_Wines.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 6: {// list clients
                    if (data_Clients.empty()) {
                        cout << "[Info] No clients in database.\n";
                        break;
                    }

                    cout << "---------------------- Clients ----------------------\n";
                    for (map<int, Client>::iterator it = data_Clients.begin(); it != data_Clients.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 7: {// list employees
                    if (data_Employees.empty()) {
                        cout << "[Info] No employees in database.\n";
                        break;
                    }

                    cout << "---------------------- Employees ----------------------\n";
                    for (map<int, Employee>::iterator it = data_Employees.begin(); it != data_Employees.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 8: {// list orders
                    if (data_Orders.empty()) {
                        cout << "[Info] No orders in database.\n";
                        break;
                    }

                    cout << "---------------------- Orders ----------------------\n";
                    for (map<int, Order>::iterator it = data_Orders.begin(); it != data_Orders.end(); it++)
                        cout << it->second << "\n---------------------------------\n";

                    break;
                }
                case 9: {// delete wine
                    int wineID = 0;
                    cout << ">> Enter wine ID to delete: ";
                    cin >> wineID;

                    data_Wines.erase(wineID);
                    cout << "[Success] Wine deleted\n";

                    break;
                }
                case 10: {// delete client
                    int clientID = 0;
                    cout << ">> Enter client ID to delete: ";
                    cin >> clientID;

                    data_Clients.erase(clientID);
                    cout << "[Success] Client deleted\n";

                    break;
                }
                case 11: {// delete employee
                    int employeeID = 0;
                    cout << ">> Enter employee ID to delete: ";
                    cin >> employeeID;

                    data_Employees.erase(employeeID);
                    cout << "[Success] Employee deleted\n";

                    break;
                }
                case 12: {// delete order
                    int orderID = 0;
                    cout << ">> Enter order ID to delete: ";
                    cin >> orderID;

                    data_Orders.erase(orderID);
                    cout << "[Success] Order deleted\n";

                    break;
                }
                case 13: {// list wines in price range
                    int minPrice = 0;
                    cout << ">> Enter minimum price: ";
                    cin >> minPrice;

                    int maxPrice = 0;
                    cout << ">> Enter maximum price: ";
                    cin >> maxPrice;

                    ofstream reportFile("report.txt");

                    int winesCount = 0;
                    for (map<int, Wine>::iterator it = data_Wines.begin(); it != data_Wines.end(); it++) {
                        Wine& wine = it->second;

                        if (wine.getPrice() >= minPrice && wine.getPrice() <= maxPrice) {
                            winesCount = winesCount + 1;
                            reportFile << "----------- " << winesCount << " -----------\n";

                            reportFile << "ID: " << wine.getID() << '\n';
                            reportFile << "Name: " << wine.getName() << '\n';
                            reportFile << "Description: " << wine.getDescription() << '\n';
                            reportFile << "Type: " << wineTypeToString(wine.getWineType()) << '\n';
                            reportFile << "Min price: " << wine.getMinPrice() << '\n';
                            reportFile << "Price: " << wine.getPrice() << '\n';
                            reportFile << "Value added: " << wine.getValueAdded() << '\n';
                            Date bottlingDate = wine.getBottlingDate();
                            reportFile << "Bottled at " << bottlingDate.day << '/' << bottlingDate.month << '/' << bottlingDate.year << '\n';

                            reportFile << "\n";
                        }
                    }

                    reportFile.close();

                    cout << "[Success] Report generated!\n";

                    break;
                }
                case 14: {// list lines bottled before given date
                    Date date;
                    cout << ">> Enter date:\n";
                    cin >> date;

                    ofstream reportFile("report.txt");

                    int winesCount = 0;
                    for (map<int, Wine>::iterator it = data_Wines.begin(); it != data_Wines.end(); it++) {
                        Wine& wine = it->second;

                        if (wine.bottledBefore(date)) {
                            winesCount = winesCount + 1;
                            reportFile << "----------- " << winesCount << " -----------\n";

                            reportFile << "ID: " << wine.getID() << '\n';
                            reportFile << "Name: " << wine.getName() << '\n';
                            reportFile << "Description: " << wine.getDescription() << '\n';
                            reportFile << "Type: " << wineTypeToString(wine.getWineType()) << '\n';
                            reportFile << "Min price: " << wine.getMinPrice() << '\n';
                            reportFile << "Price: " << wine.getPrice() << '\n';
                            reportFile << "Value added: " << wine.getValueAdded() << '\n';
                            Date bottlingDate = wine.getBottlingDate();
                            reportFile << "Bottled at " << bottlingDate.day << '/' << bottlingDate.month << '/' << bottlingDate.year << '\n';

                            reportFile << "\n";
                        }
                    }

                    reportFile.close();

                    cout << "[Success] Report generated!\n";

                    break;
                }
                case 15: {// list employees with salary in given range
                    int minSalary = 0;
                    cout << ">> Enter minimum salary: ";
                    cin >> minSalary;

                    int maxSalary = 0;
                    cout << ">> Enter maximum salary: ";
                    cin >> maxSalary;

                    ofstream reportFile("report.txt");

                    int employeesCount = 0;
                    for (map<int, Employee>::iterator it = data_Employees.begin(); it != data_Employees.end(); it++) {
                        Employee& employee = it->second;

                        if (employee.getSalary() >= minSalary && employee.getSalary() <= maxSalary) {
                            employeesCount = employeesCount + 1;
                            reportFile << "----------- " << employeesCount << " -----------\n";

                            reportFile << "ID: " << employee.getID() << '\n';
                            reportFile << "Name: " << employee.getFullName() << '\n';
                            reportFile << "Email: " << employee.getEmail() << '\n';
                            reportFile << "Phone: " << employee.getPhone() << '\n';
                            reportFile << "Gender: " << genderToString(employee.getGender()) << '\n';

                            Date birtDate = employee.getBirthDate();
                            reportFile << "Born at " << birtDate.day << '/' << birtDate.month << '/' << birtDate.year << '\n';

                            Date employmentDate = employee.getEmploymentDate();
                            reportFile << "Employed since " << employmentDate.day << '/' << employmentDate.month << '/' << employmentDate.year << '\n';

                            reportFile << "\n";
                        }
                    }

                    reportFile.close();

                    cout << "[Success] Report generated!\n";

                    break;
                }
                case 16: {// list orders with price in given range
                    int minPrice = 0;
                    cout << ">> Enter minimum price: ";
                    cin >> minPrice;

                    int maxPrice = 0;
                    cout << ">> Enter maximum price: ";
                    cin >> maxPrice;

                    ofstream reportFile("report.txt");

                    int ordersCount = 0;
                    for (map<int, Order>::iterator it = data_Orders.begin(); it != data_Orders.end(); it++) {
                        Order& order = it->second;
                        float orderPrice = order.calculateOrderPrice();

                        if (orderPrice >= minPrice && orderPrice <= maxPrice) {
                            ordersCount = ordersCount + 1;
                            reportFile << "----------- " << ordersCount << " -----------\n";
                            reportFile << "OrderID: " << order.getID() << '\n';
                            reportFile << "Price: " << orderPrice << "lei\n";

                            if (data_Clients.find(order.getClientID()) != data_Clients.end()) {
                                Client& client = data_Clients[order.getClientID()];
                                reportFile << "ClientID: " << client.getID() << '\n';
                                reportFile << "ClientName: " << client.getFullName() << '\n';
                            }
                            else {
                                reportFile << "Client was removed from database.\n";
                            }

                            if (data_Employees.find(order.getEmployeeID()) != data_Employees.end()) {
                                Employee& employee = data_Employees[order.getEmployeeID()];
                                reportFile << "EmployeeID: " << employee.getID() << '\n';
                                reportFile << "EmployeeName: " << employee.getFullName() << '\n';
                            }
                            else {
                                reportFile << "Employee was removed from database.\n";
                            }

                            for (int i = 0; i < order.getOrderedWinesLength(); i++) {
                                OrderedWine orderedWine = order[i];

                                reportFile << "Wine" << i << ": ";

                                if (data_Wines.find(orderedWine.getWineID()) != data_Wines.end()) {
                                    Wine& wine = data_Wines[orderedWine.getWineID()];
                                    reportFile << "ID(" << wine.getID() << ") ~ Name(" << wine.getName() << ") ~ Amount(" << orderedWine.getAmount() << ")\n";
                                }
                                else {
                                    reportFile << "Wine was removed from database.\n";
                                }

                            }

                            reportFile << "\n";
                        }
                    }

                    reportFile.close();

                    cout << "[Success] Report generated!\n";

                    break;
                }
                case 17: {// save data
                    saveApplicationData();

                    cout << "[Success] Saved Application Data!\n";

                    break;
                }
                case 18: {// exit
                    return;
                }
                default: {
                    throw "Invalid option";
                }
                }
            }
            catch (const char* errorMessage) {
                cout << "\n[Error]: " << errorMessage << "\n\n";
            }
        }
    }
};

int main() {
    loadApplicationData();

    Menu menu;
    menu.run();

    saveApplicationData();

    return 0;
}
