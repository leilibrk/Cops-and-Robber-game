#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#include<stdbool.h>
int Pmoves,Rmoves;
int p[100][3];   //This array will keep the position and the number of the station related to each cop.
char map[100][100];
int random_initialize(int j);
int random_move(int z, int j);
void random_move_cop(int i,int n,int m);
int check_robber_distance(int a,int xT,int yT);
void move_close(int i,int xT,int yT,int n,int m);
int which_station(int a,int xT,int yT);
void print_map(int n,int m);
void print_result(void);
int main(){
int n,m,s,i,j,k;
int b=0;
int st;
int result1=0;
int result;
int num=0;
int cop;
int xT,yT;
printf("Note: The program will print the map after each move of the robber and each move of the cops! \n");
printf("Enter the number of rows and columns: \n");
scanf("%d %d", &n, &m);
for(i=0;i<n;i++){
    for(j=0;j<m;j++){
        map[i][j]='+';
    }
}

xT=random_initialize(n);
yT=random_initialize(m);
map[xT][yT]='T';
printf("Enter the number of stations: \n");
scanf("%d",&s);
for(i=1;i<=s;i++){
     printf("Enter the number of cops in station number %d: \n",i);
     scanf("%d", &cop);
     num=cop+num;   //num =the total number of cops

      for(k=0;k<cop;k++){
         int x1=random_initialize(n);
         int y1=random_initialize(m);
         if(map[x1][y1]=='+'){
             p[b][0]=x1;
             p[b][1]=y1;
             p[b][2]=i;
             map[x1][y1]='0'+i;
             b++;
         }
         else{
            k--;
        }

    }
}

print_map(n,m);
while(true){
    map[xT][yT]='+';
    xT=random_move(xT,n);
    yT=random_move(yT,m);
    map[xT][yT]='T';
        printf("\n");
    print_map(n,m);
    Rmoves++;
    result=check_robber_distance(num,xT,yT);
    if(result==2){
                printf("\n");
            print_map(n,m);
            printf("The robber has came to the cop!! \n");
            print_result();
            break;
    }

    if(result==1){
          st=which_station(num,xT,yT);
          for(i=0;i<num;i++){
                int w=p[i][2];
                if(w==st){
                        move_close(i,xT,yT,n,m);
            }
                else{
                    random_move_cop(i,n,m);
            }
              Pmoves++;

          }

          result1=check_robber_distance(num,xT,yT);
          if(result1==2){
                printf("\n");
              print_map(n,m);
              printf("The robber has been arrested by the station number %d!! \n",st);
              print_result();
              break;
         }

    }
    if(result==3){
        for(i=0;i<num;i++){
            random_move_cop(i,n,m);
            Pmoves++;
        }
    }
        printf("\n");
    print_map(n,m);

}

return 0;

}

