#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Employee
{
    protected:
        string name;
        string lastname;
        string employmentType;
        double salary;
    public:
        Employee();
        Employee(string first, string last, string type, double pay) : name{first}, lastname{last}, employmentType{type}, salary{pay} {}

        string get_name() const{return name;}
        string get_lastname() const{return lastname;}
        string get_employmentType() const{return employmentType;}
        double getSalary() const{return salary;}

        void set_name(string first)
        {
            this->name = first;
        }
        void set_lastname(string last)
        {
            this->lastname = last;
        }
        void set_employmentType(string type)
        {
            this->employmentType = type;
        }
        void set_salary(double pay)
        {
            this->salary = pay;
        }
        void printEmployeeInfo()
        {
            string output = "Employee=";
            output.append(this->get_name());
            output.append(" ");
            output.append(this->get_lastname());
            output.append(", ");
            output.append(this->get_employmentType());
            output.append(", ");
            output.append(to_string(this->getSalary()));
            output.append("\n");
            cout << output << endl;
        }
        ~Employee();
};

class FullTimeEmployee : public Employee
{
    public:
        FullTimeEmployee();
        FullTimeEmployee(string first, double pay) : Employee(first, "UNKNOWN", "Full-time", pay){}
        ~FullTimeEmployee();
};

class PartTimeEmployee : public Employee
{
    public:
        PartTimeEmployee();
        PartTimeEmployee(string first, double pay) : Employee(first, "UNKNOWN", "Part-time", pay){}
        ~PartTimeEmployee();
};

class Company 
{
    private:
        vector<Employee> employees;
    public:
        Company();
        void set_employees(vector<Employee> setter)
        {
            this->employees = setter;
        }
        vector<Employee> get_employees() const{return employees;}
        
        double calculateAverageSalary(double salaryThreshold)
        {
            try{
                vector<Employee>::iterator iter;
                int numEmployees = 0;
                double out = 0;
                for(iter = employees.begin(); iter != employees.end(); iter++)
                {
                    if(iter->getSalary() <= salaryThreshold)
                    {
                        numEmployees++;
                        out += iter->getSalary();
                    }
                }
                if(numEmployees == 0)
                {
                    throw string("Division by 0 No employees below salary threshold.");
                }
                else 
                {
                    return (out / numEmployees);

                }
            }
            catch (const string *e)
            {
                cerr << "Exception: " << e << endl;
                return 0.0;
            }
        }
        double companyEmployeeCost()
        {
            double out = 0;
            vector<Employee>::iterator iter;
            for(iter = employees.begin(); iter != employees.end(); iter++)
            {
                    out += iter->getSalary();
            }
            return out;
        }
        void addEmployee(Employee *e)
        {
            employees.emplace_back(e);
        }
        void printEmployees()
        {
            vector<Employee>::iterator iter;
            for(iter = employees.begin(); iter != employees.end(); iter++)
            {
                iter->printEmployeeInfo();
            } 
        }
        ~Company();
};

int main() 
{
    Company watermelon;
    watermelon.addEmployee(new FullTimeEmployee("Jack", 30000));
    watermelon.addEmployee(new PartTimeEmployee("Alice", 45000));
    watermelon.printEmployees();
    try{
        cout << "Average:" << watermelon.calculateAverageSalary(100) << endl;
    }
    catch(const char *ex) {
        cerr << "Exception: " << ex << endl;
    }
    try{
        cout << "Average:" << watermelon.calculateAverageSalary(25000) << endl;
    }
    catch(const char *ex) {
        cerr << "Exception: " << ex << endl;
    }
        cout << "Company costs:" << watermelon.companyEmployeeCost() << endl;
    Company macrosoft;
    macrosoft.addEmployee(new FullTimeEmployee("John", 20000));
    macrosoft.addEmployee(new PartTimeEmployee("Jane", 15000));
    macrosoft.addEmployee(new PartTimeEmployee("Stewie", 18000));
    macrosoft.addEmployee(new PartTimeEmployee("Loise", 35000));
    macrosoft.printEmployees();
    try{
        cout << "Average:" << macrosoft.calculateAverageSalary(15000) << endl;
    }
    catch(const char *ex) {
        cerr << "Exception: " << ex << endl;
    }
    try{
        cout << "Average:" << macrosoft.calculateAverageSalary(30000) << endl;
    }
    catch(const char *ex) {
        cerr << "Exception: " << ex << endl;
    }
        cout << "Company costs:" << macrosoft.companyEmployeeCost() << endl;
    return EXIT_SUCCESS;
}
