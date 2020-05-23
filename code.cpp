//author: @mansidhall2912@gmail.com
#include<fstream>
#include<iostream>
#include<conio.h>      
#include<windows.h>
#include<string.h>
//#include<bits/stdc++.h>
using namespace std;
class medicine{                                
    char name[40];
    int med_id;
    float price;
    int choice;
    public:
        void getdata(){
            cout<<"\nENTER MEDICINE ID: "; cin>>med_id;
            cout<<"\nENTER MEDICINE NAME: "; cin>>name;
            cout<<"\nENTER PRICE: "; cin>>price;
        }
        void showdata(){
            cout<<"\t"<<med_id<<"\t|\t";
            cout<<name<<"\t|\t";
            cout<<price<<"\t\t";
        }
        void getmodifieddata(){
            char nm[40];
            int m_id;
            float prc;
            cout<<"\nENTER NEW DETAILS: "<<endl;
            cout<<"NEW ID:(enter '1' to retain old one)\n";
            cin>>m_id;
            cout<<"NEW NAME:(enter '.' to retain old one)\n";
            cin>>nm;
            cout<<"NEW PRC:(enter '1' to retain old one)\n";
            cin>>prc;
            if(strcmp(nm,".")!=0){
                strcpy(name,nm);
            }
            else{
                strcpy(nm,name);
            }
            if(m_id==1){
                m_id=med_id;
            }
            else{
                med_id=m_id;
            }
            if(prc==1){
                prc=price;
            }
            else{
                price=prc;
            }
        }
        int med(){
            return med_id;
        }
        int adm(){
            cout<<"1.PRESS 1 TO DELETE RECORD.\n2.PRESS 2 TO INSERT NEW RECORD.\n3.PRESS 3 TO MODIFY OLD RECORD.\n4.PRESS 4 TO SEARCH RECORD.\n5.PRESS 5 TO DISPLAY MEDICINES RECORD.\n6.PRESS 6 TO GO TO RECYCLE BIN.\n\n";
            cout<<"CHOICE: ";
            cin>>choice;
            return choice;
        }
}m;
int login(){
    int a=0,i=0,rt=1;
    char user[10],ch=' ',pwd[8],code[10];
    char uname[10]="admin";
    char psw[8]="clowl78";
    do{
    cout<<"\nENTER USERNAME: ";
    cin>>user;
    cout<<"\nENTER PASSWORD: ";
    while(i<8){
        pwd[i]=getch();
        ch=pwd[i];
        if(ch==13){break;
        }
        else{
            cout<<"*";
            i++;
        }
    }
    pwd[i]='\0';
    i=0;
    if(strcmp(user,uname)==0&&strcmp(pwd,psw)==0){
        cout<<"\n\t\tLOGIN SUCCESSFULL. \n";
        cout<<"\nPRESS ANY KEY TO CONTINUE.";
        getch();
        break;
    }
    else{
        cout<<"\n\tOOPS! SOMETHING WENT WRONG, TRY AGAIN. PRESS ANY KEY TO CONTINUE.\n";
        a++;
        getch();
    }
    }
    while(a<=2);
    if(a>2){
        cout<<"\n\nYOU HAVE ENTERED WRONG USERNAME OR PASSWORD MORE THAN TWO TIMES!\nPRESS ANY KEY TO EXIT.";
        getch();
        return rt;
    }
    system("cls");
}
void mainref(){
    ofstream fout;
    fout.open("medi.txt",ios::out|ios::app);
    fout.close();
    ifstream fin;
    fin.open("medi.txt",ios::in);
    cout<<"\t\t\t MEDICINE RECORD"<<endl<<endl;
    cout<<"\t\t\t-----------------"<<endl<<endl;
    cout<<"\t"<<"ID\t\tNAME\t\tPRICE\t\t"<<endl<<endl;
    while(fin.read((char*)&m,sizeof(m))){
        m.showdata();
        cout<<endl;
    }
    fin.close();
   
}
void search(){
    int ser;
    char found='n';
    cout<<"\n\nENTER MEDICINE ID TO BE SEARCHED FOR:"<<endl<<endl;
    cin>>ser;
    ifstream f;
    f.open("medi.txt",ios::binary|ios::in);
    f.seekg(0);
    while(f.read((char*)&m,sizeof(m))){
        if(ser==m.med()){
            cout<<"\n\t DETAILS OF MEDICINE WITH ID "<<ser<<":"<<endl;
            cout<<"\t"<<"ID\t\tNAME\t\tPRICE\t\t"<<endl<<endl;
            m.showdata();
            cout<<endl<<endl<<endl;
            found='y';
            //exit(1);
        }  
    }
    if(found=='n'){
        cout<<"MEDICINE NOT FOUND!"<<endl;
    }
    f.close();
}
   
