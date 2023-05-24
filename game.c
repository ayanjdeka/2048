#include "game.h"

/*AYAN DEKA INTRO PARAGRAPH: For this mp, I implemented functions that would help play the game 2048. Using the data structure of game, I used pointers to update the 
  rows, columns, and scores. Additionally, I implemented functions that would make the game itself, remake another game, and get the cell of the current game. To
 update the score, I transferred the algorithm that was given to us in Lab 8 and implemented it with pointers instead. After this, I updated the row or column by
 multiplying it by two, and adding on the score to this, and then cleared the current row. */


game * make_game(int rows, int cols)

{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));


    int size = rows * cols;//set size

    for(int i =0;i<size;i++){

      *((*mygame).cells + i) = -1;//clear everything

    }

    (*mygame).rows = rows;//set rows and columns to the game columns and rows
    (*mygame).cols = cols;  



    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));


	int size = new_rows * new_cols;//same thing as make game, just new rows and new cols
	for (int i = 0;i<size;i++){

	  *((**_cur_game_ptr).cells+i) = -1;

	}

	(**_cur_game_ptr).rows = new_rows;
	(**_cur_game_ptr).cols = new_cols;


	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)

{

  if(row < 0 || row>=(*cur_game).rows){//check if the rows and cols are in the bounds, and then return if they are in bounds the cell

    return NULL;

  }

  if(col < 0 || col>=(*cur_game).cols){

    return NULL;

  }

  return (*cur_game).cells + row * (*cur_game).cols + col;
}

int move_w(game * cur_game)

{

  int isLegalMove=0;//First example of the algorithm that we used in lab 8
  int lastMergedRow=-1;
  int foundRow=0;
  int mergableRow=-1;
  int i,j;

  for(i = 0; i < (*cur_game).rows; i++){

    lastMergedRow = -1;  //update lastMergedRow                            

    for(j = 0; j < (*cur_game).cols; j++){//iterate through the game

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   

          foundRow = 0;                  

          for(mergableRow = 0; mergableRow < i; mergableRow++){   
            if(*((*cur_game).cells + mergableRow * (* cur_game).cols + j) == -1){//find a row location that is empty
              foundRow = 1;
              break;
            }
          }
	  if(foundRow == 1){
	    *((*cur_game).cells + mergableRow * (* cur_game).cols + j) =  *((*cur_game).cells + i * (* cur_game).cols + j);//copy it
	    *((*cur_game).cells + i * (* cur_game).cols + j) = -1;//then clear it
	    isLegalMove = 1;//set the legalMove to 1
	  }

	  if((mergableRow-1) != lastMergedRow){//if they are not equal  to each other

	    if(*((*cur_game).cells +(mergableRow-1) * (* cur_game).cols + j) == *((*cur_game).cells + mergableRow * (* cur_game).cols + j)){//if the row above and 
	                                                                                                                                    //equal
	      *((*cur_game).cells +(mergableRow-1) * (* cur_game).cols + j) = *((*cur_game).cells +(mergableRow-1) * (* cur_game).cols + j)* 2;//multiply row by 2
	       (*cur_game).score += *((*cur_game).cells +(mergableRow-1) * (* cur_game).cols + j);//update score
	      *((*cur_game).cells + mergableRow * (* cur_game).cols + j) = -1;//clear the row
	      lastMergedRow = mergableRow - 1;//updateLastMergedRow for reference
	      isLegalMove = 1;//legalMove is true
	    }

	    

	  }

	}

      }
  }


      
  

  
  


    return isLegalMove;
};

int move_s(game * cur_game) 
{
    
    int lastMergedRow = -1;//similar to move_w, just switched from subtracting one to adding one. 
    int mergableRow = -1;
    int foundRow = 0;
    int isLegalMove = 0;
    int i,j;
   for(i = (*cur_game).rows - 1; i >= 0 ; i--){//go from greatest to least since we are adding one row

      lastMergedRow = -1;                             

      for(j = 0; j < (*cur_game).cols; j++){ 

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){  //checking for empty rows 

          foundRow = 0;

          for(mergableRow = (*cur_game).rows - 1; mergableRow > i; mergableRow--){        
            if(*((*cur_game).cells + mergableRow * (* cur_game).cols + j) == -1){//check for empty row while going from greatest to least
              foundRow = 1;
              break;
            }
          }

          if (foundRow == 1){
            *((*cur_game).cells + mergableRow * (* cur_game).cols + j) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;//empty the row
            isLegalMove = 1;
          }

          if ((mergableRow + 1) != lastMergedRow){//if they are not equal
            if(*((*cur_game).cells + (mergableRow + 1) * (* cur_game).cols + j) == *((*cur_game).cells + mergableRow * (* cur_game).cols + j)){//if these rows are
	                                                                                                                                      // equal
              *((*cur_game).cells + (mergableRow + 1) * (* cur_game).cols + j) = *((*cur_game).cells +(mergableRow+1) * (* cur_game).cols + j)* 2;//update the row
              (* cur_game).score += *((*cur_game).cells + (mergableRow+ 1) * (* cur_game).cols + j);//update score
              *((*cur_game).cells + mergableRow * (* cur_game).cols + j) = -1;//clear the row
              lastMergedRow = mergableRow + 1;
              isLegalMove = 1;
            }
          }
        }
      }
    }
    return isLegalMove;
};

