#include <iostream>
#include <string>

using namespace std;

string readBinary(int x)
{
    string result = "";
    while (x > 0)
    {
        result = to_string(x % 2) + result;
        x /= 2;
    }
    while (result.length() < 32)
    {
        result = "0" + result;
    }
    return result;

    // string result = "";
    // for (int i = 31; i >= 0; i--)
    // {
    //     result += to_string((x >> i) & 1);
    // };
    // return result;
}

int32_t readIntFromArrayBinary(int A[32])
{
    int32_t result = 0;
    for (int i = 0; i < 32; i++)
    {
        result = result | (A[i] << (31 - i));
    }
    return result;
}

int *add2Bin(int (&A)[8], int (&B)[8])
{
    int carry = 0;
    int *sum = new int[8]();

    for (int i = 7; i >= 0; i--)
    {
        sum[i] = A[i] ^ B[i] ^ carry;
        carry = (A[i] & B[i]) | (A[i] & carry) | (B[i] & carry);
    }

    return sum;
}

int *sub2Bin(int (&A)[8], int (&B)[8])
{
    // Chuyển B thành bù 1
    for (int i = 0; i < 8; i++)
    {
        B[i] = !B[i];
    }
    // Chuyển B thành bù 2
    int carry = 1;
    for (int i = sizeof(B) / sizeof(B[0]) - 1; i >= 0; i--)
    {
        int sum = B[i] ^ carry;
        carry = B[i] & carry;
        B[i] = sum;
    }

    // Cộng A và B sau khi chuyển B thành bù 2
    int *sum = add2Bin(A, B);
    return sum;
}

int *mul2Bin(const int (&M)[8], const int (&Q)[8])
{
    int *result = new int[17]; //[C, A, Q]
    int A[8] = {0};
    int C = 0;
    int k = 8;

    int Q_copy[8];
    for (int i = 0; i < 8; ++i)
    {
        Q_copy[i] = Q[i];
    }

    while (k > 0)
    {
        if (Q_copy[7] == 1)
        {
            // Nếu bit cuối của Q là 1 thì cộng M vào A
            int carry = 0;
            for (int i = 0; i < 8; ++i)
            {
                int sum = A[i] + M[i] + carry;
                A[i] = sum % 2;
                carry = sum / 2;
            }
            C = carry;
        }

        // Shift right [C, A, Q]
        for (int i = 7; i > 0; --i)
        {
            Q_copy[i] = Q_copy[i - 1];
        }
        Q_copy[0] = A[7];
        for (int i = 7; i > 0; --i)
        {
            A[i] = A[i - 1];
        }
        A[0] = C;
        C = 0;

        k--;
    }

    // Combine [C, A, Q] into result
    result[0] = C;
    for (int i = 0; i < 8; ++i)
    {
        result[i + 1] = A[i];
        result[i + 9] = Q_copy[i];
    }

    return result;
}

int main()
{
    // ---------------------------------------------------------
    int C[8] = {0, 0, 0, 0, 0, 0, 1, 1}; // 3
    int D[8] = {0, 0, 0, 0, 0, 1, 0, 1}; // 5

    int *mul = mul2Bin(C, D);
    cout << "Mul: ";
    for (int i = 0; i < 17; i++)
    {
        cout << mul[i] << " ";
    }
    cout << endl;
    delete[] mul;
    // ---------------------------------------------------------
    int E[8] = {0, 1, 0, 1, 1, 0, 1, 0}; // 90
    int F[8] = {0, 1, 1, 0, 1, 0, 1, 0}; // 106
    int *sub = sub2Bin(E, F);
    cout << "Sub: ";
    for (int i = 0; i < 8; i++)
    {
        cout << sub[i] << " ";
    }
    cout << endl;
    delete[] sub;
    // ---------------------------------------------------------
    int G[8] = {0, 1, 0, 1, 1, 0, 1, 0}; // 90
    int H[8] = {0, 1, 1, 0, 1, 0, 1, 0}; // 106
    int *sum = add2Bin(G, H);
    cout << "Sum: ";
    for (int i = 0; i < 8; i++)
    {
        cout << sum[i] << " ";
    }
    cout << endl;
    delete[] sum;

    // ---------------------------------------------------------
    // Câu 1 :
    // int x;
    // cout << "Nhap so nguyen X: ";
    // cin >> x;
    // cout << "Day bit nhi phan cua " << x << " la: " << readBinary(x) << endl;

    // int A[32] = {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0};
    // cout << "So nguyen X tu day bit nhi phan la: " << readIntFromArrayBinary(A) << endl;
    return 0;
}
