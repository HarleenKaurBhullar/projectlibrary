#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class book{
    int bookno;
    string bookname;
    string authorname;
    int quantity;

};

class Administrator{
    public:
    void addBook(){
        // Add book to the library
    }
    void deleteBook(){}
    void modifyBook(){}
    void addStudent(){}
    void deleteStudent(){}
    void modifyStudent(){}

};

class Student{
    int studentid;
    string studentname;
    string course;
    public:
    Student(){
        cout<<"Enter id";
        cin>>studentid;
        
    }
    void issuebook(){

    }
    void returnbook(){}
};

void ask(){
    string answer;
    cout<<"Are you a student or administrator?"<<endl;
    cin>>answer;
    
}
int main(){
    // Main function to interact with the library system
};

