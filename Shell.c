main(){
	char line[80];
	char filen[8];
	char buff[13312];
	char* command[4];
	int index=0;
	command[0]="help";
	command[1]="type";
	command[2]="exec";
	command[3]="files";
	command[4]='\0';
	syscall(0,"SHELL>",0);
	syscall(1,line,0);
	filen[0]='\0';
	filen[1]='\0';
	filen[2]='\0';
	filen[3]='\0';
	filen[4]='\0';
	filen[5]='\0';
	filen[6]='\0';

	while(command[index]!='\0'){
		int l=0;
		int trufal =1;		
		while(command[index][l]!='\0'){
			if(command[index][l]==line[l]){
				trufal=1;
			}
			else{
				trufal=0;
				break;
			}
			l++;
		}
		if(trufal==1){
			if(index==0){
				int g=1;
				while(command[g]!='\0'){
					syscall(0,command[g],0);
					syscall(0," ",0);
					g++;			
				}
				syscall(0,"\r\n",0);
				syscall(5,0,0);			
			}
			else if(index==1){
				//type 01234[5]
				filen[0]=line[5];
				filen[1]=line[6];
				filen[2]=line[7];
				filen[3]=line[8];
				filen[4]=line[9];
				filen[5]=line[10];
				syscall(3,filen,buff);
				syscall(0,buff,0);
				syscall(0,"\r\n",0);
				syscall(5,0,0);
			}
			else if(index==2){
				filen[0]=line[5];
				filen[1]=line[6];
				filen[2]=line[7];
				filen[3]=line[8];
				filen[4]=line[9];
				filen[5]=line[10];
				syscall(4,filen,0);			
				syscall(5,0,0);
			}
			else if (index==3){
				syscall(7,0,0);
				syscall(0,"\r\n",0);
				syscall(5,0,0);		
			}
			else if(index== 4){
				syscall(0,"Command Not Found\r\n",0);
				syscall(5,0,0);
	
			}	
			
		}
		index++;
	}					
	syscall(5,0,0);
}	
