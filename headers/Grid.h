#pragma once
#include <vector>
#include <random>

class Grid {
private:
    int len;
    std::vector<std::vector<int>> gridLogic;
    std::vector<std::vector<int>> gridView;

    bool isMinePossible(int i, int j) const{
        if (i == 1 && j == 1 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i == len - 1 && j == 1 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i == len - 1 && j == len - 1 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i == 1 && j == len - 1 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i == 1 && j > 1 && gridLogic[i - 1][j - 2] == 9 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9
            && gridLogic[i][j - 2] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i == len - 1 && j > 1 && gridLogic[i - 1][j - 2] == 9 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9
            && gridLogic[i][j - 2] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (j == 1 && i > 1 && gridLogic[i - 2][j - 1] == 9 && gridLogic[i - 2][j] == 9 && gridLogic[i - 1][j - 1] == 9
            && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (j == len - 1 && i > 1 && gridLogic[i - 2][j - 1] == 9 && gridLogic[i - 2][j] == 9 && gridLogic[i - 1][j - 1] == 9
            && gridLogic[i - 1][j] == 9 && gridLogic[i][j - 1] == 9)
            return false;
        if (i > 1 && j > 1 && i < len - 2 && j < len - 2 && gridLogic[i - 2][j - 2] == 9 && gridLogic[i - 2][j - 1] == 9 && gridLogic[i - 2][j] == 9
            && gridLogic[i - 1][j - 2] == 9 && gridLogic[i - 1][j - 1] == 9 && gridLogic[i - 1][j] == 9
            && gridLogic[i][j - 2] == 9 && gridLogic[i][j - 1] == 9)
            return false;

        return true;
    }

    void fillView(){
        for (int i = 0; i < len; i++) { // randomly deside what cell will have a mine
            std::vector<int> temp1(len, 10);
            gridView[i] = temp1;
        }
    }

    void fillMines(int x, int y) {
        std::random_device rd; // generate random numbers using Medison's vortex
        std::mt19937 mersenne(rd());
        for (int i = 0; i < len; i++) { // randomly deside what cell will have a mine
            std::vector<int> temp2(len);

            gridLogic[i] = temp2;
        }
        int k = 0;
        while (k < 2 * len) {
            int i = mersenne() % len;
            int j = mersenne() % len;
            if ((i != x || j != y) && !gridLogic[i][j] && isMinePossible(i, j)) {
                ++k;
                gridLogic[i][j] = 9;
            }
        }
    }
//    void fillMines() {
//        std::random_device rd; // generate random numbers using Medison's vortex
//        std::mt19937 mersenne(rd());
//        for (int i = 0; i < len; i++) { // randomly deside what cell will have a mine
//            std::vector<int> temp1(len, 10);
//            std::vector<int> temp2(len);
//
//            gridView[i] = temp1;
//            gridLogic[i] = temp2;
//        }
//        int k = 0;
//        while (k < 2 * len) {
//            int i = mersenne() % len;
//            int j = mersenne() % len;
//            if (!gridLogic[i][j] && isMinePossible(i, j)) {
//                ++k;
//                gridLogic[i][j] = 9;
//            }
//        }
//    }

    void fillLogic() {
        for (int i = 0; i < len; i++) // fill logic grid with apropriate numbers
            for (int j = 0; j < len; j++)
            {
                int n = 0;
                if (gridLogic[i][j] == 9) continue;
                if (i < len - 1 && gridLogic[i + 1][j] == 9) n++;
                if (j < len - 1 && gridLogic[i][j + 1] == 9) n++;
                if (i > 0 && gridLogic[i - 1][j] == 9) n++;
                if (j > 0 && gridLogic[i][j - 1] == 9) n++;
                if (i < len - 1 && j < len - 1 && gridLogic[i + 1][j + 1] == 9) n++;
                if (i > 0 && j > 0 && gridLogic[i - 1][j - 1] == 9) n++;
                if (i > 0 && j < len - 1 && gridLogic[i - 1][j + 1] == 9) n++;
                if (i < len - 1 && j > 0 && gridLogic[i + 1][j - 1] == 9) n++;
                gridLogic[i][j] = n;
            }
    }


public:
    Grid(int len) {
        this->len = len;
        gridLogic.resize(len);
        gridView.resize(len);
//        fillMines();
//        fillLogic();
        fillView();
    }

    void fill(int x, int y){
        fillMines(x, y);
        fillLogic();
    }

    int getView(int i, int j) const {
        return gridView[i][j];
    }
    void setView(int i, int j) {
        gridView[i][j] = gridLogic[i][j];
    }
    void setView(int i, int j, int val) {
        gridView[i][j] = val;
    }

    int getLogic(int i, int j) const {
        return gridLogic[i][j];
    }

    void showUp(int i, int j) {
        if (i < 0 || j < 0 || i == len || j == len || gridView[i][j] != 10)
            return;
        gridView[i][j] = gridLogic[i][j];
        if (!gridView[i][j]) {
            showUp(i - 1, j - 1);
            showUp(i - 1, j);
            showUp(i - 1, j + 1);
            showUp(i, j - 1);
            showUp(i, j + 1);
            showUp(i + 1, j - 1);
            showUp(i + 1, j);
            showUp(i + 1, j + 1);
        }
    }

    void border(int i, int j) {
        gridView[i][j] = gridLogic[i][j];
        if (i > 0 && j > 0 && !gridLogic[i - 1][j - 1])
            showUp(i - 1, j - 1);
        else if (i > 0 && !gridLogic[i - 1][j])
            showUp(i - 1, j);
        else if (i > 0 && j < len - 1 && !gridLogic[i - 1][j + 1])
            showUp(i - 1, j + 1);
        else if (j > 0 && !gridLogic[i][j - 1])
            showUp(i, j - 1);
        else if (j < len - 1 && !gridLogic[i][j + 1])
            showUp(i, j + 1);
        else if (i < len - 1 && j > 0 && !gridLogic[i + 1][j - 1])
            showUp(i + 1, j - 1);
        else if (i < len - 1 && !gridLogic[i + 1][j])
            showUp(i + 1, j);
        else if (i < len - 1 && j < len - 1 && !gridLogic[i + 1][j + 1])
            showUp(i + 1, j + 1);
    }

    bool isComplete() {
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                if (gridView[i][j] == 10 || gridLogic[i][j] == 9 && gridView[i][j] != 11)
                    return false;
            }
        }
        return true;
    }
};

