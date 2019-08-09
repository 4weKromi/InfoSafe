#include "head.h"
#include <limits>

Interface::options(){
	int opt;
	cout<<"\n\n 1 Create  \t_Database\n\n 2 Search\t_Strings\n\n 3 Check Current DB";
	cout<<"\n\n 4 Add   \t_Location \n\n 5 Delete\t_Strings\n\n 6 Change Pass\n\n 7 Set DB\n\n 8 Quit";
	cout<<"\n\n Select : ";
	cin>>opt;
	if(cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<" Select 1-8 !";
		return 0;
	}
	switch(opt){
		case 1:{return 1;}
		case 2:{return 2;}
		case 3:{return 3;}
		case 4:{return 4;}
		case 5:{return 5;}
		case 6:{return 6;}
		case 7:{return 7;}
		case 8:{return 8;}
		default:{
			cout<<" Select Another !"<<endl;
		}
	}
	return 0;
}	
