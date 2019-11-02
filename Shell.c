main(){
	char line[80];
	char* command[4];
	int index=0;
	command[0]="help";
	command[1]="type";
	command[2]="exec";
	syscall(0,"SHELL>",0);
	syscall(1,line,0);
	syscall(0,"I get here\r\n",0);
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
				break;	
			}
			else if(index==1){
				syscall(0,"I PRINT TYPE\r\n",0);
				break;
			}
			else if(index== 3){
				syscall(0,"Command Not Found\r\n",0);
			}
		}

		index++;
	}				
	// exacutes line
	syscall(4,line,0);
	// returns to shell	
	syscall(5,0,0);
}	
