#include <stdio.h>
#include "Functions.h"
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "hash.h"
#include "Queue.h"
#include "Node.h"
#include "Sheet.h"

int MASTER( Node* node, Sheet* sheet ){
    int func_type= node->type;
    int max_col = sheet->cols;
    int index_1 = node->cell1;
    int index_2 = node->cell2;
    int from_col = index_1%max_col;
    int to_col = index_2%max_col;
    int from_row = index_1/max_col;
    int to_row = index_2/max_col;
    int success= 1;
    if( func_type == 0 ){ // Constant assignment
        node->val = node->op_val;
    }
    else if(func_type==1){ //Addition
        if(node->cell2==-1){
            node->val= (sheet->matrix+ node->cell1)->val + node->op_val;
        }
        else{
            node->val= (sheet->matrix+ node->cell1)->val + (sheet->matrix+ node->cell2)->val;
        }
    }
    else if(func_type==2){ //Subtraction
        if(node->cell2==-1){
            node->val= (sheet->matrix+ node->cell1)->val - node->op_val;
        }
        if(node->cell1==-1){
            node->val= node->op_val- (sheet->matrix+ node->cell2)->val ;
        }
        else{
            node->val= (sheet->matrix+ node->cell1)->val - (sheet->matrix+ node->cell2)->val;
        }
    }

    else if(func_type==3){ //Product
        if(node->cell2==-1){
            node->val= ((sheet->matrix+ node->cell1)->val) * (node->op_val);
        }
        else{
            node->val= ((sheet->matrix+ node->cell1)->val) * ((sheet->matrix+ node->cell2)->val);
        }
    }

    else if(func_type==4){ //Division
        if(node->cell2==-1){
            node->val= ((sheet->matrix+ node->cell1)->val)/(node->op_val);
        }
        if(node->cell1==-1){
            node->val= (node->op_val)/((sheet->matrix+ node->cell2)->val) ;
        }
        else{
            node->val= ((sheet->matrix+ node->cell1)->val)/((sheet->matrix+ node->cell2)->val);
        }
    }
    
    else if( func_type == 5){ // MIN(RANGE)
        int ans=  MIN( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;

    }
    else if( func_type == 6 ){ // MAX(RANGE)

        int ans= MAX( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;

    }
    else if( func_type == 7 ){ // AVG(RANGE)
        node->val= AVG( from_row,from_col,to_row,to_col,max_col, sheet );
    }
    else if( func_type == 8 ){ // SUM(RANGE)

        node->val= SUM( from_row,from_col,to_row,to_col,max_col, sheet );

    }

    else if( func_type == 9 ){ // STDEV(RANGE)

        node->val= STDEV( from_row,from_col,to_row,to_col,max_col, sheet );
    }

    else if( func_type == 10){ // SLEEP(RANGE)
        SLEEP(node,sheet);
    }
    else{
        success=0;

    }
    
    return success;
}

int MAX( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet ){

    int mx = INT_MIN;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            int element = ( matrix + i*max_col +j )->val;
            if( mx < element ){
                mx = element;
            }
        }
    }
    return mx;

}

int MIN( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet ){
    
    int mn = INT_MAX;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            int element = ( matrix + i*max_col +j )->val;
            if( mn > element ){
                mn = element;
            }
        }
    }

    return mn;

}

int AVG( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet ){
    
    int avg_sum = 0;
    Node* matrix= sheet->matrix;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            avg_sum += ( matrix + i*max_col +j )->val;
        }
    }

    int num_elements = ( to_row - from_row + 1 )*( to_col - from_col + 1 );
    int avg = avg_sum/num_elements;

    return avg;

}

int SUM( int from_row,int from_col,int to_row,int to_col,int max_col,Sheet* sheet ){
    
    int sum = 0;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            sum += ( matrix + i*max_col +j )->val;
        }
    }

    return sum;

}

int STDEV( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet ){
    Node* matrix= sheet->matrix;
    int sum = SUM(from_row, from_col, to_row, to_col, max_col, matrix);
    int num_of_terms = ( to_col - from_col )*( to_row - from_row );
    int mean = sum / num_of_terms;
    int var = 0;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            var += ((( matrix + i*max_col +j )->val) - mean )*((( matrix + i*max_col +j )->val) - mean );
        }
    }
    
    var /= num_of_terms;
    int std_dev = sqrt( var );;
    
    return std_dev;

}

void SLEEP(Node* node, Sheet* sheet){

    
    if(node->cell1==-1){
        int sec= node->op_val;
        clock_t strt_time =  clock(); 
        clock_t end_time = strt_time + sec * CLOCKS_PER_SEC; 
        node->val= sec;
        while( clock() < end_time ) {}
    }
    else{
        int sec= ((sheet->matrix)+node->cell1)->val;
        clock_t strt_time =  clock();
        clock_t end_time = strt_time + sec * CLOCKS_PER_SEC;
        node->val= sec;
        while( clock() < end_time ) {}
    }
    

}

int CHECK_CYCLE( Sheet* sheet ){
    
    Queue* q = (Queue*)(malloc(sizeof(Queue)));
    QueueInit(q);
    int max_cols = sheet->cols;
    int max_rows = sheet->rows;

    for( int i = 0 ; i<max_rows ; i++ ){

        for( int j = 0 ; j<max_cols ; j++ ){

            Node* node = (sheet->matrix + i*max_cols + j );

            if( node->in_size == 0 ){

                QueueNode* newNode = (QueueNode*)(malloc(sizeof(QueueNode)));
                QueueNodeInit(newNode);
                newNode->node = (sheet->matrix + i*max_cols + j );
                QueuePush(q,newNode);

            }
        }

    }

    int n = 0;

    while( isEmpty(q) == 0 ){

        QueueNode* Node = QueuePop(q);
        n++;
        LinkedList* top = Node->node->OutNeighbours;
        
        while( top!= NULL ){

            (sheet->matrix + top->data)->in_size--;

            if((sheet->matrix + top->data)->in_size == 0){
                
                QueueNode* newNode = (QueueNode*)(malloc(sizeof(QueueNode)));
                newNode->node = (sheet->matrix + top->data);
                QueuePush(newNode,q);

            }

        }

        free(Node);

    }

    free(q);

    for( int i = 0 ; i<max_cols ; i++ ){

        int count = 0;

        for( int j = 0 ; j<max_cols ; j++ ){

            LinkedList* inNeighbours = (sheet->matrix + i*max_cols + j )->InNeighbours;

            while( inNeighbours!=NULL ){

                count++;
                inNeighbours = inNeighbours->next;

            }

        }

    }

    if( n == max_cols*max_cols ){
        return 1;
    }

    return 0;

}