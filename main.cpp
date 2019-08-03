#include "head.h"

class ProgramLoop: public ChooseSet, public Interface{
	public:
	ProgramLoop(){
		verify();
		setFile();
	}
	int flow(){
			while(true){
				int pick=options();
				if(pick==1){
					cout<<" 1 selected"<<endl;
				}
				else if(pick==2){
					cout<<" 2 selected"<<endl;
				}
				else if(pick==3){
					cout<<" 3 selected"<<endl;
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
					setFile();
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
