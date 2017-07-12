/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* Homework 1 18
 * File:   main.cpp
 * Author: s352431
 *
 * Created on 2017年7月12日, 下午 4:43
 */


#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int index(int i, int j);
float compute(float *w, vector< float > mData, int rowNum);
void swap(vector<float>& mData, int l, int r);
int countError(int rowNumTest,vector<float> mTestData, float *w );
int row = 6;
int y = row - 1;

/*
 * 
 */
int main(int argc, char** argv) {
    fstream mFile("hw1_18_train.dat", ios_base::in);
    fstream mTest("hw1_18_test.dat", ios_base::in);
    srand(time(NULL));
    vector< float > mData;
    vector< float > mTestData;
    float temp = 0;
    int count = 0;
    while (mFile >> temp) {
        if (count % y == 0) {
            mData.push_back(1.0);
        }
        count++;
        mData.push_back(temp);
    }
    int maxJ = count / row;
    for(int j = 0 ; j < maxJ ; j++ ){
        for (int i = 0; i < row ; i++) {
            cout << ", data[" << i <<","<<j<< "]:" << mData[index(i,j)];
        }
        cout<<endl;
    }
    int testCount = 0;
    while (mTest >> temp) {
        if (testCount % y == 0) {
            mTestData.push_back(1.0);
        }
        testCount++;
        mTestData.push_back(temp);
    }
    
    
    int rowNum = mData.size() / row;
    int rowNumTest = mTestData.size() / row;
    int maxCycle = 100;
    int cycle = maxCycle;
    int error = 0;
    
    float bestW[5] = {0.0f};
    while (cycle) {
        float w[5] = {0.0f};
        int updateNum = 50;
        int bestE = INT_MAX;
        while(updateNum) {
            int j = rand() % rowNum;
            float thisY = mData[index(y, j)];
            if ((compute(w, mData, j) * thisY) <= 0) {
                for (int i = 0; i < row - 1; i++) {
                    w[i] += thisY * mData[index(i, j)];
                }
                int nowE = countError(rowNumTest,mTestData,w);
                if(nowE < bestE){
                    for (int i = 0; i < row - 1; i++) {
                        bestW[i] = w[i];
                    }
                    bestE = nowE;
                }
                --updateNum;
            }
        }
        error += bestE;
        cout <<endl<<cycle<< ",error:" << bestE;
        for (int i = 0; i < row - 1; i++) {
            cout << ", w[" << i << "]:" << bestW[i];
        }
        --cycle;
    }
    cout <<endl<< "error:" << error <<", avg error:"<<(float(error)) / (float(maxCycle) * float(rowNumTest) )<< endl;


    return 0;
}
int countError(int rowNumTest,vector<float> mTestData, float *w ){
    int nowE = 0;
    for(int j = 0 ; j < rowNumTest ; j++ ){
        float ty = mTestData[index(y, j)];
        if ((compute(w, mTestData, j) * ty) < 0) {
            ++nowE;
        }
    }
    return nowE;
}

void swap(vector<float>& mData, int l, int r) {
    for (int i = 0; i < row; i++) {
        float temp = mData[index(i, l)];
        mData[index(i, l)] = mData[index(i, r)];
        mData[index(i, r)] = temp;
    }
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

int index(int i, int j) {
    return i + j * row;
}

