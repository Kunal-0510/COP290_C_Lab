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
        }
        else if(node->operator=='-'){
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
        }
        else if(node->operator=='/'){ //TODO: Handle division by zero.
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
        else{
            success=0;
        }
    }
    else if( func_type == 2){ // MIN(RANGE)
        int ans=  MIN( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;

    }
    else if( func_type == 3 ){ // MAX(RANGE)

        int ans= MAX( from_row,from_col,to_row,to_col,max_col, sheet );
        node->val= ans;

    }

    else if( func_type == 4 ){ // AVG(RANGE)
        node->val= AVG( from_row,from_col,to_row,to_col,max_col, sheet );
    }

    else if( func_type == 5 ){ // SUM(RANGE)

        node->val= SUM( from_row,from_col,to_row,to_col,max_col, sheet );

    }

    else if( func_type == 6 ){ // STDEV(RANGE)

        node->val= STDEV( from_row,from_col,to_row,to_col,max_col, sheet );
    }

    else if( func_type == 7){ // SLEEP(RANGE)
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

int CHECK_CYCLE( Sheet* sheet ){
    // printf("I reached here!!111\n");
    Queue* q = (Queue*)(malloc(sizeof(Queue)));
    QueueInit(q);
    int max_cols = sheet->cols;
    int max_rows = sheet->rows;
    // printf("I reached here!!112\n");
    for( int i = 0 ; i<max_rows ; i++ ){

        for( int j = 0 ; j<max_cols ; j++ ){
            // printf("I reached here!!11 i: %d j: %d\n", i, j);
            Node* node = (sheet->matrix + i*max_cols + j );
            // printf("insize:%d\n", node->in_size);
            if( node->in_size == 0 ){

                QueueNode* newNode = (QueueNode*)(malloc(sizeof(QueueNode)));
                QueueNodeInit(newNode);
                // printf("I reached here!!1111\n");
                newNode->node = (sheet->matrix + i*max_cols + j );
                // printf("I reached here!!1112\n");
                QueuePush(newNode,q);
                // printf("I reached here!!1113\n");
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
                QueueInit(newNode);
                newNode->node = (sheet->matrix + top->data);
                QueuePush(newNode,q);

            }
            top=top->next; //Gogo mistake counter:4

        }

        free(Node);

    }

    free(q);

    for( int i = 0 ; i<max_cols ; i++ ){
        for( int j = 0 ; j<max_cols ; j++ ){
            int count = 0;
            LinkedList* inNeighbours = (sheet->matrix + i*max_cols + j )->InNeighbours;
            while( inNeighbours!=NULL ){
                count++;
                inNeighbours = inNeighbours->next;
            }
            (sheet->matrix + i*max_cols + j )->in_size = count;
        }
    }
    if( n == max_cols*max_cols ){
        return 1;
    }
    return 0;

}

int add_edge(Node* node, Sheet* sheet){
    if(node->type>0){
        // printf("I reached here!!13\n");
        LinkedList* curr_head= node->InNeighbours;
        int temp_size= node->in_size;
        node->InNeighbours= NULL;
        node->in_size=0;
        LinkedList* tempList = NULL; 
        if(node->type==1){
            if(node->cell1!=-1){
                node->InNeighbours= add_node(node->InNeighbours, node->cell1);
                node->in_size++;
                if(find_node(((sheet->matrix)+(node->cell1))->OutNeighbours, node->id)==0){
                    ((sheet->matrix)+node->cell1)->OutNeighbours= add_node(((sheet->matrix)+node->cell1)->OutNeighbours, node->id);
                    tempList= add_node(tempList, node->cell1);
                }
            }
            if(node->cell2!=-1){
                node->InNeighbours= add_node(node->InNeighbours, node->cell2);
                node->in_size++;
                if(find_node(((sheet->matrix)+(node->cell2))->OutNeighbours, node->id)==0){
                    ((sheet->matrix)+node->cell2)->OutNeighbours= add_node(((sheet->matrix)+node->cell2)->OutNeighbours, node->id);
                    tempList= add_node(tempList, node->cell2);
                }
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
                    node->InNeighbours= add_node(node->InNeighbours, cell);
                    node->in_size++;
                    if(find_node(((sheet->matrix)+cell)->OutNeighbours, node->id)==0){
                        ((sheet->matrix)+ cell)->OutNeighbours= add_node(((sheet->matrix)+ cell)->OutNeighbours, node->id);
                        tempList= add_node(tempList, cell);
                    }
                }
            }
        }
        // printf("I reached here!!15\n");
        printf("indegree of %d: %d\n", node->id, node->in_size);
        print_list(node->InNeighbours);
        if(CHECK_CYCLE(sheet)==1){
                LinkedList* tmp= tempList;
                while(tmp!=NULL){
                    delete_node(((sheet->matrix)+tmp->data)->OutNeighbours, node->id);
                    tmp=tmp->next;
                }
                free_list(tmp);
                LinkedList* tmp2= node->InNeighbours;
                node->InNeighbours= curr_head;
                free_list(tmp2);
                node->in_size= temp_size;
                return 0;
            }
        else{
            free_list(curr_head);
            free_list(tempList);
            return 1;
        }
        // printf("I reached here!!16\n");
    }
    else{
        return 1;
    }
}

/* Doing recalculation on the nodes not the entire sheet*/

void recalculate_node( Node* node , Sheet* sheet ){
    // printf("I reached here!!1\n");

    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Memory allocation failed for Queue q\n");
        return;
    }
    QueueInit(q);

    int max_cols = sheet->cols;

    QueueNode* n1 = (QueueNode*)malloc(sizeof(QueueNode));
    if (n1 == NULL) {
        fprintf(stderr, "Memory allocation failed for QueueNode n1\n");
        free(q);
        return;
    }
    QueueNodeInit(n1);
    n1->node = node;
    QueuePush(n1, q);

    Queue* q1 = (Queue*)malloc(sizeof(Queue));
    if (q1 == NULL) {
        fprintf(stderr, "Memory allocation failed for Queue q1\n");
        free(n1);
        free(q);
        return;
    }
    QueueInit(q1);

    // printf("I reached here!!2\n");

    while( isEmpty(q) == 0 ){

        QueueNode* Node = QueuePop(q);
        LinkedList* top = Node->node->OutNeighbours;
        QueuePush(Node,q1);

        while( top!= NULL ){

            (sheet->matrix + top->data)->in_size--;

            if((sheet->matrix + top->data)->in_size == 0){
                
                QueueNode* newNode = (QueueNode*)(malloc(sizeof(QueueNode)));
                QueueInit(newNode);
                newNode->node = (sheet->matrix + top->data);
                QueuePush(newNode,q);

            }
            top=top->next;

        }

    }

    free(q);

    for( int i = 0 ; i<max_cols ; i++ ){


        for( int j = 0 ; j<max_cols ; j++ ){
            int count = 0;

            LinkedList* inNeighbours = (sheet->matrix + i*max_cols + j )->InNeighbours;

            while( inNeighbours!=NULL ){

                count++;
                inNeighbours = inNeighbours->next;

            }
            (sheet->matrix + i*max_cols + j )->in_size = count;

        }

    }
    PrintQueue(q1);
    while( isEmpty(q1) == 0 ){

        QueueNode* head = QueuePop(q1);
        MASTER( head->node ,sheet );
        free(head);

    }
    free(q1);

}
