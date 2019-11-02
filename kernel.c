void printString(char*);
void readstring(char*);
void printChar(char) ;
void readsector(char*,int);
void readfile(char*,char*,int*);
void handleInterrupt21(int , int , int, int);
void executeProgram(char*);
void terminate();
void main(){
		char buffer[13312];
		char line[80];
		int sectorsRead;
		char shellname[6];
		shellname[0]='s';
		shellname[1]='h';
		shellname[2]='e';
		shellname[3]='l';
		shellname[4]='l';
		shellname[5]='\0';		
		makeInterrupt21();
		interrupt(0x21, 4, shellname, 0, 0);
		//interrupt(0x21,0,"Enter A Line> ",0,0);		
		//interrupt(0x21,1,line,0,0);
		//interrupt(0x21,4,line,0,0);
		//interrupt(0x21, 0,"\r\n", 0, 0);		
		//interrupt(0x21, 3, "messag", buffer, &sectorsRead);
		//if(sectorsRead > 0){			
		//	interrupt(0x21, 0, buffer, 0, 0);   /*print out the file*/ 
		//}
		//else{
		//interrupt(0x21, 0, "messag not found\r\n", 0, 0);
		//} 		
		interrupt(0x21,5,0,0,0);
}
void terminate(){
	char shellname[6];
	shellname[0]='s';
	shellname[1]='h';
	shellname[2]='e';
	shellname[3]='l';
	shellname[4]='l';
	shellname[5]='\0';
	interrupt(0x21, 4, shellname, 0, 0);
	while(1);
}
void executeProgram(char* name){
	int i=0x0;
	int l=0;
	int sectorsRead;
	char buffer[13312];
	interrupt(0x21, 3, name, buffer, &sectorsRead);	
	if (sectorsRead > 0){		
		while( l!=13312){
			putInMemory(0x2000,i,buffer[l]);
			i++;	
			l++;
		}
		launchProgram(0x2000);
	}
	else{
		interrupt(0x21, 0, "File not found\r\n", 0, 0);
	} 
}
void readstring(char* line)
{
	int i=0;
	while(1)
	{
		char c= interrupt(0x16, 0, 0, 0, 0);
		if(c==0xd){
			interrupt(0x10,0xe*256+0xa,0,0,0);
			interrupt(0x10,0xe*256+0xd,0,0,0);
			line[i]=0x0;	
			break;
		}
		else if(c!=0x8 && i!=80){
			line[i]=c;
			interrupt(0x10,0xe*256+c,0,0,0);
			i++;	
		}	
		else if(c==0x8 && i!=0)
		{
			interrupt(0x10,0xe*256+c,0,0,0);
			interrupt(0x10,0xe*256+0x20,0,0,0);
			interrupt(0x10,0xe*256+c,0,0,0);			
			i--;
		}	
	}
}
void printChar(char c){
	interrupt(0x10, 0xe*256+c, 0, 0, 0);
}
void printString(char* line){
	int i=0;	
	while(line[i]!='\0'){		
		interrupt(0x10, 0xe*256+line[i], 0, 0, 0);
		i++;
	}
}
void readfile(char* Name, char* buffer, int* sr){
	char dir[512];
	int p=0;
	*sr=0;
	interrupt(0x21, 2, dir,2, 0);	
	for(p; 32*p<=512;p++){
		if(dir[32*p+0] == Name[0] && dir[32*p+1] == Name[1] && dir[32*p+2] == Name[2] && dir[32*p+3] == Name[3] && dir[32*p+4] == Name[4] && dir[32*p+5] == Name[5]){
			*sr = 1;		
			interrupt(0x21, 2, buffer, dir[32*p+6], 0);
		}
		else{
			interrupt(0x21, 0, "", 0, 0);
			}
	}
}
void handleInterrupt21(int ax, int bx, int cx, int dx){
	if (ax==0){
	printString(bx);	
	}
	else if (ax==1){
	readstring(bx);
	}
	else if (ax==2){
	readsector(bx,cx);
	}
	else if (ax==3){
	readfile(bx,cx,dx);	 	
	}
	else if(ax==4){
	executeProgram(bx);
	}
	else if(ax==5){
	terminate();	
	}
	else if(ax==6){
	printChar(bx);	
	}	
	else{
	printChar(7); 	
	}
}
void readsector(char* buffer,int sector){
	interrupt(0x13,2*256+1,buffer,0*256+sector+1,0*256+0x80);
}
