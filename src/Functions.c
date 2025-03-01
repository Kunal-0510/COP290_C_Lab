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

// A1> graph>  topological sort>  
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
    else if(func_type==1){ //arithmetic
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
            // printf("cell1: %d cell2: %d val: %d\n", node->cell1, node->cell2, node->op_val);
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
        else if(node->operator=='/'){ //TODO: Handle division by zero. (Donee)
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

// void CHECK_CYCLE( Node* node , int* vis , Sheet* sheet , int  cell1 , int cell2 ,int* flag , int type , Stack* st ){
//     vis[node->id] = 1;
//     if(type>1&&type<7){
//         if((node->id)/(sheet->cols)>=(cell1)/(sheet->cols)&&(node->id)/(sheet->cols)<=(cell2)/(sheet->cols)){
//             if((node->id)%(sheet->cols)>=(cell1)%(sheet->cols)&&(node->id)%(sheet->cols)<=(cell2)%(sheet->cols)){
//                 *flag = 1;
//             }
//         }
//     }
//     else if ( type == 1 ){
//         if(cell2!=-1&& cell1!=-1){
//             if((node->id)/(sheet->cols)==(cell1)/(sheet->cols)&&(node->id)%(sheet->cols)==(cell1)%(sheet->cols)){
//                 *flag = 1;
//             }
//             if((node->id)/(sheet->cols)==(cell2)/(sheet->cols)&&(node->id)%(sheet->cols)==(cell2)%(sheet->cols)){
//                 *flag = 1;
//             }
//         }
//         else if (cell1!=-1){
//             if((node->id)/(sheet->cols)==(cell1)/(sheet->cols)){
//                 if((node->id)%(sheet->cols)==(cell1)%(sheet->cols)){
//                     *flag = 1;
//                 }
//             }
//         }
//         else {
//             if((node->id)/(sheet->cols)==(cell2)/(sheet->cols)){
//                 if((node->id)%(sheet->cols)==(cell2)%(sheet->cols)){
//                     *flag = 1;
//                 }
//             }
//         }
//     }
//     else if(type == 7){
//         if(cell1!=-1){
//             if((node->id)/(sheet->cols)==(cell1)/(sheet->cols)&&(node->id)%(sheet->cols)==(cell1)%(sheet->cols)){
//                 *flag = 1;
//             }
//         }
//     }
    
//     LinkedList* out = (sheet->matrix+node->id)->OutNeighbours;
//     while( out!= NULL ){
//         if( vis[out->data]==0 ){
//             CHECK_CYCLE( (sheet->matrix)+(out->data) ,  vis ,  sheet ,  cell1 ,  cell2 , flag ,  type , st );
//             if(flag == 1){
//                 return;
//             }
//         }
//         out = out->next; 
//     }
//     push( st, node->id );
// }
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
        // if (vis[id]==1) continue;  // Skip if already visited

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

        // Push all unvisited neighbors onto the stack
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
                // push_linked(lkd);
               
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
// int add_edge(Node* node, Sheet* sheet){
//     int n = (sheet->cols)*(sheet->rows);
//     LinkedList* curr_head= node->InNeighbours;
//     LinkedList* temp= curr_head;
//     node->InNeighbours=NULL;
//     while(temp!=NULL){
//         delete_node(&(((sheet->matrix)+temp->data)->OutNeighbours), node->id);
//         temp=temp->next;
//     }
    
//     if(node->type>0 && !(node->type==7 && node->cell1==-1)){


//         LinkedList* tempList = NULL; 
       
//         if(node->type==1 || node->type==7){
//             if(node->cell1!=-1){
//                 add_node(&(node->InNeighbours), node->cell1);
//                 add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
//                 add_node(&tempList, node->cell1);
//             }

//             if(node->cell2!=-1){
//                 add_node(&(node->InNeighbours), node->cell2);
//                 add_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), node->id);
//                 add_node(&tempList, node->cell2);
//             }
//         }
        
//         else{
//             int max_col = sheet->cols;
//             int index_1 = node->cell1;
//             int index_2 = node->cell2;
//             int from_col = index_1%max_col;
//             int to_col = index_2%max_col;
//             int from_row = index_1/max_col;
//             int to_row = index_2/max_col;


//             for( int i = from_row; i <= to_row; i++ ){
//                 for( int j = from_col; j<=to_col; j++ ){
//                     int cell= i*max_col+j;
//                     add_node(&node->InNeighbours, cell);
//                     add_node(&(((sheet->matrix)+ cell)->OutNeighbours), node->id);
//                     add_node(&tempList, cell);
//                 }
//             }
//         }
       

//         int* pathVis = (int*)calloc(n, sizeof(int));
//         int* vis = (int*)calloc(n, sizeof(int));

//         int cycle= CHECK_CYCLE(node->id,pathVis,vis,sheet);

//         free(vis);
//         free(pathVis);

//         if(cycle==1){
//             LinkedList* tmp= tempList;

//             while(tmp!=NULL){
//                 delete_node(&(((sheet->matrix)+tmp->data)->OutNeighbours), node->id);
//                 tmp=tmp->next;
//             }

//             LinkedList* temp= curr_head;

//             while(temp!=NULL){
//                 add_node(&(((sheet->matrix)+temp->data)->OutNeighbours), node->id);
//                 temp=temp->next;
//             }

//             free_list(&(node->InNeighbours));
//             node->InNeighbours= temp;
//             free_list(&tmp);
//             return 0;
//         }
//         else{

//             free_list(&curr_head);
//             free_list(&tempList);

//             return 1;
//         }
//     }
//     else{
        
//         free_list(&curr_head);
//         node->InNeighbours=NULL;
//         return 1;
//     }
// }
//input-> cycle-> delete->assign->add->recalculate
int delete_edge(Node* node , Sheet* sheet){// node-> previous
    int type= node->type;
    if(type>1){
        if(type==7){
            if(node->cell1!=-1){
                // LinkedList* tba= ((sheet->matrix)+node->cell1)->OutNeighbours;
                delete_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
                // ((sheet->matrix)+node->cell1)->OutNeighbours=tba;
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
                    // LinkedList* tba= ((sheet->matrix)+cell)->OutNeighbours;
                    delete_node(&(((sheet->matrix)+cell)->OutNeighbours), node->id);
                    // ((sheet->matrix)+cell)->OutNeighbours=tba;
                }
            }
        }
    }
    else if(type==1){
        
        if(node->cell1!=-1){
            // LinkedList* tba= ((sheet->matrix)+node->cell1)->OutNeighbours;
            delete_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
            // ((sheet->matrix)+node->cell1)->OutNeighbours=tba;
        } 
        if(node->cell2!=-1){
            // LinkedList* tba= ((sheet->matrix)+node->cell2)->OutNeighbours;
            delete_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), node->id);
            // ((sheet->matrix)+node->cell2)->OutNeighbours=tba;
        }
    
    }
    return 1;
}

