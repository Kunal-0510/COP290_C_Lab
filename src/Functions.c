#include "Functions.h"

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
                node->val= (sheet->matrix+ node->cell2)->val + node->op_val;
            }
            else if(node->cell2==-1){
                node->val= (sheet->matrix+ node->cell1)->val + node->op_val;
            }
            else{
                node->val= (sheet->matrix+ node->cell1)->val + (sheet->matrix+ node->cell2)->val;
            }
            node->isValid=1;
            return 1;
        }
        else if(node->operator=='-'){
            // printf("cell1: %d cell2: %d val: %d\n", node->cell1, node->cell2, node->op_val);
            if(node->cell2==-1){
                node->val= (sheet->matrix+ node->cell1)->val - node->op_val;
                // printf("value: %d\n", node->val);
                
            }
            else if(node->cell1==-1){
                node->val= node->op_val- (sheet->matrix+ node->cell2)->val ;
            }
            else{
                node->val= (sheet->matrix+ node->cell1)->val - (sheet->matrix+ node->cell2)->val;
            }
            node->isValid=1;
            return 1;
        }
        else if(node->operator=='*'){
            if(node->cell1==-1){
                node->val= (sheet->matrix+ node->cell2)->val * node->op_val;
            }
            else if(node->cell2==-1){
                node->val= (sheet->matrix+ node->cell1)->val * node->op_val;
            }
            else{
                node->val= (sheet->matrix+ node->cell1)->val * (sheet->matrix+ node->cell2)->val;
            }
            node->isValid=1;
            return 1;
        }
        else if(node->operator=='/'){ //TODO: Handle division by zero. (Donee)
            if(node->cell2==-1){
                if(node->op_val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    node->val= ((sheet->matrix+ node->cell1)->val)/(node->op_val);
                    node->isValid=1;
                }
                
                
            }
            else if(node->cell1==-1){
                if((sheet->matrix+ node->cell2)->val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    node->val= (node->op_val)/((sheet->matrix+ node->cell2)->val) ;
                    node->isValid=1;
                }

            }
            else{
                if((sheet->matrix+ node->cell2)->val==0){
                    node->isValid=0;
                    return 1;
                }
                else{
                    node->val= ((sheet->matrix+ node->cell1)->val)/((sheet->matrix+ node->cell2)->val);
                    node->isValid=1;
                }
                
            }
            return 1;
        }
        else{
            return 0;
        }
    }
    else if( func_type == 2){ // MIN(RANGE)
        int ans=  MIN( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;
        node->isValid=1;
        return 1;

    }
    else if( func_type == 3 ){ // MAX(RANGE)

        int ans= MAX( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;
        node->isValid=1;
        return 1;

    }

    else if( func_type == 4 ){ // AVG(RANGE)
        node->val= AVG( from_row,from_col,to_row,to_col,max_col, sheet );
        node->isValid=1;
        return 1;
    }

    else if( func_type == 5 ){ // SUM(RANGE)

        node->val= SUM( from_row,from_col,to_row,to_col,max_col, sheet );
        node->isValid=1;
        return 1;

    }

    else if( func_type == 6 ){ // STDEV(RANGE)

        node->val= STDEV( from_row,from_col,to_row,to_col,max_col, sheet );
        node->isValid=1;
        return 1;
    }

    else if( func_type == 7){ // SLEEP(RANGE)
        SLEEP(node,sheet);
        node->isValid=1;
        return 1;
        
    }

    else{
        return 0;

    }
    
    
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
    int std_dev = sqrt( var );
    
    return std_dev;

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
    }
    else{
        int sec= ((sheet->matrix)+node->cell1)->val;
        if(sec>0){
            clock_t strt_time =  clock(); 
            clock_t end_time = strt_time + sec * CLOCKS_PER_SEC; 
            node->val= sec;
            while( clock() < end_time ) {}
        }
        node->val= sec;
    }
}

