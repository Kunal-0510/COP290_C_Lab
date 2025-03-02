#include "Functions.h"
#include "linked_stack.h"
/*
0- constant 
1- arithmetic
2- MIN
3- MAX
4- AVG
5- SUM 
6- STDEV
7- SLEEP
*/

// Master function to handle different types of operations on a node
int MASTER( Node* node, Sheet* sheet ){
    int func_type= node->type;
    int max_col = sheet->cols;
    int index_1 = node->cell1; 
    int index_2 = node->cell2;
    int from_col = index_1%max_col;
    int to_col = index_2%max_col;
    int from_row = index_1/max_col;
    int to_row = index_2/max_col;

    if( func_type == 0 ){ // Constant assignment
        node->val = node->op_val;
        return 1;
    }
    else if(func_type==1){ //Arithmetic operations
        if(node->operator=='+'){
            if(node->cell1==-1){
                if((sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell2)->val + node->op_val;
                    node->isValid=1;
                }
            }
            else if(node->cell2==-1){
                if((sheet->matrix+ node->cell1)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val + node->op_val;
                    node->isValid=1;
                }
            }
            else{
                if((sheet->matrix+ node->cell1)->isValid==0 || (sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val + (sheet->matrix+ node->cell2)->val;
                    node->isValid=1;
                }
            }
            return 1;
        }
        else if(node->operator=='-'){
            if(node->cell2==-1){
                if((sheet->matrix+ node->cell1)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val - node->op_val;
                    node->isValid=1;
                }
                
            }
            else if(node->cell1==-1){
                if((sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= node->op_val- (sheet->matrix+ node->cell2)->val ;
                    node->isValid=1;
                }
            }
            else{
                if((sheet->matrix+ node->cell1)->isValid==0 || (sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val - (sheet->matrix+ node->cell2)->val;
                    node->isValid=1;
                }
            }
            return 1;
        }
        else if(node->operator=='*'){
            if(node->cell1==-1){
                if((sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell2)->val * node->op_val;
                    node->isValid=1;
                }
            }
            else if(node->cell2==-1){
                if((sheet->matrix+ node->cell1)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val * node->op_val;
                    node->isValid=1;
                }
            }
            else{
                if((sheet->matrix+ node->cell1)->isValid==0 || (sheet->matrix+ node->cell2)->isValid==0){
                    node->isValid=0;
                }
                else{
                    node->val= (sheet->matrix+ node->cell1)->val * (sheet->matrix+ node->cell2)->val;
                    node->isValid=1;
                }
            }
            return 1;
        }
        else if(node->operator=='/'){
            if(node->cell2==-1){
                if(node->op_val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    if((sheet->matrix+ node->cell1)->isValid==0){
                        node->isValid=0;
                    }
                    else{
                        node->val= ((sheet->matrix+ node->cell1)->val)/(node->op_val);
                        node->isValid=1;
                    }
                    
                }
                
                
            }
            else if(node->cell1==-1){
                if((sheet->matrix+ node->cell2)->val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    if((sheet->matrix+ node->cell2)->isValid==0){
                        node->isValid=0;
                    }
                    else{
                        node->val= (node->op_val)/((sheet->matrix+ node->cell2)->val);
                        node->isValid=1;
                    }
                }

            }
            else{
                if((sheet->matrix+ node->cell2)->val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    if((sheet->matrix+ node->cell1)->isValid==0 || (sheet->matrix+ node->cell2)->isValid==0){
                        node->isValid=0;
                    }
                    else{
                        node->val= ((sheet->matrix+ node->cell1)->val)/((sheet->matrix+ node->cell2)->val);
                        node->isValid=1;
                    }
                }
                
            }
            return 1;
        }
        else{
            return 0;
        }
    }
    else if( func_type == 2){ // MIN(RANGE)
        MIN( from_row,from_col,to_row,to_col,max_col, sheet , node);
        
        return 1;

    }
    else if( func_type == 3 ){ // MAX(RANGE)

        MAX( from_row,from_col,to_row,to_col,max_col, sheet , node);
        return 1;

    }

    else if( func_type == 4 ){ // AVG(RANGE)
        AVG( from_row,from_col,to_row,to_col,max_col, sheet , node);
        return 1;
    }

    else if( func_type == 5 ){ // SUM(RANGE)

        SUM( from_row,from_col,to_row,to_col,max_col, sheet , node);

        return 1;

    }

    else if( func_type == 6 ){ // STDEV(RANGE)
        STDEV( from_row,from_col,to_row,to_col,max_col, sheet, node );
        return 1;
    }

    else if( func_type == 7){ // SLEEP(RANGE)
        SLEEP(node,sheet);
        return 1;     
    }

    else{
        return 0;

    }
    
    
}

// Function to calculate the maximum value in a range
void MAX( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet, Node* node ){

    int mx = INT_MIN;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            if(( matrix + i*max_col +j )->isValid==0){
                node->isValid=0;
                return;
            }
            int element = ( matrix + i*max_col +j )->val;
            if( mx < element ){
                mx = element;
            }
        }
    }
    node->val= mx;
    node->isValid=1;
    return;

}

// Function to calculate the minimum value in a range
void MIN( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet , Node* node){
    
    int mn = INT_MAX;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            if(( matrix + i*max_col +j )->isValid==0){
                node->isValid=0;
                return;
            }
            int element = ( matrix + i*max_col +j )->val;
            if( mn > element ){
                mn = element;
            }
        }
    }

    node->val=mn;
    node->isValid=1;
    return;

}

