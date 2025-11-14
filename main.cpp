#include <iostream>
#include <vector>
#include <set>

using namespace std;
const int n = 5;

bool is_reflexive(int matrix[][n]) {
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0) {
            return false;
        }
    }
    return true;
}

bool is_symmetric(int matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool is_transitive(int matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (matrix[i][k] == 1 && matrix[k][j] == 1 && matrix[i][j] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

vector<int> equivalence_classes(int x, int matrix[][n]) {
    vector<int> r;
    for (int j = 0; j < n; j++) {
        if (matrix[x][j]) {
            r.push_back(j + 1);
        }
    }
    return r;
}

vector<vector<int>> all_equivalence_classes(int matrix[][n]) {
    vector<vector<int>> r;
    set<int> st;
    for (int j = 0; j < n; j++) {
        if (st.count(j))continue;
        vector<int> tmp;
        for (int k = 0; k < n; k++) {
            if (matrix[j][k]) {
                st.insert(k);
                tmp.push_back(k + 1);
            }
        }
        r.push_back(tmp);
    }
    return r;
}

void print_equivalence_classes(int mat[][n]) {
    if (is_reflexive(mat) && is_symmetric(mat) && is_transitive(mat)) {
        cout << "동치 관계." << endl;
        vector<vector<int>> als = all_equivalence_classes(mat);
        for (int i = 0; i < als.size(); i++) {
            cout << "동치류 " << i + 1 << ": ";
            for (auto j: als[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
        cout << endl;

        vector<int> tmp;
        for (int i = 0; i < n; i++) {
            cout << i + 1 << "의 동치류: ";
            for (auto j: equivalence_classes(i, mat)) {
                cout << j << ' ';
            }
            cout << endl;
        }

    } else {
        cout << "동치 관계가 아님." << endl;
    }
    cout << endl;
}

void copy_mat(int out[][n], int in[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out[i][j] = in[i][j];
        }
    }
}

void print_matrix(int mat[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << ' ';
        }
        cout << endl;
    }
}

void reflexive_closure(int in[][n], int out[][n]) {
    copy_mat(out, in);
    for (int i = 0; i < n; i++) {
        out[i][i] = 1;
    }
}

void symmetric_closure(int in[][n], int out[][n]) {
    copy_mat(out, in);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (in[i][j] == 1) {
                out[j][i] = 1;
            }
        }
    }
}

void transitive_closure(int in[][n], int out[][n]) {
    copy_mat(out, in);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (out[i][k] == 1 && out[k][j] == 1) {
                    out[i][j] = 1;
                }
            }
        }
    }
}

signed main() {
    cout << "matrix 자동 생성 1 or 수동 입력 2: ";
    int opt;
    cin >> opt;
    int mat[n][n];
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (opt == 2)cin >> mat[i][j];
            else mat[i][j] = rand() % 2;
        }
    }
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ origin matrix:" << endl;
    print_matrix(mat);
    cout << endl;

    print_equivalence_classes(mat);
    int tmp[n][n];
    if (!is_reflexive(mat)) {
        reflexive_closure(mat, tmp);
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ 반사 폐포 변환 후 matrix:" << endl;
        print_matrix(tmp);
        cout << endl;
        print_equivalence_classes(tmp);
    }
    if (!is_symmetric(mat)) {
        symmetric_closure(mat, tmp);
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ 대칭 폐포 변환 후 matrix:" << endl;
        print_matrix(tmp);
        cout << endl;
        print_equivalence_classes(tmp);
    }
    if (!is_transitive(mat)) {
        transitive_closure(mat, tmp);
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ 추이 폐포 변환 후 matrix:" << endl;
        print_matrix(tmp);
        cout << endl;
        print_equivalence_classes(tmp);
    }
}
