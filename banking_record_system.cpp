#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

class account_query{
    private:
        char account_number[20];
        char firstname[10];
        char lastname[10];
        float total_balance;
    public:
        void read_data();
        void write_record();
        void show_record();
        void read_record();
        void search_record();
        void edit_record();
        void delete_record();
};

void account_query :: read_data(){
    cout<<"\n Enter Account Number: ";
    cin>>account_number;
    cout<<"\n Enter First Name: ";
    cin>>firstname;
    cout<<"\n Enter Last Name: ";
    cin>>lastname;
    cout<<"\n Enter balance: ";
    cin>>total_balance;
    cout<<endl;
}
void account_query :: write_record(){
    ofstream outfile;
    outfile.open("record.bank",ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this),sizeof(*this)); //to convert one pointer to any other pointer type
    outfile.close();

}
void account_query :: show_record(){
    cout<<"Account Number: "<<account_number<<endl;
    cout<<"First Name: "<<firstname<<endl;
    cout<<"Last Name: "<<lastname<<endl;
    cout<<"Current Balance: "<<total_balance<<endl;
    cout<<"---------------------------------"<<endl;
}
void account_query :: read_record(){
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile){
        cout<<"Error in opening! File not found !"<<endl;
        return;
    }
    cout<<"\n *** Data From File ***"<<endl;
    while (!infile.eof()){
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))){
            show_record();
        }
    }
    infile.close();
}
void account_query :: search_record(){
    int n;
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile){
        cout<<"Error in opening! File not found !"<<endl;
        return;
    }
    infile.seekg(0,ios::end);                   //to get arbitrary position of the file 
    int count = infile.tellg()/sizeof(*this);   //to get position of pointer
    cout<<"\n There are "<<count<<" records in the file";
    cout<<"\n Enter record number to search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this),sizeof(*this));
    show_record();
}
void account_query :: edit_record(){
    int n;
    fstream iofile;
    iofile.open("record.bank",ios::in|ios::binary);
    if(!iofile){
        cout<<"Errorr in opening! File not found !"<<endl;
        return;
    }
    iofile.seekg(0,ios::end);
    int count = iofile.tellg()/sizeof(*this); 
    cout<<"\n There are "<<count<<" records in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this),sizeof(*this));
    cout<<"Record "<< n <<" has following data: "<<endl;
    show_record();
    iofile.close();
    iofile.open("record.bank",ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\n Enter data to modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this),sizeof(*this));
}
void account_query :: delete_record(){
    int n;
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile){
        cout<<"Errorr in opening! File not found !"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this); 
    cout<<"\n There are"<<count<<" records in the file";
    cout<<"\n Enter record Number to delete: ";
    cin>>n;
    fstream tempfile;
    tempfile.open("tempfile.bank",ios::out|ios::binary);
    infile.seekg(0);
    for(int i =0;i<count;i++){
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1)){
            continue;
        }
        tempfile.write(reinterpret_cast<char*>(this),sizeof(*this));
    }
    infile.close();
    tempfile.close();
    remove("record.bank");
    rename("tempfile.bank","record.bank");
}

int main(){
    account_query A;
    int choice;
    cout<<"***Banking Account Information System***"<<endl;
    while(true){
        cout<<"Select one option to proceed:";
        cout<<"\n 1> Add record to file";
        cout<<"\n 2> Show record from file";
        cout<<"\n 3> Search record from file";
        cout<<"\n 4> Update record in file";
        cout<<"\n 5> Delete record from file";
        cout<<"\n 6> Exit";
        cout<<"\n Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            A.write_record();
            break;
        case 2:
            A.read_record();
            break;
        case 3:
            A.search_record();
            break;
        case 4:
            A.edit_record();
            break;
        case 5:
            A.delete_record();
            break;
        case 6:
            exit(0);
        
        default:
            cout<<"\n Enter correct choice: ";
            // exit(0);
        }
    }
    system("pause");
    return 0;
}

