#include "head.h"
#include <limits>

Interface::options(){
	int opt;
	cout<<"\n\n 1 Add \t\tAppend Mode\n\n 2 [empty]\t[empty]\n\n 3 View \tIndex";
	cout<<"\n\n 4 View \tbeg-to-eof\n\n 5 Check\tCurrent Database\n\n 6 Create\tDatabase";
	cout<<"\n\n 7 Set \t\tDatabases\n\n 8 Change \tApp Password\n\n 9 Reset \tApp\n\n 0 Quit";
	cout<<"\n\n Select 0-9 : ";
	cin>>opt;
	if(cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<" Select 0-9 !";
		return 0;
	}
	switch(opt){
		case 1:{
			cin.ignore(1);
			flagWrite=0;
			cout<<"\n Enter an Entity [<32 chars]: ";
			cin.getline(buffEntity,32);
			cout<<"\n Enter "<<buffEntity<<" Decription [<480 chars]: ";
			cin.getline(buffDesc,480);
			cout<<"\n Save? Y/N : ";
			cin>>choice;
			if(choice=='Y'||choice=='y'){
				flagWrite=1;
				cout<<"\n Saved !";
			}
			else if(choice=='N'||choice=='n'){
				flagWrite=0;
				cout<<"\n Discarded !";
			}
			else
				cout<<"\n Wrong Choice !";
			return 1;}
		case 2:{
			return 2;
		}
		case 3:{return 3;}
		case 4:{return 4;}
		case 5:{return 5;}
		case 6:{return 6;}
		case 7:{return 7;}
		case 8:{return 8;}
		case 9:{return 9;}
		case 0:{return 0;}
		default:{
			cout<<" Select Another !"<<endl;
		}
	}
	return 0;
}	
