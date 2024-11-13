 #include <iostream>
using namespace std;
#include <string>
#include <fstream>

class Book{
    public:
    fstream fh;
    string str1[20];
    int n;
    int i;
    string bookname;
    string author;
    string bookno;
    int quantity;
    Book(){
        fh.open("booksagain.dat",ios::in|ios::out|ios::app|ios::binary);
        if(!fh.is_open()){
            cerr << "Error opening file books" << endl;
        }
    }

};

class studentdetails{
    public:
    fstream fh2;
    string studentname;
    string studentid;
    string studentprogram;
    studentdetails(){
        fh2.open("studentdetails.dat",ios::in|ios::out|ios::app|ios::binary);
        if(!fh2.is_open()){
            cerr << "Error opening file studentdetails" << endl;
        }
    }
};
class administrator : public Book, public studentdetails{
    public:
    int password=1234;
    int verifypassword;
    int choice;
    string line;
    bool found = false;
    void enter(){                            
        cout<<"Enter name of book: ";
        getline(cin,bookname);
        
        cout<<"Enter author of book: ";
        getline(cin,author);
        cout<<"Enter book number: ";
        cin>>bookno;
        cout<<"Enter quantity of book: ";
        cin>>quantity;
        
        cin.ignore();
    }

    void addbook(){ 
        fh.close();
        fh.open("booksagain.dat",ios::in|ios::out|ios::app|ios::binary);                      //to add book
        cout<<"Enter no of books:";
        cin>>n;
        cin.ignore();
        for(i=0;i<n;i++){
        enter();
        fh<<bookname<<","<<author<<","<<bookno<<","<<quantity<<endl;
    }}
    
    void showbooks(){                         // to see list of books
        fh.close();
        fh.clear();
        cout<<"Enter the number of books you want to see";
        cin>>n;
        cin.ignore();
        fh.open("booksagain.dat",ios::binary|ios::in);
        for(i=0;i<n;i++){
        getline(fh,str1[i]);
        cout<<str1[i]<<endl;
        
    }
    fh.close();
    }



    void findbook(){                         // to find a book
        string name;
        fh.close();
        fh.clear();
        cout<<"Enter name of book you want to find"<<endl;
        cin.ignore();
        getline(cin,name);
        
        fh.open("booksagain.dat",ios::in|ios::out|ios::binary);
        if (!fh.is_open()) {
            cerr << "Error opening file for reading" << endl;
            return;
        }
        string line;
        
        bool found = false;
        //iterate through file
        while(getline(fh,line)){
            int pos=line.find(name);
            
            if(pos != string::npos){
                found = true;
                cout<<"book available"<<endl;
                cout<<line<<endl;
                
               
        }
       


    }
    if(!found){
        cout<<"Book not found"<<endl;
        fh.close();
    }
    
}
void borrowbook(){
    findbook();
    

}
void returnbook(){
    string brname;
    line="";
    cout<<"Enter the name of the book"<<endl;
    cin.ignore();
    getline(cin, brname);
}
void enterStudent(){ // To enter student details
        cout << "Enter name of student: ";
        getline(cin, studentname);
        cout << "Enter ID of student: ";
        getline(cin, studentid);
        cout << "Enter program of student: ";
        getline(cin, studentprogram);
        
        cin.ignore();
    }

    void addstudent() { // To add student
        cout << "Enter number of students: ";
        cin >> n;
        cin.ignore();
        fh2.close();
        fh2.open("studentdetails.dat",ios::in|ios::out|ios::app|ios::binary);
        if (!fh2.is_open()) {
            cerr << "Error opening file for writing" << endl;
            return;
        }
        for (i = 0; i < n; i++) {
            enterStudent();
            fh2<<studentname<<","<<studentid<<","<<studentprogram<< endl;
        }
        fh2.close();
    }

    void showStudents() { // To see list of students
        fh2.close();
        cout << "Enter the number of students you want to see: ";
        cin >> n;
        cin.ignore();
        fh2.open("studentdetails.dat", ios::in|ios::binary);
        if (!fh2.is_open()) {
            cerr << "Error opening file for reading" << endl;
            return;
        }
        string str1;
        for (i = 0; i < n; i++) {
            if (getline(fh2, str1)) {
                cout << str1 << endl;
            } else {
                break;
            }
        }
        fh2.close();
    }

    

    void findStudent(string id) { // To find a student
       
        fh2.close();
        fh2.clear();
        

        fh2.open("studentdetails.dat", ios::in|ios::binary);
        if (!fh2.is_open()) {
            cerr << "Error opening file for reading" << endl;
            return;
        }
        string line;
        

        // Iterate through file
        while (getline(fh2, line)) {
            int pos = line.find(id);
            if (pos != string::npos) {
                found = true;
                cout << "Student found:" << endl;
                cout << line << endl;
                break;
            }
        }
        
        if (!found) {
            cout << "Student not found" << endl;
        }
        
        fh2.close();
    }

    void adminfindstudent(){
         string id;
         cout << "Enter id of student you want to find: ";
        cin.ignore();
        getline(cin, id);
        findStudent(id);
    }

    administrator(){
        cout<<"To verify you are administrator enter password"<<endl;
        cin>>verifypassword;
        if(verifypassword==password){
            while(choice!=7){
            cout<<"Choose option"<<endl<<"1. Add book"<<endl<<"2. Show book"<<endl<<"3. Find books"<<endl<<"4. Add student"<<endl<<"5. Show students"<<endl<<"6. Find students"<<endl<<"7. Exit";
            cin>>choice;
            switch(choice){
                case 1:
                    addbook();
                    break;
                case 2:
                    showbooks();
                    break;
                case 3:
                    findbook();
                    break;
                case 4:
                    addstudent();
                    break;
                case 5:
                    showStudents();
                    break;
                case 6:
                    adminfindstudent();
                    break;
                case 7:
                cout<<"Exiting..."<<endl;
                break;
                default:
                    cout<<"Invalid choice";
        
    }}}
    

}};

class student:public administrator{
    public:
    string tempstudentid;
    student(){
        cout<<"Enter your student id"<<endl;
        cin>>tempstudentid;
        findStudent(tempstudentid);
        if(found){
            cout<<"Welcome to library"<<endl;
            while(1){
                cout<<"Choose option"<<endl<<"1. Issue book"<<endl<<"2. Return book"<<endl<<"3. Exit"<<endl;
                cin>>choice;
                switch(choice){
                    case 1:
                        findbook();
                        break;
                    case 2:
                        returnbook();
                        break;
                    case 3:
                        exit(0);
                        break;
                    default:
                        cout<<"Invalid choice";
                }
            }
        }


    }
};


int main(){
    student s;
    
} 