int move_a(game * cur_game) //slide left
{

  int isLegalMove=0; //similar to move w but with columns
  int lastMergedCol=-1;
  int foundCol=0;
  int mergableCol=-1;
  int i,j;

  for(i = 0; i < (*cur_game).rows; i++){

      lastMergedCol = -1;                              

      for(j = 0; j < (*cur_game).cols; j++){

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   

          foundCol = 0;                  

          for(mergableCol = 0; mergableCol < j; mergableCol++){   
            if(*((*cur_game).cells + i * (* cur_game).cols + mergableCol) == -1){
              foundCol = 1;//found column that was empty
              break;
            }
          }
	  if(foundCol == 1){
	    *((*cur_game).cells + i * (* cur_game).cols + mergableCol) =  *((*cur_game).cells + i * (* cur_game).cols + j);//copy
	    *((*cur_game).cells + i * (* cur_game).cols + j) = -1;//clear
	    isLegalMove = 1;
	  }

	  if((mergableCol-1) != lastMergedCol){//check if not equal

	    if(*((*cur_game).cells + i  * (* cur_game).cols + (mergableCol-1)) == *((*cur_game).cells + i * (* cur_game).cols + mergableCol)){
	      *((*cur_game).cells + i  * (* cur_game).cols + (mergableCol-1))=  *((*cur_game).cells + i  * (* cur_game).cols + (mergableCol-1))*2;//update row
	      (*cur_game).score += *((*cur_game).cells + i  * (* cur_game).cols + (mergableCol-1));//update score
	      *((*cur_game).cells + i * (* cur_game).cols + mergableCol) = -1;//lear that row
	      lastMergedCol = mergableCol - 1;
	      isLegalMove = 1;
	    }

	    

	  }

	}

      }
  }


      
  

  
 
   return isLegalMove;

};

int move_d(game * cur_game){ //slide to the right
    int lastMergedCol = -1;
    int mergableCol = -1;
    int colFound = 0;
    int isLegalMove = 0;
    int i,j;//same as move s, just with columns
    for(i = 0; i < (*cur_game).rows; i++){

      lastMergedCol = -1;                             
      for(j = (*cur_game).cols - 1; j >= 0; j--){//start from greatest ot least because we are adding a cloumn

        if(*((*cur_game).cells + i * (* cur_game).cols + j) != -1){   
          colFound = 0;

          for(mergableCol = (*cur_game).cols - 1; mergableCol >= j; mergableCol--){              
	    if(*((*cur_game).cells + i * (* cur_game).cols + mergableCol) == -1){//found if column is -1.
              colFound = 1;
              break;
            }
          }

          if (colFound == 1){
            *((*cur_game).cells + i * (* cur_game).cols + mergableCol) = *((*cur_game).cells + i * (* cur_game).cols + j);  //copy and clear
            *((*cur_game).cells + i * (* cur_game).cols + j) = -1;  
            isLegalMove = 1;
          }

          if ((mergableCol + 1) != lastMergedCol){
            if(*((*cur_game).cells + i * (* cur_game).cols + (mergableCol + 1)) == *((*cur_game).cells + i * (* cur_game).cols + mergableCol)){  //if are equal       
              *((*cur_game).cells + i * (* cur_game).cols + (mergableCol + 1)) =*((*cur_game).cells + i * (* cur_game).cols + (mergableCol + 1))* 2; //update that
	                                                                                                                                             // column 
              (* cur_game).score += *((*cur_game).cells + i * (* cur_game).cols + (mergableCol + 1));//update score
              *((*cur_game).cells + i * (* cur_game).cols + mergableCol) = -1;//clear
              lastMergedCol = mergableCol + 1;//update lastMerged Col and isLegalMove
              isLegalMove = 1;
            }
          }
        }
      }
    }
    return isLegalMove;
};
int legal_move_check(game * cur_game)
{
                              
      for(int y = 0; y < (*cur_game).rows; y++){

	for(int x=0;x<(*cur_game).cols;x++){

	  int currentValue = *get_cell((cur_game),y,x);

	  if(currentValue == -1){
	    return 1;//check if the currentValue is equal to -1
	  }
	  
	  cell* getup    = get_cell(cur_game, y - 1, x);  //get the adjacent cells so that we can compare  
            cell* getdown  = get_cell(cur_game, y + 1, x);
            cell* getleft  = get_cell(cur_game, y, x - 1);     
            cell* getright = get_cell(cur_game, y, x + 1);     


	    //if the cells are not null, and they are equal to the current value, the another move can be made because these are adjacent to the current cell. 
            if (getleft != NULL && *getleft == currentValue) {           
                return 1;
            }
            if (getright != NULL && *getright == currentValue) {         
                return 1;
            }
            if (getup != NULL && *getup == currentValue) {               
                return 1;
            }
            if (getdown != NULL && *getdown == currentValue) {           
                return 1;
            }

	}


      }

    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