// Function to calculate the average value in a range
void AVG( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet , Node* node){
    
    int avg_sum = 0;
    Node* matrix= sheet->matrix;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            if(( matrix + i*max_col +j )->isValid==0){
                node->isValid=0;
                return;
            }
            avg_sum += ( matrix + i*max_col +j )->val;
        }
    }

    int num_elements = ( to_row - from_row + 1 )*( to_col - from_col + 1 );
    int avg = avg_sum/num_elements;

    node->val= avg;
    node->isValid=1;
    return;

}

// Function to calculate the sum of values in a range
void SUM( int from_row,int from_col,int to_row,int to_col,int max_col,Sheet* sheet , Node* node){
    
    int sum = 0;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            if(( matrix + i*max_col +j )->isValid==0){
                node->isValid=0;
                return;
            }
            sum += ( matrix + i*max_col +j )->val;
        }
    }

    node->val= sum;
    node->isValid=1;
    return;

}

// Function to calculate the standard deviation of values in a range
void STDEV( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet , Node* node){

    int sum = 0;
    Node* matrix= sheet->matrix;
    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            if(( matrix + i*max_col +j )->isValid==0){
                node->isValid=0;
                return;
            }
            sum += ( matrix + i*max_col +j )->val;
        }
    }
    int num_of_terms = ( to_col - from_col +1 )*( to_row - from_row +1);
    int mean = sum / num_of_terms;
    double var = 0.0;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            var += ((( matrix + i*max_col +j )->val) - mean )*((( matrix + i*max_col +j )->val) - mean );
        }
    }
    
    var /= num_of_terms;
    
    node->val= (int)round(sqrt(var));
    node->isValid=1;
    return;

}

// Function to handle the SLEEP operation
void SLEEP(Node* node, Sheet* sheet){
    if(node->cell1==-1){
        int sec= node->op_val;
        if(sec>0){
            clock_t strt_time =  clock(); 
            clock_t end_time = strt_time + sec * CLOCKS_PER_SEC; 
            node->val= sec;
            while( clock() < end_time ) {}
        }
        node->val= sec;
        node->isValid=1;
        return;
    }
    else{
        if(((sheet->matrix)+node->cell1)->isValid==0){
            node->isValid=0;
            return;
        }
        int sec= ((sheet->matrix)+node->cell1)->val;
        if(sec>0){
            clock_t strt_time =  clock(); 
            clock_t end_time = strt_time + sec * CLOCKS_PER_SEC; 
            node->val= sec;
            while( clock() < end_time ) {}
        }
        node->val= sec;
        node->isValid=1;
        return;
    }
}

