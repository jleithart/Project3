#include "globals.h"
#include <iostream>

using namespace std;
void PrintBoard();

int main(){
	PrintBoard();
	system("PAUSE");
	return 0;
}

void PrintBoard(){
	for(int y = 0; y < 32; y++){
		for(int x = 0; x < 32; x++){
			if(board[y][x] == 0){
				cout << ".";
			}
			else{
				cout << "x";
			}
		}
		cout << endl;
	}
}