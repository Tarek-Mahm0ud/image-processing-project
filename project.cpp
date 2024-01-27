#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE],image2[SIZE][SIZE],image3[128][128];
unsigned char shrinkimage[SIZE][SIZE];
char file[100],file2[100];
void load_Image_1 () {
   cout << "Enter the source image file name: ";
   cin >> file;
   strcat (file, ".bmp");
   readGSBMP(file, image);
}
void load_Image_2 () {
    readGSBMP(file, image2);
}
void save_Image_1 () {
   cout << "Enter the target image file name: ";
   cin >> file;
   strcat (file, ".bmp");
   writeGSBMP(file, image);
}
void save_Image_2 () {
    cout << "Enter the target image 2 file name: ";
    cin >> file2;
    strcat (file2, ".bmp");
    writeGSBMP(file2, image2);
}
void menu(){
    cout<<"Please select a filter to apply or 0 to exit: "<<endl;
    cout<<"1-\tblack and white"<<endl<<"2-\tInvert Filter"<<endl<<"3-\tMerge Filter"<<endl<<"4-\tFlip Image"<<endl<<"5-\tDarken and Lighten Image"<<endl<<"6-\tRotate Image"<<endl<<"7-\tDetect Image Edges"<<endl<<"8-\tEnlarge Image"<<endl<<"9-\tShrink Image"<<endl<<"0-\tExit"<<endl;
}
void black_and_white(){
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            if (image[x][y]< 128)
                image[x][y] = 0;
            else image[x][y] = 255;
        }
    }
}
void error_diffusion(){
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            if(image2[x][y]<128){
                int Pold=image2[x][y];
                image2[x][y]=0;
                int error =Pold;
                if(y+1<=256&&x==0){
                    image2[x][y+1]=image2[x][y+1]+round(7.0/16.0*error);
                }
                if(x+1<=256&&y+1<=256){
                    image2[x+1][y+1]=image2[x+1][y+1]+round(1.0/16.0*error);
                }
                if(x+1<=256){
                    image2[x+1][y]=image2[x+1][y]+round(5.0/16.0*error);
                }
                if(y-1>=0&&x+1<=256){
                    image2[x+1][y-1]=image2[x+1][y-1]+round(3.0/16.0*error);
                }
            }
            else{
                int Pold=image2[x][y];
                image2[x][y]=255;
                int error =Pold-255;
                if(y+1<=256&&x==0){
                    if((image2[x][y+1]+round(7.0/16.0*error))<0){
                        image2[x][y+1]=0;
                    }else{
                        image2[x][y+1]=image2[x][y+1]+round(7.0/16.0*error);
                    }
                }
                if(x+1<=256&&y+1<=256){
                    if((image2[x+1][y+1]+round(1.0/16.0*error))<0){
                        image2[x+1][y+1]=0;
                    }else{
                        image2[x+1][y+1]=image2[x+1][y+1]+round(1.0/16.0*error);
                    }
                }
                if(x+1<=256){
                    if((image2[x+1][y]+round(5.0/16.0*error))<0){
                        image2[x+1][y]=0;
                    }else{
                        image2[x+1][y]=image2[x+1][y]+round(5.0/16.0*error);
                    }
                }
                if(y-1>=0&&x+1<=256){
                    if((image2[x+1][y-1]+round(3.0/16.0*error))<0){
                        image2[x+1][y-1]=0;
                    }else{
                        image2[x+1][y-1]=image2[x+1][y-1]+round(3.0/16.0*error);
                    }
                }
            }
        }
    }
}
void invert_filter(){
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            image[x][y]=255-image[x][y];
        }
    }
}
void merge_two_image(){
    cout<<"Enter the source image 2 file name: ";
    cin>>file2;
    strcat (file2, ".bmp");
    readGSBMP(file2, image2);
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            image[x][y]=(image[x][y]+image2[x][y])/2;
        }
    }
    char file3[100];
    cout << "Enter the target image file name: ";
    cin >> file3;
    strcat (file3, ".bmp");
    writeGSBMP(file3, image);
}
void filp_image(){
    char s;
    cout<<"Flip (h)orizontally or (v)ertically ?\n";
    cin>>s;
    if(s=='v'||s=='V'){
        for(int x=0;x<SIZE/2;x++){
            for(int y=0;y<SIZE;y++){
                swap(image[x][y],image[255-x][255-y]);
                // swap first indces with last indces
            }
        }
    }
    else if(s=='h'||s=='H'){
        for(int y=0;y<SIZE/2;y++){
            for(int x=0;x<SIZE;x++){
                swap(image[x][y],image[x][255-y]);
                // swap first indces with last indces
            }
        }
    }
    else{
        cout<<"Choose correctly and try again.\n";
    }
}
void Darken_and_Lighten(){
    cout<<"Do you want to (d)arken or (l)ighten?\n";
    char s;
    cin>>s;
    if(s=='d'||s=='D'){
        for(int x=0;x<SIZE;x++){
            for(int y=0;y<SIZE;y++){
                image[x][y]-=image[x][y]*0.5;
            }
        }
    }
    else if(s=='l'||s=='L'){
        for(int x=0;x<SIZE;x++){
            for(int y=0;y<SIZE;y++){
                image[x][y]+=(256-image[x][y])*0.5;
            }
        }
    }
    else {
        cout<<"Choose correctly and try again.\n";
    }
}
void Rotate_Image(){
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            image2[x][y]=image[x][y];
        }
    }
    int d;
    cout<<"Rotate (90), (180) , (270) or (360) degrees? with clockwise"<<endl;
    cin>>d;
    d/=90;
    while(d--){
        for(int x=0;x<SIZE;x++){
            for(int y=0;y<SIZE;y++){
                image[y][x]=image2[255-x][y];
            }
        }
        for(int x=0;x<SIZE;x++){
            for(int y=0;y<SIZE;y++){
                image2[x][y]=image[x][y];
            }
        }
    }
}
void Detect_Image_Edges(){
    long avg = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++){
            avg += image[i][j]; // taking the sum of all elements in the photo
        }
    }
    avg /= (SIZE * SIZE); // to calculate the average color of the photo
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j< SIZE; j++){
            if ( ( image[i][j] < avg ) and ( image[i][j+1] < avg ) ){
                while ( image[i][j+4] < avg){
                    if (image[i+1][j]<avg){
                        // if there is a black cell and black cells after it , makes these two cells white
                        image[i][j+2]=255;
                        j+=1;
                    }
                    else{
                        j+=1;
                    }
                }
            }
            if (image[i][j]>avg){
                image[i][j] = 255; // if cell is more than average color of photo make it white
            }
        }
    }
    cout << "End filter" << endl;
}
void scaled_up(){
    for(int i = 0, x = 0;  i <= 256 && x <= 128; i += 2, x++){ //scaled up image
        for(int j = 0, y = 0; j <= 256 && y <= 128; j += 2 ,y++){
            // each pixel in small image (image3) take 4 pixel in large image
            // I took each pixel and multiplied it by four
            image[i][j] = image3[x][y];
            image[i+1][j] = image3[x][y];
            image[i][j+1] = image3[x][y];
            image[i+1][j+1] = image3[x][y];
        }
    }
}
void Enlarge_Image(){
    cout<<"Please select one of the four quarters of the image: (1,2,3,4)\n";
    int n;cin>>n;
    if(n==1){
        for(int x=0;x<128;x++){
            for(int y=0;y<128;y++){
                image3[x][y]=image[x][y];
            }
        }
        scaled_up();
    }
    else if(n==2){
        for(int x=0;x<128;x++){
            for(int y=128;y<256;y++){
                image3[x][y-128]=image[x][y];
            }
        }
        scaled_up();
    }
    else if(n==3){
        for(int x=128;x<256;x++){
            for(int y=0;y<128;y++){
                image3[x-128][y]=image[x][y];
            }
        }
        scaled_up();
    }
    else if(n==4){
        for(int x=128;x<256;x++){
            for(int y=128;y<256;y++){
                image3[x-128][y-128]=image[x][y];
            }
        }
        scaled_up();
    }
    else{
        cout<<"Choose correctly and try again.\n";
        Enlarge_Image();
    }

}
void Shrink_Image(){
    cout<<"Shrink to (1/2), (1/3) or (1/4)?\n";
    string ratio;cin>>ratio;
    for(int x=0;x<SIZE;x++){
        for(int y=0;y<SIZE;y++){
            shrinkimage[x][y]=255;
        }
    }
    if(ratio=="1/2"){
        for (int x = 0; x < SIZE/2; ++x) {
            for (int y = 0; y <SIZE/2 ; ++y) {
                shrinkimage[x][y] = image[x*2][y*2];
            }
        }
        for (int x = 0; x <SIZE; ++x) {
            for (int y = 0; y<SIZE; ++y) {
                image[x][y] =shrinkimage[x][y];
            }
        }
    }
    else if(ratio=="1/3"){
        for (int x=0;x<SIZE/3;++x) {
            for (int y=0;y<SIZE/3 ;++y) {
                shrinkimage[x][y]=image[x*3][y*3];
            }
        }
        for (int x = 0; x <SIZE; ++x) {
            for (int y = 0; y<SIZE; ++y) {
                image[x][y] =shrinkimage[x][y];
            }
        }
    }
    else if(ratio=="1/4"){
        for (int x = 0; x < SIZE/4; ++x) {
            for (int y = 0; y <SIZE/4 ; ++y) {
                shrinkimage[x][y]=image[x*4][y*4];
            }
        }
        for (int x = 0; x <SIZE; ++x) {
            for (int y = 0; y<SIZE; ++y) {
                image[x][y] =shrinkimage[x][y];
            }
        }
    }
    else{
        cout<<"Choose correctly and try again.\n";
        Shrink_Image();
    }
}
int main()
{
    int num;
    menu();
    cin>>num;
    if(num==1){ // 1- black and white
        load_Image_1();
        load_Image_2();
        black_and_white();
        error_diffusion();
        save_Image_1();
        save_Image_2();
    }
    else if(num==2){ // 2- Invert Filter
        load_Image_1();
        invert_filter();
        save_Image_1();
    }
    else if(num==3){ // 3-	Merge Filter
        load_Image_1();
        merge_two_image();
    }
    else if(num==4){ // 4-	Flip Image
        load_Image_1();
        filp_image();
        save_Image_1();
    }
    else if(num==5){ // 5-	Darken and Lighten Image
        load_Image_1();
        Darken_and_Lighten();
        save_Image_1();
    }
    else if(num==6){ // 6-	Rotate Image
        load_Image_1();
        Rotate_Image();
        save_Image_1();
    }
    else if(num==7){ // 7-	Detect Image Edges
        load_Image_1();
        Detect_Image_Edges();
        save_Image_1();
    }
    else if(num==8){ // 8-	Enlarge Image
        load_Image_1();
        Enlarge_Image();
        save_Image_1();
    }
    else if(num==9){ // 9-	Shrink Image
        load_Image_1();
        Shrink_Image();
        save_Image_1();
    }
    else if(num==0){ // 0-	Exit
        cout<<"Thank you <3"<<endl;
        return 0;
    }
    return 0;
}