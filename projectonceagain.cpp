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
    bool found1 = false;
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


bool findbook(){                         // to find a book
        string name;
        char ch;
        fstream tempfile;
        tempfile.open("tempfile1.dat",ios::in|ios::out|ios::binary|ios::trunc);
        if(!tempfile.is_open()){
            cout<<"Error in opening temp file";
        }
        cout<<"Enter name of book you want to find"<<endl;
        cin.ignore();
        getline(cin,name);
        
        fh.close();
        fh.clear();
        bool found = false;

        fh.open("booksagain.dat", ios::in|ios::binary);
        if (!fh.is_open()) {
            cerr << "Error opening file for reading" << endl;
            
        }
        string line;
        

        // Iterate through file
        while (getline(fh, line)) {
            int pos = line.find(name);
            if (pos != string::npos){
                found = true;
                cout << "Book found:" << endl;
                cout << line << endl;
                int pos1=line.find(',');
       
        int pos2=line.find(',',pos1+1);
        
        int pos3=line.find(',',pos2+1);
        
        int count=line.substr(pos3+1).length();
        
        int quantity= stoi(line.substr(pos3+1));
        
        if(quantity>0){
            cout<<"Do you want to borrow the book";
            cin>>ch;
            if(ch=='y'){
               
                 quantity--;
                line.replace(pos3+1,count,to_string(quantity));
                        
                        
                        
            }  else{
                cout<<"Returning...";
                break;
            }   
               
            }
            
        }
        tempfile<<line<<endl;
            
        
        
}
fh.close();
tempfile.close();
if(found){
                remove("booksagain.dat");
                rename("tempfile1.dat","booksagain.dat");
            }
if(!found) {
            cout << "Book not found" << endl;
            remove("tempfile.1dat");
        }
        
        fh.close();
        return found;
}

 


// string borrowbook(){
//     char ch;
//     string bline;
//     if(findbook()){
//         fh.close();
//         fh.clear();
        
//         fh.open("booksagain.dat",ios::in|ios::out|ios::binary);
//         if (!fh.is_open()) {
//             cerr << "Error opening file for reading" << endl;
//             return "";
//         }
//         while(getline(fh,line)){
        
//         int pos1=line.find(',');
       
//         int pos2=line.find(',',pos1+1);
        
//         int pos3=line.find(',',pos2+1);
        
//         int count=line.substr(pos3+1).length();
        
//         int quantity= stoi(line.substr(pos3+1));
//         cout<<"quantity is"<<quantity;
//         if(quantity>0){
//             cout<<"Do you want to borrow the book";
//             cin>>ch;
//             if(ch=='y'){
//                  quantity--;
//                         line.replace(pos3+1,count,to_string(quantity));
//                         fh.clear();
//                         fh.seekp(0);
//                         bline=line;
//                         fh<<line<<endl;
//                         cout<<"Book borrowed successfully"<<endl;
                        
//                         return line.substr(pos2+1,pos3);
//             }
//             else{
//                 cout<<"Returning...";
//                 break;
//             }
        
        
//     }
//     }
//     if(quantity++){
//         cout<<"Book currently not in stock"<<endl;
//     }
//     // int checkbook=0;
//     // if(checkbook>0){
//     //      cout<<"Do you want to borrow the book? Enter y for yes and n for no"<<endl;
//     //             char ch;
//     //             cin>>ch;
//     //             if(ch=='y'){
//     //                 int pos1=line.find(',');
//     //                 int pos2=line.find(',',pos1+1);
//     //                 int pos3=line.find(',',pos2+1);
//     //                 int count=line.substr(pos3+1).length();
                   
                    
//     //                 if(checkbook>0){
//     //                     checkbook--;
//     //                     line.replace(pos3,count,to_string(checkbook));
//     //                     fh.clear();
//     //                     fh.seekp(0);
//     //                     fh<<line<<endl;
//     //                     cout<<"Book borrowed successfully"<<endl;
//     //                     fh.close();
    
//     //             }}
                
//     //         }

// }
// }
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
            fh2<<studentname<<","<<studentid<<","<<studentprogram<<","<<"0"<< endl;
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
            if (pos != string::npos){
                found1 = true;
                cout << "Student found:" << endl;
                cout << line << endl;
               
            }
            
        }
        
        if(!found1) {
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

    void administratormenu(){
        cout<<"To verify you are administrator enter password"<<endl;
        cin>>verifypassword;
        if(verifypassword==password){
            while(choice!=7){
            cout<<"Choose option"<<endl<<"1. Add book"<<endl<<"2. Show book"<<endl<<"3. Borrow book"<<endl<<"4. Add student"<<endl<<"5. Show students"<<endl<<"6. Find students"<<endl<<"7. Exit";
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
    

// }
}};

class student:public administrator{
    public:
    string tempstudentid;
    void studentmenu(){
        cout<<"Enter your student id"<<endl;
        cin>>tempstudentid;
        findStudent(tempstudentid);
        if(found1){

            cout<<"Welcome to library"<<endl;
            while(1){
                cout<<"Choose option"<<endl<<"1. Issue book"<<endl<<"2. Return book"<<endl<<"3. Exit"<<endl;
                cin>>choice;
                switch(choice){
                    case 1:
                        borrowbook2();
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
    void borrowbook2(){
        string line1,line2;
                line2=findbook();
                cout<<line2;
                fh2.open("studentdetails.dat",ios::in|ios::out|ios::binary);
        if(!fh2.is_open()){
            cerr << "Error opening file studentdetails" << endl;
        }
         while(getline(fh2,line1)){
            int pos=line1.find(tempstudentid);
            if(pos!=std::string::npos){
           
            int pos2=line1.find(',',pos);
            
            int pos3=line1.find(',',pos2+1);
            
            line1.replace(pos3+1,line2.length(),line2);
            fh2.clear();

            fh2.seekp(0);
            fh2<<line1<<endl;
            }}
        }
};


int main(){
    int choice1;
    while(choice1!=3){
    cout<<"Welcome!"<<endl<<"if you are student type 1"<<endl<<" if you are administrator type 2"<<endl<<"type 3 to exit";
    cin>>choice1;
    switch(choice1){
        case 1:{
            student s;
            s.studentmenu();
            break;}
        case 2:{
            administrator a;
            a.administratormenu();
            break;}
        case 3:
            cout<<"Exiting..."<<endl;
            break;
        default:
            cout<<"Invalid choice";
    }}
    

    
} 