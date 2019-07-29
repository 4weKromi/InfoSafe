#include "head"

DiskOperate::setDbFile(){
	char filename[64];
	char ch;
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open("setApp.conf");
		if(fileIn){
			cout<<" setApp.conf Available"<<endl;
			while(fileIn){
				fileIn.get(ch);
				if(ch=='>'){
					while(ch!=';'){
						cout<<ch;
						fileIn.get(ch);
					}
				}
			}
			cout<<" loaded "<<endl;
			fileIn.close();
		}
		else{
			fileOut.open("setApp.conf");
			cout<<" Enter new Database name (Syntax: filename.ext) : ";
			gets(filename);
			fileOut<<"DB File>"<<filename<<";";
			fileOut.close();
			cout<<"Database Created : "<<filename<<endl;
		}
		return 0;
	}
DiskOperate::changeDbFile(){
	char filename[64];
	char ch;
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open("setApp.conf");
		if(fileIn){
		cout<<" Current DB : ";
		while(fileIn){
			fileIn.get(ch);
			if(ch=='>'){
				while(ch!=';'){
					cout<<ch;
					fileIn.get(ch);
					}
				}
			}
			fileIn.close();
			fileOut.open("setApp.conf");
			cout<<"\n Enter Database name (Syntax: filename.ext) : ";
			cin>>filename;
			fileOut<<"DB File>"<<filename<<";";
			fileOut.close();
			cout<<"Database Changed to "<<filename<<endl;
		}
		else{
			cout<<" Sorry setApp.conf not found"<<endl;
			return 1;
		}
		return 0;
	}