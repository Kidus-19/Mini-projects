#include<iostream>
#include<string>
#include<string.h>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){

string names[10];
char tik1[3],*p=tik1;
int tik[4],*q=tik,trip[5],classs[5],dd[5],aa[5],choice=0,ticket=0,c=0,d=0;
bool bol=false;

cout<<"------------------------------Hello and Welcome to our Online Flight Booking System-------------------------------"<<endl<<endl;;


do{
    cout<<"Press 1 for Booking"<<endl;
    cout<<"Press 0 to Exit"<<endl;
    cin>>choice;
    if(choice!=1&&choice!=0){
        cout<<"Invalid Entry, please Try again"<<endl;
    }
}
while(choice!=1&&choice!=0);



while(choice){   //he we used choice in case the user wants to quit from the start


    do{
        cout<<"How many tickets do you want"<<endl;
        cin>>ticket;
        if(ticket<=0){
            cout<<"Invalid Entry, please Try again"<<endl;
        }
        else if(ticket>5){
            cout<<"You can't book more than 5 tickets "<<endl;
        }
    }
    while(ticket<=0||ticket>5);

    for(int n=0;n<ticket;n++){

        system("cls");
        cin.ignore(INT_MAX,'\n');//To eliminate any new line inside the buffer
        cout<<"First and Last Name of Passenger number "<<n+1<<endl;
        getline(cin,names[n]);

        do{
            cout<<"Press 1 for One way or Press 2 for Round trip"<<endl;
            cin>>trip[n];
            bol=false;
            if(trip[n]!=1&&trip[n]!=2){
                cout<<"Invalid Entry, please Try again"<<endl;
                bol=true;
            }
        }
        while(bol);


        switch(trip[n]){
            case 1:       //for one time trip
                do{
                    cout<<"Enter Departure day for the october month"<<endl;
                    cin>>dd[n];
                    bol=false;
                    if(dd[n]<0||dd[n]>31){
                        cout<<"Invalid Entry, please Try again"<<endl;
                        bol=true;
                    }
                }
                while(bol);
                break;

            case 2:     //for round trip
                do{
                    cout<<"Enter Departure date for the October month"<<endl;
                    cin>>dd[n];

                    cout<<"Enter Arrival date for the October month"<<endl;
                    cin>>aa[n];
                    bol=false;

                    if(dd[n]<0||dd[n]>31||aa[n]<0||aa[n]>31){
                        cout<<"Invalid Entry, please Try again"<<endl;
                        bol=true;
                    }

                    else if(aa[n]<dd[n]){
                        cout<<"Arrival date cant be before departure date "<<endl;
                        bol=true;
                    }
                }
                while(bol);
                break;
        }//switch ends here.

        do{
            cout<<"Press 1 for Economy class or Press 2 for Business class"<<endl;
            cin>>classs[n];
            bol=false;
            if(classs[n]!=1&&classs[n]!=2){
                cout<<"Invalid Entry, please Try again"<<endl;
                bol=true;
            }
        }
        while(bol);

    }//for loop ends here

    system("cls");
    srand(time(0));
    for(int j=0;j<ticket;j++){   //Takes individual information for each ticket
        cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"Passenger :"<<names[j]<<'\t';
        if(classs[j]==1){
            cout<<"//Economy class"<<endl;
        }
        else if(classs[j]==2){
            cout<<"//Business class"<<endl;;
        }
        if(trip[j]==1){//one way trip
            cout<<"One way trip"<<'\t';
            cout<<"//Departure Date : October "<<dd[j]<<endl;
        }
        else if(trip[j]==2){  //for round trip
            cout<<"Round trip"<<'\t';
            cout<<"//Departure Date : October "<<dd[j]<<endl;
            cout<<"//Arrival Date : October "<<aa[j]<<endl;
        }
        // TICKET NUMBER USING RANDOM FUNCTION
         cout<<"Ticket ID : ";


         for(int i=0;i<3;i++){
            *(p+i)='A'+rand()%26;
            cout<<tik1[i];
        }
         for(int i=0;i<4;i++){
            *(q+i)=rand()%9;
            cout<<tik[i];
        }
        cout<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl<<endl;
    }//for loop ends here.
    choice=0;   //After everything is done we want the program to end and 0 means false.
}//while loop ends here
cout<<"--------------------------------------------Thank you--------------------------------------------------------"<<endl;
system("pause");
return 0;
}