void insertnew(){
    ofstream fout;
    fout.open("medi.txt",ios::app|ios::out|ios::binary);
    m.getdata();
    fout.write((char*)&m,sizeof(m));
    fout.close();
}
 
void modify(){
    int mid;
    long pos;
    char found='n';
    fstream fio("medi.txt",ios::in|ios::out);
    cout<<"ENTER MEDICINE ID WHOSE RECORD IS TO MODIFIED:\n";
    cin>>mid;
    while(fio.read((char*)&m,sizeof(m))){
       
        if(m.med()==mid){
            cout<<"OLD RECORD OF ID "<<mid<<endl;
            cout<<"\t"<<"ID\t\tNAME\t\tPRICE\t\t"<<endl<<endl;
            m.showdata();
            int pos=fio.tellg()-sizeof(m);
            fio.seekg(pos,ios::beg);
            m.getmodifieddata();
            //fio.seekg(sizeof(m),ios::cur);
            fio.write((char*)&m,sizeof(m));
            found='y';
            break;
        }
    }
    if(found=='n'){
        cout<<"MEDICINE WITH ID "<<mid<<" NOT FOUND!!\n";
    }
    fio.seekg(0);
    fio.close();
}
 
void delrecord(){
    ifstream pf("medi.txt",ios::in);
    ofstream nf("temp.txt",ios::out|ios::app);
    ofstream rf("rcb.txt",ios::out|ios::app);
    medicine m2;
    int mdid;
    char found='t', confirm='y';
    cout<<"\nENTER MEDICINE ID TO DELETE ITS RECORD\n";
    cin>>mdid;
    cin.ignore();
    while(pf.read((char*)&m2,sizeof(m2))){
       
        if(m2.med()==mdid){
            cout<<"\t"<<"ID\t\tNAME\t\tPRICE\t\t"<<endl<<endl;
            m2.showdata();
            found='f';
            cout<<"\nARE YOU SURE YOU WANT TO DELETE THIS RECORD?(y/n)\n\t";
            cin>>confirm;
            // int pos=pf.tellg();
            // pf.seekg(pos);
            rf.write((char*)&m,sizeof(m));
            rf.close();
            if(confirm=='n'){
                nf.write((char*)&m2,sizeof(m2));
            }
        }else{
            nf.write((char*)&m2,sizeof(m2));
        }
    }
    if(found=='t'){
        cout<<"MEDICINE WITH ID "<<mdid<<" NOT FOUND!!\n\n";
    }
    pf.close();
    nf.close();
    remove("medi.txt");
    rename("temp.txt","medi.txt");
}
 
void recyclebin(){
    ifstream rf("rcb.txt",ios::in);
    cout<<"\t\t\tDELETED RECORDS\n\n";
    cout<<"\t"<<"ID\t\tNAME\t\tPRICE\t\t"<<endl<<endl;
    while(rf.read((char*)&m,sizeof(m))){
        m.showdata();
        cout<<"\n";
    }
    rf.close();
}
 
int menu(char yes='y'){
        //medicine m;
    switch(m.adm()){
        case 1: delrecord();
        break;
        case 2: insertnew();
        break;
        case 3: modify();
        break;
        case 4: search();
        break;
        case 5: mainref();
        break;
        case 6: recyclebin();
        break;
        default: cout<<"NO MATCH FOUND!\n";
        break;
    }
    cout<<"GO TO MENU?(y/n)\n";
    cin>>yes;
    if(yes=='y'){
        system("cls");
        menu('y');
    }
}
 
int main(){
    if(login()!=1){
    	cout<<"\t\tWELCOME  TO  MEDICINES  RECORD  MANAGEMENT  SYSTEM.\n\n\n";
        menu();
    }  
    return 0;
}
