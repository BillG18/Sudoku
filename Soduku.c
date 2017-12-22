/*
 * Soduku.c
 *
 *  Created on: Mar 15, 2016
 *      Author: Billy
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//example solved sudoku array. solved sudoku board found on google, in the full prigram
//this would be imported from file and converted to integer array as seen here
int nextX;
int nextY;
int end = 0;
//int terminate = 0;
int sudoku[80];
int sudokuGrid[9][9];//initializes a 2d array which is comprised of 9 rows of 9
char fileName[50];

int open(char filename[]){//opens a sudoku array from file
	int i;
	int x=0;
	int y=0;
	int z;

	FILE *inputFile = fopen(filename, "r");//pointer to open file for reading

	char temp[2];//temporary storage for each grouping of numbers between spaces
	char temp2[80];//array to hold string values of all numbers

	while(!feof(inputFile)){//reads the input file until it is over
			fscanf(inputFile, "%s", temp);//reads the file until it encounters a space
			strcat(temp2, temp);//imports 3 new values into temp2
	}

	fclose(inputFile);
	for(i=0; i < 81; i++){
		z = (temp2[i] - '0');//converts all values in array temp2 into integers and puts them in "sudoku" array
		sudokuGrid[x][y] = z;
		if((i+1) % 9 == 0){
			y++;
		    x=0;
		}
		else{
			x++;
		}
	}
	return 0;
}

int is_row_valid(int sudoku[][9]){
	int numcount = 0;
	int i;
	int j;
	//row verification, iterates through each row and checks if the total is equal to that of the total of 1-9 which is 45
	for(j=0; j<9; j++){
		for (i =0; i < 9; i++){
			numcount = numcount + sudoku[i][j];
			if(((i+1)%9) == 0){//the end numbers will always cleanly divide by 9 so this is used to indicate the end of a row
				if(numcount != 45){
					return 0;
				}
				numcount = 0;
			}
		}
	}
	return 1;
}

int is_col_valid(int sudoku[][9]){
	//column verification, iterates through columns by adding 9 to the first position until through the whole column and then checks if total is equal to 45
	int numcount = 0;
		int i;
		int j;
		//row verification, iterates through each row and checks if the total is equal to that of the total of 1-9 which is 45
		for(j=0; j<9; j++){
			for (i =0; i < 9; i++){
				numcount = numcount + sudoku[j][i];
				if(((i+1)%9) == 0){//the end numbers will always cleanly divide by 9 so this is used to indicate the end of a row
					if(numcount != 45){
						return 0;
					}
					numcount = 0;
				}
			}
		}
	/*	int y=0;
		int z=0;
		int numcount = 0;
		for(z=0;z<9;z++){
			int q = z;
			for(y=0;y<9;y++){
				numcount = sudoku[q] + numcount;
				q=q+9;
			}
			if(numcount != 45){
				return 2;
			}
			else{
				numcount = 0;
			}
		}
		*/
	return 1;
}

int is_block_valid(int sudoku[][9]){
	//square verification, iterates through each square by iterating through three integers three times each group seperated by 6 spaces, checks the total of each square value to 45
	int blockX = 0;
	int blockY = 0;
	int a;
	int b;
	int c;
	int d;
	int numcount = 0;
	for(d=0;d<3;d++){
		for(a=0;a<3;a++){
			for(b=0;b<3;b++){
				for(c=0;c<3;c++){
					numcount = sudokuGrid[blockX+c][blockY]+numcount;
					if(c==2){
						blockY++;
					}
				}
			}
			if(numcount!=45){
				return 0;
			}
			numcount=0;
		}
		//cases to reset the starting value in the proper column after it has reached the bottom
		if(d==0){
			blockX=3;
			blockY=0;
		}
		if(d==1){
			blockX=6;
			blockY=0;
		}
	}
		return 1;
}