int random_initialize(int j){
time_t t=time(NULL);
srand(t);
int res=rand()%j;
return res;
}
int random_move(int z, int j){
time_t t=time(NULL);
srand(t);
while(true){

int i= -1 +rand()%3;
if(i==0){
    return z;
}

if(i==1 && z+1<j){
    return z+1;
}

if(i==-1 && z-1>=0){
    return z-1;
}

}

}
void random_move_cop(int i,int n,int m){
    while(true){
            int x=p[i][0];
            int y=p[i][1];
            int z=p[i][2];
            int x1=random_move(x,n);
            int y1=random_move(y,m);
            if(map[x1][y1]=='+'){
                map[x][y]='+';
                map[x1][y1]='0'+z;
                p[i][0]=x1;
                p[i][1]=y1;
                break;
            }

        }
}
int check_robber_distance(int a,int xT,int yT){
int i;
int distance;
for(i=0;i<a;i++){
    int x=p[i][0];
    int y=p[i][1];
    distance=(int)(pow(x-xT,2)+pow(y-yT,2));
    if(distance==0){
        return 2;
        }
}
for(i=0;i<a;i++){
    int x=p[i][0];
    int y=p[i][1];
    distance=(int)(pow(x-xT,2)+pow(y-yT,2));
    if(distance==8 || distance==2 || distance==4 || distance==1 || distance==5){
        return 1;

    }
}
return 3;

}
int which_station(int a,int xT,int yT){
int i;
int distance;
int res;
for(i=0;i<a;i++){
    int x=p[i][0];
    int y=p[i][1];
    distance=(int)(pow(x-xT,2)+pow(y-yT,2));
    if(distance==8 || distance==2 || distance==4 || distance==1 || distance==5){
        res=p[i][2];
        return res;

    }
}
}
void move_close(int i,int xT,int yT,int n,int m){
    int x,y,z,d1,d2;
         x=p[i][0];
         y=p[i][1];
         z=p[i][2];
         d1=xT-x;
         d2=yT-y;
    if(d1>0 && d2>0){
          if(map[x+1][y+1]=='+' || map[x+1][y+1]=='T'){
             map[x][y]='+';
             x=x+1;
             y=y+1;
             map[x][y]='0'+z;
             p[i][0]=x;
             p[i][1]=y;
        }
           else{
                 random_move_cop(i,n,m);
            }

        }
    if(d1<0 && d2<0){
           if(map[x-1][y-1]=='+' || map[x-1][y-1]=='T'){
                  map[x][y]='+';
                   x=x-1;
                   y=y-1;
                   map[x][y]='0'+z;
                   p[i][0]=x;
                   p[i][1]=y;
        }
          else{
                random_move_cop(i,n,m);
            }

        }
    if(d1>0 && d2==0){
            if(map[x+1][y]=='+' || map[x+1][y]=='T'){
              map[x][y]='+';
              x=x+1;
              map[x][y]='0'+z;
              p[i][0]=x;
              p[i][1]=y;
            }
             else{
                random_move_cop(i,n,m);
            }

        }
    if(d1==0 && d2>0){
            if(map[x][y+1]=='+' || map[x][y+1]=='T'){
              map[x][y]='+';
               y=y+1;
              map[x][y]='0'+z;
              p[i][0]=x;
              p[i][1]=y;
            }
             else{
               random_move_cop(i,n,m);
            }

        }
    if(d1<0 && d2==0){
           if(map[x-1][y]=='+' || map[x-1][y]=='T'){
            map[x][y]='+';
            x=x-1;
            map[x][y]='0'+z;
            p[i][0]=x;
            p[i][1]=y;
        }
            else{
                random_move_cop(i,n,m);
            }

        }
    if(d1==0 && d2<0){
           if(map[x][y-1]=='+' || map[x][y-1]=='T'){
             map[x][y]='+';
             y=y-1;
             map[x][y]='0'+z;
             p[i][0]=x;
             p[i][1]=y;
        }
            else{
               random_move_cop(i,n,m);
            }

        }
    if(d1>0 && d2<0){

          if(map[x+1][y-1]=='+' || map[x+1][y-1]=='T'){
            map[x][y]='+';
            x=x+1;
            y=y-1;
            map[x][y]='0'+z;
            p[i][0]=x;
            p[i][1]=y;
            }
            else{
                random_move_cop(i,n,m);
            }

        }
    if(d1<0 && d2>0){
        if(map[x-1][y+1]=='+' || map[x-1][y+1]=='T'){
            map[x][y]='+';
            x=x-1;
            y=y+1;
            map[x][y]='0'+z;
            p[i][0]=x;
            p[i][1]=y;
        }
         else{
                random_move_cop(i,n,m);
            }

        }

}
void print_map(int n,int m){
 int i,j;
 for(i=0;i<n;i++){
     for(j=0;j<m;j++){
        printf("%c",map[i][j]);
    }
    printf("\n");
}
 Sleep(500);

}
void print_result(void){
printf("The total moves of the robber : %d \n",Rmoves);
printf("The total moves of the cops : %d \n",Pmoves);
}