int add_edge(Node* node, Sheet* sheet){
    int type= node->type;
    if(type>1){
        if(type==7){
            if(node->cell1!=-1){
                // LinkedList* tba= ((sheet->matrix)+node->cell1)->OutNeighbours;
                add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
                // ((sheet->matrix)+node->cell1)->OutNeighbours=tba;
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
                    // LinkedList* tba= ((sheet->matrix)+cell)->OutNeighbours;
                    add_node(&(((sheet->matrix)+cell)->OutNeighbours), node->id);
                    // ((sheet->matrix)+cell)->OutNeighbours=tba;
                }
            }
        }
    }
    else if(type==1){
        
        if(node->cell1!=-1){
            // LinkedList* tba= ((sheet->matrix)+node->cell1)->OutNeighbours;
            add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
            // ((sheet->matrix)+node->cell1)->OutNeighbours=tba;
        } 
        if(node->cell2!=-1){
            // LinkedList* tba= ((sheet->matrix)+node->cell2)->OutNeighbours;
            add_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), node->id);
            // ((sheet->matrix)+node->cell2)->OutNeighbours=tba;
        }
    
    }
    return 1;
}
/* Doing recalculation on the nodes not the entire sheet*/
// void topo_sort( int id , int* vis , Stack* st ,Sheet* sh ){

//     vis[id] = 1;
//     LinkedList* in = (sh->matrix+id)->OutNeighbours;
//     while( in!= NULL ){
//         if( vis[in->data]==0 ){
//             topo_sort( in->data , vis , st , sh );
//         }
//         in=in->next; //Gogo Stupidity counter- infinity
//     }
//     push( st, id );
// }

// void dfs( int id , int*vis , Sheet* sheet ){
//     vis[id] = 1;
//     LinkedList* in = (sheet->matrix+id)->OutNeighbours;
//     while( in!= NULL ){
//         if( vis[in->data]==0 ){
//             (sheet->matrix+in->data)->isValid = (sheet->matrix +id)->isValid;
//             dfs( in->data , vis ,sheet );
//         }
//         in=in->next; 
//     }
// }

void recalculate_node( Node* node , Sheet* sheet , Stack* st ){
    int n = (sheet->cols)*(sheet->rows);
    while(isempty(st) == 0){
        int a= pop(st);
        MASTER((sheet->matrix+a),sheet);      
    }
}