int verification(int sudoku[][9]){//if 1 returned the sudoku solution id verified, if any other value something is wrong (different return values could assist in locating the problem but could alos be standardized to all return "1" for failure
	if(is_row_valid(sudoku)==1){
		if(is_col_valid(sudoku)==1){
			if(is_block_valid(sudoku)==1){
				printf("Solution Verfified!\n");
				return 1;
			}
		}
	}
	printf("No solution found");//if the solution is unverified then it is not a solution
	return 0;
}
//checks for the next non inhabited cell by iterating through every non empty cell until a match is found all the while increasing x and y as needed
int nextEmpty(x, y){
	if(sudokuGrid[x][y]==0){
		nextX = x;
		nextY = y;
		return 1;
	}
	else{
		while(sudokuGrid[x][y]!=0){
			if((x+1)%9 != 0){
				x++;
			}
			else if((x+1)%9==0){
				x=0;
				y++;
			}
			if(y==9){
				end=1;//base case which is made true once all cells are filled and y becomes 9 (1 row above the 0-8 needed to fill sudoku)
				return 1;//ends while loop;
			}
		}
		nextX = x;
		nextY = y;
		return 1;
	}
	return 0;
}

//checks the row columns and bvlock inhabited by the cell called and if there is no instance of number 'a' yet it passes a value of 1 for true
int canSolve(int x, int y, int z){

	int blockX = ((x)/3 * 3);
	int blockY = ((y)/3 * 3);
	int b=0;
	int c=0;
	int d;

	for(d=0; d < 9; d++){
		//Column Check
		if(sudokuGrid[x][d] == z){
			return 0;
		}
		//Row Check
		if(sudokuGrid[d][y] == z){
			return 0;
		}
	}

	//Block Check
		for(b=0;b<3;b++){
			for(c=0;c<3;c++){
				if(sudokuGrid[blockX+c][blockY] == z){
					return 0;
				}
				if(c==2){
					blockY++;
				}
			}
		}
	return 1;
}

int solve(int x, int y){
	int a;
	if(end == 1){//base case, the nextEmpty value of 8,8 will iterate in a while loop until y becomes 9 triggering the end vlue to become true and ending the loop
		return 1;
	}
	for(a = 1; a<10; a++){//for the numbers 1-10 checks all other array positions with canSolve and assigns the one to the current cell before calling the function again
		if(canSolve(x,y,a) == 1){
			sudokuGrid[x][y] = a;
			nextEmpty(x,y);
			if(solve(nextX, nextY) == 1){
				return 1;
			}
			sudokuGrid[x][y] = 0;//If the initial a value is not a valid solutoon after other cells have passed
		}
	}
	return 0;
}

int toString(int sudokuArray[][9]){//prints array values based on the values of the 25 character long lines being even or odd
	int x;
	int y;
	int row=0;
	int col=0;

	printf("\n-------------------------\n");
	for(x=1;x<12;x++){
		if((x%4)==0){
			printf("|-------+-------+-------|\n");
			x++;
			}
		for(y=0;y<26;y++){
			if(y==25){
				printf("\n");
			}
			else if((y%8) == 0){
				printf("|");
			}
			else if((y%2)!=0){
				printf(" ");
			}
			else if((y%2)==0){
				if(sudokuArray[row][col] == 0){
					printf(".");
				}
				else{
					printf("%d",sudokuArray[row][col]);
				}
				if(row!=9){
					row++;
				}
				if(row==9){
					col++;
				    row=0;
				}
			}
		}
	}
	printf("-------------------------\n");
	return 0;
}


int output(){//output prints filename and converts sudoku array into string
	printf("%s", fileName);
	toString(sudokuGrid);
	return 0;
}

int input(){//takes the filename from input from main and calls open function to open it
	open(fileName);
	fflush(stdout);
	output();
	solve(0,0);
	printf("\nsolved ");
	output();
	return 0;
}



int main(){//main function
	printf("please enter a file name:\n");
	fflush(stdout);//encountered difficulty getting eclipse to print statements as the program was running even though statments all ended with a newline, the easiest slution I could find was to manually "flush" each printf to get the program working
	scanf("%s",fileName);
	input();
	verification(sudokuGrid);//verifies the solution
	return 0;
}