// Function to check for cycles in the dependency graph and topologically sort the nodes
void CHECK_CYCLE(Node* startNode, int* vis, Sheet* sheet, int cell1, int cell2, int* flag, int type, Stack* st) {
    Stack* stack= (Stack*)malloc(sizeof(Stack));
    StackInit(stack);  // Initialize local stack

    push(stack, startNode->id);
    
    LinkedStack* lkd = (LinkedStack*)malloc(sizeof(LinkedStack));
    LinkedStackInit(lkd);
    push_linked(lkd,startNode->OutNeighbours);
    while (isempty(stack)==0) {
        int id = peek(stack);
        Node* node = sheet->matrix + id;

        // Cycle condition checks
        if(vis[id]==0){
            if (type > 1 && type < 7) {
                if ((id / sheet->cols) >= (cell1 / sheet->cols) && (id / sheet->cols) <= (cell2 / sheet->cols)) {
                    if ((id % sheet->cols) >= (cell1 % sheet->cols) && (id % sheet->cols) <= (cell2 % sheet->cols)) {
                        *flag = 1;
                        
                    }
                }
            } else if (type == 1) {
                if (cell2 != -1 && cell1 != -1) {
                    if ((id / sheet->cols) == (cell1 / sheet->cols) && (id % sheet->cols) == (cell1 % sheet->cols)) {
                        *flag = 1;
                    }
                    if ((id / sheet->cols) == (cell2 / sheet->cols) && (id % sheet->cols) == (cell2 % sheet->cols)) {
                        *flag = 1;
                    }
                } else if (cell1 != -1) {
                    if ((id / sheet->cols) == (cell1 / sheet->cols) && (id % sheet->cols) == (cell1 % sheet->cols)) {
                        *flag = 1;
                    }
                } else {
                    if ((id / sheet->cols) == (cell2 / sheet->cols) && (id % sheet->cols) == (cell2 % sheet->cols)) {
                        *flag = 1;
                    }
                }
            } else if (type == 7) {
                if (cell1 != -1) {
                    if ((id / sheet->cols) == (cell1 / sheet->cols) && (id % sheet->cols) == (cell1 % sheet->cols)) {
                        *flag = 1;
                    }
                }
            }
        }
        vis[id]=1;
        if(*flag==1){
            return;
        }

        // Push first unvisited neighbor onto the stack
        LinkedList* in = linked_peek(lkd);
        int has_unvisited_child = 0;
        
        while (in != NULL) {
            if (vis[in->data] == 0) {
                push(stack, in->data);
                if((sheet->matrix+ (in->data))->OutNeighbours!=NULL){
                    push_linked(lkd, (sheet->matrix+ (in->data))->OutNeighbours);
                }
                else{
                    LinkedStackNode* temp = (LinkedStackNode*)malloc(sizeof(LinkedStackNode));
                    temp->next=lkd->top;
                    lkd->top=temp;
                }
               
                has_unvisited_child = 1;
                break; // Explore deeper first
            }
            in = in->next;
        }
        
        if (has_unvisited_child==0) {
            pop(stack);
            push(st, id);
            LinkedList* node = pop_linked(lkd);
            if(node!=NULL){
                if(node->next!=NULL){
                    push_linked(lkd,node->next);
                }
            }
        } 
    }
    free(stack);
}

// Function to delete edges from the dependency graph which the node previously depended on
int delete_edge(Node* node , Sheet* sheet){// node-> previous
    int type= node->type;
    if(type>1){
        if(type==7){
            if(node->cell1!=-1){   
                delete_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), &(node->id));
            }    
        }
        else{
            int cols= sheet->cols;
            int cell1= node->cell1;
            int cell2= node->cell2;
            int row1= cell1/cols;
            int col1= cell1%cols;
            int row2= cell2/cols;
            int col2= cell2%cols;
            for(int i=row1; i<=row2; i++){
                for(int j=col1; j<=col2; j++){
                    int cell = i*cols+j;   
                    delete_node(&(((sheet->matrix)+cell)->OutNeighbours), &(node->id));
                }
            }
        }
    }
    else if(type==1){
        
        if(node->cell1!=-1){
            delete_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), &(node->id));
        } 
        if(node->cell2!=-1){
            delete_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), &(node->id));
        }
    
    }
    return 1;
}

// Function to add edges to the dependency graph which the node now depends on
int add_edge(Node* node, Sheet* sheet){
    int type= node->type;
    if(type>1){
        if(type==7){
            if(node->cell1!=-1){ 
                add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), &(node->id));
            }    
        }
        else{
            int cols= sheet->cols;
            int cell1= node->cell1;
            int cell2= node->cell2;
            int row1= cell1/cols;
            int col1= cell1%cols;
            int row2= cell2/cols;
            int col2= cell2%cols;
            for(int i=row1; i<=row2; i++){
                for(int j=col1; j<=col2; j++){
                    int cell = i*cols+j;
                    add_node(&(((sheet->matrix)+cell)->OutNeighbours), &(node->id));
                }
            }
        }
    }
    else if(type==1){
        
        if(node->cell1!=-1){
            add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), &(node->id));
        } 
        if(node->cell2!=-1){
            add_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), &(node->id));
        }
    
    }
    return 1;
}

// Function to recalculate the value of a node
void recalculate_node( Node* node , Sheet* sheet , Stack* st ){
    int n = (sheet->cols)*(sheet->rows);
    while(isempty(st) == 0){
        int a= pop(st);
        MASTER((sheet->matrix+a),sheet);      
    }
}

