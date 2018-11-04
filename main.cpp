#include <iostream>
#include <pthread.h>


#define MAX_SZ  1000


using namespace std;


int n[2],m[2];
int a[MAX_SZ][MAX_SZ];
int b[MAX_SZ][MAX_SZ];
int result1[MAX_SZ][MAX_SZ];
int result2[MAX_SZ][MAX_SZ];


void get_first_input(){
    printf("Enter size of the first matrix\n");
    scanf("%d %d",&n[0],&m[0]);

    for(int i=0;i<n[0];i++){
        for(int j=0;j<m[0];j++)
            scanf("%d",&a[i][j]);
    }
}
void get_seconds_input(){
    printf("\nEnter size of the second matrix\n");
    scanf("%d %d",&n[1],&m[1]);

    for(int i=0;i<n[1];i++){
        for(int j=0;j<m[1];j++)
            scanf("%d",&b[i][j]);
    }
}

void *multiply1(void *x){
    /// current thread id
    int tid = *(int *)x;

    int row = tid/m[1];
    int col = tid%m[1];


    for(int i=0;i<m[0];i++){
             result1[row][col] += a[row][i] * b[i][col];
    }
}
void solve_each_element_using_thread(){
    /// number of threads we will need is n[0] * m[1]  which is the size of the answer matrix


    int need = n[0]*m[1];
    pthread_t p[need];


    for(int i=0;i<need;i++){
        pthread_create(&p[i] , NULL , multiply1 , (void *)(new int(i)));
    }

    for(int i=0;i<need;i++){
         pthread_join(p[i] , NULL);
    }

     printf("\n\nThe result of the first procedure : \n\n" );

     for(int i=0;i<n[0];i++){
         for(int j=0;j<m[1];j++){
             printf("%d " , result1[i][j]);
         }
         printf("\n");
     }
}

void *multiply2(void *x){
    /// current thread id
    int tid = *(int *)x;

    int row = tid;

    for(int i=0;i<m[0];i++){
        for(int col = 0 ; col<n[1]; col++)
             result2[row][col] += a[row][i] * b[i][col];
    }
}
void solve_each_row_using_thread(){
    /// number of threads we will need is n[0]  which is the number of rows in the answer matrix


    int need = n[0];
    pthread_t p[need];


    for(int i=0;i<need;i++){
        pthread_create(&p[i] , NULL , multiply2 , (void *)(new int(i)));
    }

    for(int i=0;i<need;i++){
         pthread_join(p[i] , NULL);
    }

     printf("\n\nThe result of the second procedure : \n\n" );
     for(int i=0;i<n[0];i++){
         for(int j=0;j<m[1];j++){
             printf("%d " , result2[i][j]);
         }
         printf("\n");
     }
}

int main()
{

    freopen("test.in","r",stdin);

    get_first_input();
    get_seconds_input();
    solve_each_element_using_thread();
    solve_each_row_using_thread();

    return 0;
}
