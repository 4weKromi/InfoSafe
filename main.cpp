#include "head.h"

class ProgramLoop: public Interface, public FileOperate{
	public:
	ProgramLoop(){
		verify();
	}
	int flow(){
			while(true){
				int pick=options();
				if(pick==1){
					createDb();
				}
				else if(pick==2){
					char str[]="Hello";
					char str2[]="Awe";
					enText(str,str2);
					deText();
				}
				else if(pick==3){
					currentDb();
				}
				else if(pick==4){
					cout<<" 4 selected"<<endl;
				}
				else if(pick==5){
					cout<<" 5 selected"<<endl;
				}
				else if(pick==6){
					changePass();
				}
				else if(pick==7){
					changeDb();
				}
				else if(pick==8){
					cout<<" Bye "<<endl;
					break;
				}
			}
		return 0;
	}
};

int main(int argc, char **argv){
	cout<<" ";
	ProgramLoop pl;
	pl.flow();
	return 0;
}
