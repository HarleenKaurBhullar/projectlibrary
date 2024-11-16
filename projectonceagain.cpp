 #include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <cctype>
class Book{                      //class book to declare attributes of books
    public:
    fstream fh;
    string str1[20];
    int n;
    int i;
    string bookname;
    string author;
    string bookno;
    int quantity;
    Book(){                      //constructor books to initialise file to store book data
        fh.open("booksagain.dat",ios::in|ios::out|ios::app|ios::binary);       //opening a binary file called booksagain.dat to 
        if(!fh.is_open()){                                                     //store details of books
            cerr << "Error opening file books" << endl;
        }
    }

};

class studentdetails{            //class student details to declare attributes of students data
    public:
    fstream fh2;
    string studentname;
    string studentid;
    string studentprogram;
    studentdetails(){             //constructor student details to initialize file
        fh2.open("studentdetails.dat",ios::in|ios::out|ios::app|ios::binary);            //opening a binary file called studentdetails.dat 
        if(!fh2.is_open()){                                                              //to store details of student
            cerr << "Error opening file studentdetails" << endl;
        }
    }
};

string tolowercase(string s) {           //A function to convert strings to lowercase
        for(char c: s){
            c = tolower(c);
        }
        return s;
    }

class administrator : public Book, public studentdetails{             //Administartor class attribute to handle all administartion related 
    public:                                                           //operations
    bool found1 = false;
    int password=1234;
    int verifypassword;
    int choice;
    string line;
    bool found = false;
    void enter(){                                                     //function for administrator to enter name of the book
        cout<<"Enter name of book: ";
        getline(cin,bookname);
        bookname=tolowercase(bookname);
        cout<<"Enter author of book: ";
        getline(cin,author);
        author=tolowercase(author);
        cout<<"Enter book number: ";
        cin>>bookno;
        cout<<"Enter quantity of book: ";
        cin>>quantity;
        
        cin.ignore();
    }

