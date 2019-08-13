/* https://github.com/4weKromi */
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
					if(flagWrite==1)
					enText(buffEntity,buffDesc);
					writeFile();
				}
				else if(pick==2){
					cout<<"\n 2 Selected \n";
				}
				else if(pick==3){
					loadFile(1);/* Decrypts Using Index*/		
				}
				else if(pick==4){
					loadFile(0);/* Decrypts all*/
				}
				else if(pick==5){
					currentDb();/* Current DB Details*/
				}
				else if(pick==6){
					createDb();/* Creates new DB file*/
				}
				else if(pick==7){
					changeDb();/* Changes Current DB */
				}
				else if(pick==8){
					changePass();/* Changes Key */
				}
				else if(pick==9){
					reset();/* Reset apps and quit*/
					break;
				}
				else if(pick==0){
					cout<<"\n\n Bye !!\n"<<endl;
					break;/* Breaks Loop - Quits */
				}
			}
		return 0;
	}
};

int main(int argc, char **argv){
	ProgramLoop pl;
	pl.flow();
	return 0;
}
