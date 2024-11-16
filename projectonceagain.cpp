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


string findbook(string name) {
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


 
void deletebook() {
    string deline, line;
    fstream tempfile;
    bool found = false;

    cout << "Enter the name of the book to delete: ";
    cin.ignore();
    getline(cin, deline);

    // Check if the book exists
    fh.close();
    fh.clear();
    if (findbook(deline).empty()) {
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
    tempfile.open("temp.dat", ios::out | ios::binary);
    if (!tempfile.is_open()) {
        cerr << "Error opening temporary file" << endl;
        fh.close();
        return;
    }

    // Read and write lines, excluding the one to be deleted
    while (getline(fh, line)) {
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

void deletestudent(){
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
    tempstufile.open("tempstu.dat",ios::out|ios::binary|ios::trunc);
    if(!tempstufile.is_open()){
        cerr<<"Error opening tempstu file";
        return;
    }
   

    while(getline(fh2,string2)){
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
    if(found){
        cout<<"Student deleted successfully";
       
    remove("studentdetails.dat");
    rename("tempstu.dat","studentdetails.dat");
    }
    else{
        cout<<"Student not found";
        remove("tempstu.dat");
    }
    

   
}

void modifyquantity(){
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

class student:public administrator{
    public:
    string tempstudentid;
    void studentmenu(){
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

    void returnbook() {
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
    while (getline(fh2, line)) {
        size_t pos = line.find(tempstudentid);
        if (pos != string::npos) { // Found student record
            size_t lastComma = line.rfind(',');
            bookno = line.substr(lastComma + 1);

            if (bookno != "0") { // Student has borrowed a book
                cout << "Returning book with ID: " << bookno << endl;
                line.replace(lastComma + 1, bookno.length(), "0");
                bookReturned = true;
            } else {
                cout << "You have not borrowed any books." << endl;
            }
        }
        tempstufile << line << endl; // Write to temporary student file
    }

    fh2.close();
    tempstufile.close();

    // Replace the original student details file
    remove("studentdetails.dat");
    rename("tempstufile1.dat", "studentdetails.dat");

    if (!bookReturned) {
        return; // Exit if no book was returned
    }

    // Open the books file to update the quantity
    fh.open("booksagain.dat", ios::in | ios::binary);
    if (!fh.is_open()) {
        cerr << "Error opening booksagain.dat" << endl;
        return;
    }

    // Create a temporary file for books
    tempfile.open("tempfile1.dat", ios::out | ios::binary | ios::trunc);
    if (!tempfile.is_open()) {
        cerr << "Error opening tempfile1.dat" << endl;
        fh.close();
        return;
    }

    // Process each book record
    while (getline(fh, line)) {
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

    // Replace the original books file
    remove("booksagain.dat");
    rename("tempfile1.dat", "booksagain.dat");
}


    string borrowbook() {
    string name;
    char ch;
    fstream tempfile;

    cout << "Enter name of the book you want to borrow: ";
    cin.ignore();
    getline(cin, name);

    string bookLine = findbook(name); // Use findbook1 to locate the book

    if (bookLine.empty()) {
        cout << "Book not found." << endl;
        return "";
    }

    // Parse the found line for details
    int pos1 = bookLine.find(',');
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

        // Update book file
        string line;
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
        return bookLine.substr(pos2 + 1, pos3 - pos2 - 1); // Return book number
    } else {
        cout << "Returning to menu..." << endl;
        return "";
    }
}
    void borrowbook2(){
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
            valid=stoi(line1.substr(pos0+1));
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


int main(){
    administrator a;
    student s;
    int choice1;
    while(choice1!=3){
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