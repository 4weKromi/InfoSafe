#include "head.h"
#include "hash/md5.h"
#include <cstring>
#include <cstdio>

Authenticate::verify(){
	char shash[64];
	char pcompare[64];
	char temp[64];
	char ch;
	int index=0;
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open(".hash");
		if(fileIn){
			while(fileIn){
				fileIn.get(ch);
				if(ch=='>'){
					fileIn.get(ch);
					while(ch!=';'){
						temp[index]=ch;
						fileIn.get(ch);
						index++;
					}
				}
			}
			fileIn.close();
			while(true){
				cout<<"\n Enter pass : ";
				cin>>pcompare;
				string str=md5(pcompare);
				int n = str.length(); 
				char arr[n+1];
				unsigned int i;
				for (i = 0; i < sizeof(arr); i++) { 
					arr[i] = str[i]; 
				}
				if(strcmp(temp,arr)==0){
					cout<<" Okay !!";
					return 0;
				}
				else
					cout<<" Try Again ! ";
			}
		}else{
			fileOut.open(".hash");
			cout<<" Enter new pass : ";
			gets(shash);
			fileOut<<"hash>"<<md5(shash)<<";";
			fileOut.close();
			cout<<" New Pass : "<<shash<<endl;
			cout<<" Pass hash : "<<md5(shash)<<endl;
		}
	return 0;
}
Authenticate::changePass(){
	char shash[64];
	ofstream fileOut;
	if (remove(".hash")==0){
		fileOut.open(".hash");
		cout<<" Enter new pass : ";
		cin>>shash;
		fileOut<<"hash>"<<md5(shash)<<";";
		fileOut.close();
		cout<<" Pass Changed : "<<shash<<endl;
		cout<<" Pass hash : "<<md5(shash)<<endl;
	}
	else{
		cout<<" Failed to change pass";
	}
	return 0;
}



