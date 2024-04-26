#include<stdio.h>
int height = 20, width = 20;
void draw(){
    int i,j;
    for(i; i<height; i++){
        for(j=0; j<width; j++){
            if(i==0 || i==height-1 || j==0 || width-1){
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(){
    draw();

}