    void addbook(){                                                    //function to add book to binary file that stores books using
        fh.close();                                                    //previous enter function
        fh.open("booksagain.dat",ios::in|ios::out|ios::app|ios::binary);                      
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


string findbook(string name) {             //to find a book
    fh.close();
    fh.clear();
    fh.open("booksagain.dat", ios::in | ios::binary);
    if (!fh.is_open()) {
        cerr << "Error opening file for reading" << endl;
        return "";
    }

    string line;
    while (getline(fh, line)) {
        int pos = line.find(name);
        if (pos != string::npos) {
            fh.close();
            return line; // Return the found book details
        }
    }

    fh.close();
    return ""; // Return empty if book not found
}


 
void deletebook() {                         //function to delete record of a book
    string deline, line;  
    fstream tempfile;
    bool found = false;

    cout << "Enter the name of the book to delete: ";
    cin.ignore();
    getline(cin, deline);
    deline = tolowercase(deline);

    // Check if the book exists
    fh.close();
    fh.clear();
    if (findbook(deline).empty()) {         //if book not found return
        cout << "Book not found!" << endl;
        return;
    }

    // Reopen the books file for reading
    fh.open("booksagain.dat", ios::in | ios::binary);
    if (!fh.is_open()) {
        cerr << "Error opening books file for reading" << endl;
        return;
    }

    // Open temporary file for writing
    tempfile.open("temp.dat", ios::out | ios::binary);          //initializing a temporary file to store data
    if (!tempfile.is_open()) {
        cerr << "Error opening temporary file" << endl;
        fh.close();
        return;
    }

    // Read and write lines, excluding the one to be deleted
    while (getline(fh, line)) {                        //if book is found delete the book and rewrite the file
        if (line.find(deline) == string::npos) {
            tempfile << line << endl; // Copy lines that do not match
        } else {
            found = true; // Book found and skipped
        }
    }

    fh.close();
    tempfile.close();

    if (found) {
        remove("booksagain.dat");
        rename("temp.dat", "booksagain.dat");
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Book not found in file!" << endl;
    }
}

void deletestudent(){                   //function to delete record of a student
    string tempid1,string2;
    fstream tempstufile;
    bool found = false;
    cout<<"Enter id of student to delete";
    cin>>tempid1;
   
    fh2.close();
    
    fh2.clear();
    fh2.open("studentdetails.dat",ios::in|ios::out|ios::binary);
     if(!fh2.is_open()){
        cout<<"Error opening students file";
    }
    tempstufile.open("tempstu.dat",ios::out|ios::binary|ios::trunc);     //initialization of a temporary file to store details of student
    if(!tempstufile.is_open()){
        cerr<<"Error opening tempstu file";
        return;
    }
   

    while(getline(fh2,string2)){          //skip over the line of student if found                 
        int pos=string2.find(tempid1);
        if(pos!=string::npos){
            found=true;
            continue;
        }
        tempstufile<<string2<<endl;
        
    }

     fh2.clear();
    fh2.close();
    tempstufile.close();
    tempstufile.clear();
    if(found){                        //rewriting previous file with new file
        cout<<"Student deleted successfully";
       
    remove("studentdetails.dat");
    rename("tempstu.dat","studentdetails.dat");
    }
    else{                           //if there is no matching student in file
        cout<<"Student not found";
        remove("tempstu.dat");
    }
    

   
}

void modifyquantity(){              //for administrator to modify the quantity of books
    string qbookno,qline;
    fstream tempfile;
    bool found=false;
    
    cout<<"Enter book number to modify quantity: ";
    cin>>qbookno;
    string newquantity;
    if(findbook(qbookno)==""){
        cout<<"Book not found!";
        return;
    }
    cout<<"Enter new quantity: ";
    cin>>newquantity;
    fh.close();
    fh.clear();
    fh.open("booksagain.dat",ios::in|ios::out|ios::binary);
    tempfile.open("temp.dat",ios::out|ios::binary|ios::trunc);

    while(getline(fh,qline)){
        int pos1=qline.rfind(',');
        if(pos1!=string::npos){
            found=true;
        string tempstr=qline.substr(pos1);
        qline.replace(pos1+1,newquantity.length(),newquantity);}
        tempfile<<qline<<endl;

    }
    fh.close();
    tempfile.close();
    if(found){
        cout<<"Quantity updated successfully";
        remove("booksagain.dat");
        rename("temp.dat","booksagain.dat");
    }
    else{
        cout<<"Book not found";
        remove("temp.dat");
    }
   

}




void enterStudent(){ // To enter student details
        cout << "Enter name of student: ";
        getline(cin, studentname);
        studentname=tolowercase(studentname);
        cout << "Enter ID of student: ";
        getline(cin, studentid);
        cout << "Enter program of student: ";
        getline(cin, studentprogram);
        studentprogram=tolowercase(studentprogram);
        
        cin.ignore();
    }

    void addstudent() { // To add student to binary file of student
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

    

    void findStudent(string id) { // To find a student through id of student
       
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

    void adminfindstudent(){             //for admin to find student
         string id;
         cout << "Enter id of student you want to find: ";
        cin.ignore();
        getline(cin, id);
        findStudent(id);
    }

    void administratormenu(){               //menu for administrator 
        string findname;
        cout<<"To verify you are administrator enter password"<<endl;
        cin>>verifypassword;
        if(verifypassword==password){
            while(choice!=10){
            cout<<"Choose option"<<endl<<"1. Add book"<<endl<<"2. Show book"<<endl<<"3. Find book"<<endl<<"4. Add student"<<endl<<"5. Show students"<<endl<<"6. Find students"<<endl<<"7.Delete book"<<endl<<"8. Delete Student"<<endl<<"9.Modify quantity of book"<<endl<<"10.Exit";
            cin>>choice;
            switch(choice){
                case 1:
                    addbook();
                    break;
                case 2:
                    showbooks();
                    break;
                case 3:
                cout<<"Enter book name";
                cin>>findname;
                    findbook(findname);
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
                    deletebook();
                    break;
                case 8:
                    deletestudent();
                    break;
                case 9:
                   modifyquantity();
                    break;
                case 10:
                cout<<"Exiting..."<<endl;
                break;
                default:
                    cout<<"Invalid choice";
        
    }}}
    

// }
}};

class student:public administrator{            //a student class that inherits administrator class
    public:
    string tempstudentid;
    void studentmenu(){                       //menu for student
        cout<<"Enter your student id"<<endl;
        cin>>tempstudentid;
        findStudent(tempstudentid);
        if(found1){

            cout<<"Welcome to library"<<endl;
            while(choice!=3){
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
                        cout<<"Exiting...";
                        break;
                    default:
                        cout<<"Invalid choice";
                }
            }
        }
        


    }

    void returnbook() {                         //function to return a book
    string line, bookno;
    fstream tempfile, tempstufile;
    bool bookReturned = false;

    // Open the student details file
    fh2.open("studentdetails.dat", ios::in | ios::binary);
    if (!fh2.is_open()) {
        cerr << "Error opening studentdetails.dat" << endl;
        return;
    }

    // Create a temporary file for student details
    tempstufile.open("tempstufile1.dat", ios::out | ios::binary | ios::trunc);
    if (!tempstufile.is_open()) {
        cerr << "Error opening tempstufile1.dat" << endl;
        fh2.close();
        return;
    }

    // Process each student record
    while (getline(fh2, line)) {          //using id of student to find its record and if student has a book borrowed return book
        size_t pos = line.find(tempstudentid);
        if (pos != string::npos) { // Found student record
            size_t lastComma = line.rfind(',');
            bookno = line.substr(lastComma + 1);

            if (bookno != "0") { // Student has borrowed a book
                cout << "Returning book with ID: " << bookno << endl;
                line.replace(lastComma + 1, bookno.length(), "0");
                bookReturned = true;
            } else {                    //If student has no book issued
                cout << "You have not borrowed any books." << endl;
            }
        }
        tempstufile << line << endl; // Write to temporary student file
    }

    fh2.close();
    tempstufile.close();

    remove("studentdetails.dat");        // Replace the original student details file
    rename("tempstufile1.dat", "studentdetails.dat");

    if (!bookReturned) {
        return;                         // Exit if no book was returned
    }

    fh.open("booksagain.dat", ios::in | ios::binary);  // Replace the original student details file
    if (!fh.is_open()) {
        cerr << "Error opening booksagain.dat" << endl;
        return;
    }

    tempfile.open("tempfile1.dat", ios::out | ios::binary | ios::trunc); 
    if (!tempfile.is_open()) {
        cerr << "Error opening tempfile1.dat" << endl;
        fh.close();
        return;
    }

    
    while (getline(fh, line)) {           // Process each book record
        size_t pos = line.find(bookno);
        if (pos != string::npos) { // Found the book to update
            size_t lastComma = line.rfind(',');
            int quantity = stoi(line.substr(lastComma + 1));
            quantity++; // Increment the quantity
            line.replace(lastComma + 1, string::npos, to_string(quantity));
            cout << "Updated quantity for book ID " << bookno << ": " << quantity << endl;
        }
        tempfile << line << endl; // Write to temporary books file
    }

    fh.close();
    tempfile.close();

    
    remove("booksagain.dat");              // Replace the original books file
    rename("tempfile1.dat", "booksagain.dat");
}


    string borrowbook() {
    string name;
    char ch;
    fstream tempfile;

    cout << "Enter name of the book you want to borrow: ";
    cin.ignore();
    getline(cin, name);
    name=tolowercase(name);

    string bookLine = findbook(name); // Use findbook1 to locate the book

    if (bookLine.empty()) {
        cout << "Book not found." << endl;
        return "";
    }

    
    int pos1 = bookLine.find(',');           //to find quaqntity of book
    int pos2 = bookLine.find(',', pos1 + 1);
    int pos3 = bookLine.find(',', pos2 + 1);

    int quantity = stoi(bookLine.substr(pos3 + 1));
    if (quantity <= 0) {
        cout << "Book is currently out of stock." << endl;
        return "";
    }

    cout << "Book found: " << bookLine << endl;
    cout << "Do you want to borrow this book? (y/n): ";
    cin >> ch;

    if (ch == 'y') {
        tempfile.open("tempfile1.dat", ios::in | ios::out | ios::binary | ios::trunc);
        if (!tempfile.is_open()) {
            cerr << "Error opening temp file" << endl;
            return "";
        }

        fh.open("booksagain.dat", ios::in | ios::binary);
        if (!fh.is_open()) {
            cerr << "Error opening file for reading" << endl;
            tempfile.close();
            return "";
        }

        
        string line;                 // Update books file with new quantity
        while (getline(fh, line)) {
            if (line == bookLine) {
                quantity--;
                line.replace(pos3 + 1, bookLine.size() - pos3 - 1, to_string(quantity));
            }
            tempfile << line << endl;
        }

        fh.close();
        tempfile.close();

        remove("booksagain.dat");
        rename("tempfile1.dat", "booksagain.dat");

        cout << "Book borrowed successfully." << endl;
        return bookLine.substr(pos2 + 1, pos3 - pos2 - 1); 
    } else {
        cout << "Returning to menu..." << endl;
        return "";
    }
}
    void borrowbook2(){                    //Function so student can borrow book
        string line1="",line2="",line3="";
        int valid;
        bool yes=false;
        fh2.open("studentdetails.dat",ios::in|ios::out|ios::binary);
        if(!fh2.is_open()){
            cerr << "Error opening file studentdetails" << endl;
        }
        
        
        
        fstream tempstufile;
        tempstufile.open("tempstufile1.dat",ios::in|ios::out|ios::binary|ios::trunc);    
         while(getline(fh2,line1)){
            
            int pos=line1.find(tempstudentid);
            
            if(pos!=std::string::npos){
                yes=true;
            int pos0=line1.rfind(',');
            valid=stoi(line1.substr(pos0+1));       //to make sure student does not have a book already issued
            if(valid==0){
            line2=borrowbook();
            int pos2=line1.find(',',pos);
            
            int pos3=line1.find(',',pos2+1);
            
            line1.replace(pos3+1,line2.length(),line2);
            }
            }
            tempstufile<<line1<<endl;
         }
         fh2.close();
         tempstufile.close();
         remove("studentdetails.dat");
         rename("tempstufile1.dat","studentdetails.dat");
         if(valid!=0){
            cout<<"You already have one book issued. Please return it before borrowing another book."<<endl;
         }

        }
};


int main(){             //main function
    administrator a;
    student s;
    int choice1;
    while(choice1!=3){          //main menu
    cout<<"Welcome!"<<endl<<"if you are student type 1"<<endl<<" if you are administrator type 2"<<endl<<"type 3 to exit";
    cin>>choice1;
    switch(choice1){
        case 1:{
            
            s.studentmenu();
            break;}
        case 2:{
           
            a.administratormenu();
            break;}
        case 3:
            cout<<"Exiting..."<<endl;
            break;
        default:
            cout<<"Invalid choice";
    }}
    

    
} 