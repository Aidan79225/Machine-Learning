/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* Homework 1 15
 * File:   main.cpp
 * Author: s352431
 * 
 * Created on 2017年7月11日, 下午 2:59
 */
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int index(int i, int j);
float compute(float *w, vector< float > mData, int rowNum);
int row = 6;
int y = row - 1;
/*
 * 
 */
int main() {
    fstream mFile("hw1_15_train.dat",ios_base::in);
    vector< float > mData;
    float temp = 0;
    int count = 0;
    while(mFile >> temp){
        if(count % y == 0){
            mData.push_back(1.0);
        }
        count++;
        mData.push_back(temp);
    }
    int size = mData.size();
    int rowNum = size / row;
    for(int j = 0 ; j < rowNum ; j++){
        for(int i = 0 ; i < row ; i++ ){
            cout << mData[index(i,j)] << ", ";
        }
        cout<<endl;
    }
    cout<<endl;
    float w[5] = {0.0f};
    count = 0;
    for(int j = 0 ; j < rowNum ; j++);
    int j = 0;
    int end = rowNum;
    while(j != end){
        if(j >= rowNum)j = j % rowNum;
        float thisY = mData[index(y,j)];
        if( (compute(w, mData, j) * thisY) <= 0){
            for(int i = 0 ; i< row-1 ; i++){
                w[i] += thisY * mData[index(i,j)];
                cout<<"i:"<<i<<",j:"<<j<<", index"<<index(i,j)<<", ";
            }
            end = j;
            count ++;
            cout<<endl;
            for(int i = 0 ; i< row-1 ; i++){
                cout<<"w["<<i<<"]:"<<w[i]<<", ";
            }
        }
        j++;
    }
    cout<<"count:"<<count<<endl;
    for(int i = 0 ; i< row-1 ; i++){
        cout<<"w["<<i<<"]:"<<w[i]<<", ";
    }
    
    return 0;
}

float compute(float *w, vector< float > mData, int rowNum) {
    int i = 0;
    float ans = 0.0f;
    for (int i = 0; i < row - 1; i++) {
        ans += w[i] * mData[index(i, rowNum)];
    }
    if(ans == 0)return -1;
    else return ans;
}

int index(int i, int j){
    return i + j * row;
}
