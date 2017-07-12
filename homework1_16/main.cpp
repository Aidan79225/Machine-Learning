/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: s352431
 *
 * Created on 2017年7月12日, 下午 2:39
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int index(int i, int j);
int compute(float *w, vector< float > mData, int rowNum);
void swap(vector<float>& mData, int l, int r);
int row = 6;
int y = row - 1;

/*
 * 
 */
int main(int argc, char** argv) {
    fstream mFile("hw1_15_train.dat", ios_base::in);
    srand(time(NULL));
    vector< float > mData;
    float temp = 0;
    int count = 0;
    while (mFile >> temp) {
        if (count % y == 0) {
            mData.push_back(1);
        }
        count++;
        mData.push_back(temp);
    }
    int size = mData.size();
    int rowNum = size / row;
    int maxCycle = 2000;
    int cycle = maxCycle;
    while (cycle) {

        for (int j = 0; j < rowNum; j++) {
            swap(mData, j, rand() % rowNum);
        }
        float w[5] = {0.0f};
        for (int j = 0; j < rowNum; j++) {
            int thisY = mData[index(y, j)];
            if ((compute(w, mData, j) * thisY) < 0) {
                for (int i = 0; i < row - 1; i++) {
                    w[i] += thisY * mData[index(i, j)];
                }
                j = 0;
                count++;
            }
        }
        cout <<endl<< "count:" << count;
        for (int i = 0; i < row - 1; i++) {
            cout << "w[" << i << "]:" << w[i] << ", ";
        }
        --cycle;
    }
    cout <<endl<< "count:" << count <<", avg count:"<<(float(count)) / (float(maxCycle))<< endl;


    return 0;
}

void swap(vector<float>& mData, int l, int r) {
    for (int i = 0; i < row; i++) {
        float temp = mData[index(i, l)];
        mData[index(i, l)] = mData[index(i, r)];
        mData[index(i, r)] = temp;
    }
}

int compute(float *w, vector< float > mData, int rowNum) {
    int i = 0;
    float ans = 0.0f;
    for (int i = 0; i < row - 1; i++) {
        ans += w[i] * mData[index(i, rowNum)];
    }
    return ans > 0.0 ? 1 : -1;
}

int index(int i, int j) {
    return i + j * row;
}

