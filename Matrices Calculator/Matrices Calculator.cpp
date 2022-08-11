#include <iostream>
#include <cmath>

using namespace std;

void calc_addition(int row_size, int column_size, long long AMatrix[][15], long long BMatrix[][15])
{
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++)
        {
            cout << round(AMatrix[i][j] + BMatrix[i][j]) << " ";
        }
        cout << endl;
    }
}

void calc_subtraction(int row_size, int column_size, long long AMatrix[][15], long long BMatrix[][15])
{
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++)
        {
            cout << round(AMatrix[i][j] - BMatrix[i][j]) << " ";
        }
        cout << endl;
    }
}

void calc_multiplication(int Arow_size, int Bcolumn_size, int Common_size, long long AMatrix[][15], long long BMatrix[][15])
{
    int multiplication = 0;

    for (int i = 0; i < Arow_size; ++i)
    {

        for (int j = 0; j < Bcolumn_size; ++j) {

            for (int k = 0; k < Common_size; ++k)
            {
                multiplication += AMatrix[i][k] * BMatrix[k][j];
            }
            cout << round(multiplication) << " ";
            multiplication = 0;
        }
        cout << endl;
    }

}
long long calc_determinant(int row_size, int column_size, long long dMatrix[][15])
{
    long long dMatrix_result = 0;
    if (row_size == 1)
        return dMatrix[0][0];
    long long temp[15][15];
    int sign = 1;
    for (int cf = 0; cf < row_size; cf++)
    {
        int temp_i = 0, temp_j = 0;
        for (int mati = 0; mati < row_size; mati++)
        {
            for (int matj = 0; matj < column_size; matj++)
                if (mati != 0 && matj != cf)
                {
                    temp[temp_i][temp_j] = dMatrix[mati][matj];
                    temp_j++;
                    if (temp_j == row_size - 1)
                    {
                        temp_i++;
                        temp_j = 0;
                    }
                }
        }
        dMatrix_result = dMatrix_result + (sign * dMatrix[0][cf] * calc_determinant(row_size - 1, column_size - 1, temp));
        sign = sign * -1;

    }
    return dMatrix_result;
}
void calc_adjoint(int row_size, int column_size, long long mainMatrix[][15], long long adjointMatrix[][15])
{
    if (row_size == 1)
    {
        adjointMatrix[0][0] = 1;
        return;
    }

    long long temp[15][15];

    int sign = 1;

    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++)
        {

            int temp_i = 0, temp_j = 0;
            for (int mati = 0; mati < row_size; mati++)
            {
                for (int matj = 0; matj < column_size; matj++)
                    if (mati != i && matj != j)
                    {
                        temp[temp_i][temp_j] = mainMatrix[mati][matj];
                        temp_j++;
                        if (temp_j == row_size - 1)
                        {
                            temp_i++;
                            temp_j = 0;
                        }
                    }
            }


            if ((i + j) % 2 == 0)
                sign = 1;
            else
                sign = -1;


            adjointMatrix[j][i] = sign * calc_determinant(row_size - 1, column_size - 1, temp);
        }
    }
}
bool calc_inverse(int row_size, int column_size, long long mainMatrix[][15], double inverse[][15])
{
    long long determinantValue = calc_determinant(row_size, column_size, mainMatrix);
    if (determinantValue != 0)
    {
        long long adjMatrix[15][15];
        calc_adjoint(row_size, column_size, mainMatrix, adjMatrix);

        for (int i = 0; i < row_size; i++)
        {
            for (int j = 0; j < column_size; j++)
                inverse[i][j] = adjMatrix[i][j] / (double)determinantValue;
        }
        return true;
    }
    return false;
}
int main()
{
    int Arow, Acol, Brow, Bcol;
    long long A[15][15], B[15][15];
    cout << "Please enter dimensions of Matrix A:" << endl;
    cin >> Arow >> Acol;
    cout << "Please enter dimensions of Matrix B:" << endl;
    cin >> Brow >> Bcol;

    cout << "Please enter values of Matrix A:" << endl;
    for (int i = 0; i < Arow; i++)
    {
        for (int j = 0; j < Acol; j++)
        {
            cin >> A[i][j];
        }
    }
    cout << "Please enter values of Matrix B:" << endl;
    for (int i = 0; i < Brow; i++)
    {
        for (int j = 0; j < Bcol; j++)
        {
            cin >> B[i][j];
        }
    }
    int UserInput;
    do {
        cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):" << endl;
        cin >> UserInput;
        if (UserInput == 1)
        {
            if (Arow == Brow && Acol == Bcol)
                calc_addition(Arow, Acol, A, B);
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
        }
        else if (UserInput == 2)
        {
            if (Arow == Brow && Acol == Bcol)
                calc_subtraction(Arow, Acol, A, B);
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
        }
        else if (UserInput == 3)
        {
            if (Acol == Brow)
                calc_multiplication(Arow, Bcol, Acol, A, B);
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;

            }
        }
        else if (UserInput == 4)
        {
            if (Brow == Bcol && Acol == Brow)
            {
                double BInverse[15][15];
                if (calc_inverse(Brow, Bcol, B, BInverse))
                {
                    double multiplication = 0;
                    for (int i = 0; i < Arow; ++i)
                    {
                        for (int j = 0; j < Bcol; ++j) {

                            for (long long k = 0; k < Acol; ++k)
                            {
                                multiplication += (double)A[i][k] * BInverse[k][j];
                            }
                            cout << (long long)round(multiplication) << " ";
                            multiplication = 0;
                        }
                        cout << endl;
                    }
                }
                else
                {
                    cout << "The operation you chose is invalid for the given matrices." << endl;
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
        }
        if (UserInput == 5) {
            if (Arow == Acol) {
                cout << calc_determinant(Arow, Acol, A) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;
            }
        }
        if (UserInput == 6) {
            if (Brow == Bcol) {
                cout << calc_determinant(Brow, Bcol, B) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices." << endl;

            }
        }
        if (UserInput == 7)
        {
            cout << "Thank you!";

        }
    } while (UserInput != 7);

    return 0;

}