int CHECK_CYCLE( int id,int* pathVis,int* vis,Sheet* sheet ){
    vis[id]=1;
    pathVis[id]=1;
    LinkedList* top = (sheet->matrix+id)->OutNeighbours;
    while(top!=NULL){
        if(vis[top->data]==0){
            if(CHECK_CYCLE(top->data,pathVis,vis,sheet)){
                return 1;
            }
        }
        else if(pathVis[top->data]==1){
            return 1;
        }
        top=top->next;
    }
    pathVis[id]=0;
    return 0;
}

int add_edge(Node* node, Sheet* sheet){
    int n = (sheet->cols)*(sheet->rows);
    LinkedList* curr_head= node->InNeighbours;
    LinkedList* temp= curr_head;
    node->InNeighbours=NULL;
    while(temp!=NULL){
        delete_node(&(((sheet->matrix)+temp->data)->OutNeighbours), node->id);
        temp=temp->next;
    }
    
    if(node->type>0 && !(node->type==7 && node->cell1==-1)){


        LinkedList* tempList = NULL; 
       
        if(node->type==1 || node->type==7){
            if(node->cell1!=-1){
                add_node(&(node->InNeighbours), node->cell1);
                add_node(&(((sheet->matrix)+node->cell1)->OutNeighbours), node->id);
                add_node(&tempList, node->cell1);
            }

            if(node->cell2!=-1){
                add_node(&(node->InNeighbours), node->cell2);
                add_node(&(((sheet->matrix)+node->cell2)->OutNeighbours), node->id);
                add_node(&tempList, node->cell2);
            }
        }
        
        else{
            int max_col = sheet->cols;
            int index_1 = node->cell1;
            int index_2 = node->cell2;
            int from_col = index_1%max_col;
            int to_col = index_2%max_col;
            int from_row = index_1/max_col;
            int to_row = index_2/max_col;


            for( int i = from_row; i <= to_row; i++ ){
                for( int j = from_col; j<=to_col; j++ ){
                    int cell= i*max_col+j;
                    add_node(&node->InNeighbours, cell);
                    add_node(&(((sheet->matrix)+ cell)->OutNeighbours), node->id);
                    add_node(&tempList, cell);
                }
            }
        }
       

        int* pathVis = (int*)calloc(n, sizeof(int));
        int* vis = (int*)calloc(n, sizeof(int));

        int cycle= CHECK_CYCLE(node->id,pathVis,vis,sheet);

        free(vis);
        free(pathVis);

        if(cycle==1){
            LinkedList* tmp= tempList;

            while(tmp!=NULL){
                delete_node(&(((sheet->matrix)+tmp->data)->OutNeighbours), node->id);
                tmp=tmp->next;
            }

            LinkedList* temp= curr_head;

            while(temp!=NULL){
                add_node(&(((sheet->matrix)+temp->data)->OutNeighbours), node->id);
                temp=temp->next;
            }

            free_list(&(node->InNeighbours));
            node->InNeighbours= temp;
            free_list(&tmp);
            return 0;
        }
        else{

            free_list(&curr_head);
            free_list(&tempList);

            return 1;
        }
    }
    else{
        
        free_list(&curr_head);
        node->InNeighbours=NULL;
        return 1;
    }
}

/* Doing recalculation on the nodes not the entire sheet*/
void topo_sort( int id , int* vis , Stack* st ,Sheet* sh ){

    vis[id] = 1;
    LinkedList* in = (sh->matrix+id)->OutNeighbours;
    while( in!= NULL ){
        if( vis[in->data]==0 ){
            topo_sort( in->data , vis , st , sh );
        }
        in=in->next; //Gogo Stupidity counter- infinity
    }
    push( st, id );
}
void recalculate_node( Node* node , Sheet* sheet ){
    // printf("I reached here!!1\n");

    Stack* st = (Stack*)(malloc(sizeof(Stack)));
    StackInit(st);

    int n = (sheet->cols)*(sheet->rows);
    int* vis = (int*)malloc(n * sizeof(int));
    memset(vis, 0, n * sizeof(int));
    topo_sort( node->id, vis, st, sheet );

    free(vis);
    int flag=1;
    while(isempty(st) == 0){
        MASTER((sheet->matrix+pop(st)),sheet);   
    }
}