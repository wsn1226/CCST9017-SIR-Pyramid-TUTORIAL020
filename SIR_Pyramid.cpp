#include <iostream>
#include <math.h>
using namespace std;
double LSM(int fall, int max, double a[]);

int main()
{
    double ratio1, ratio2, smin, alphamin, gammamin, a = pow(10, -10), b = pow(10, -3), S0 = 600000, min = pow(10, 11);
    double S[150], I[150], R[150], deltaS[150];
    int thirtythousand, start, max, fall, whensequal0;
    for (int SJ = S0; SJ < 1000000; SJ += 100000)
    {
        for (double gamma = 0.001; gamma <= 0.3; gamma += b) //traverse gamma from 0.001 to 1
        {
            for (double alpha = pow(10, -8); alpha <= pow(10, -6); alpha += a) //traverse alpha from 10^-8 to 10^-6
            {
                whensequal0 = 150, S[0] = SJ, I[0] = 100, R[0] = 0, deltaS[0] = 0; //initialize all parameters
                for (int i = 1; i < 150; i++)
                {
                    S[i] = S[i - 1] - alpha * S[i - 1] * I[i - 1]; //use the formula of SIR model
                    I[i] = I[i - 1] + alpha * S[i - 1] * I[i - 1] - gamma * I[i - 1];
                    R[i] = R[i - 1] + gamma * I[i - 1];
                    deltaS[i] = S[i - 1] - S[i]; //namely the new joins in the graph
                    if (S[i] <= 0)
                    {
                        whensequal0 = i; //if S<=0, terminate this loop immediately
                        break;
                    }
                }
                if (whensequal0 >= 12)
                {

                    for (int j = 0; j < whensequal0 - 4; j++)
                    {

                        if (deltaS[j] > 30000) //find the 30000 value in deltaS
                        {
                            thirtythousand = j;
                            break;
                        }
                    }
                    for (int j = 0; j < whensequal0 - 2; j++) //find the maximum value in deltaS
                    {
                        if (deltaS[j + 1] < deltaS[j])
                        {
                            max = j;
                            break;
                        }
                    }

                    for (int j = 0; j < max; j++) //find the lefthand side of MAX
                    {
                        if (deltaS[j] > deltaS[max] - 54000)
                        {
                            start = j;
                            break;
                        }
                    }
                    for (int j = max; j < whensequal0; j++) //find the righthand side of LEFT
                    {
                        if (deltaS[j] < deltaS[max] - 54000)
                        {
                            fall = j;
                            break;
                        }
                    }
                    if (fall - max > 0 && start - thirtythousand > 0)
                    {
                        ratio1 = (max - start) / (fall - max);
                        ratio2 = (max - start) / (start - thirtythousand);
                    }
                    if (ratio1 >= 0.8 && ratio1 <= 1.2 && ratio2 >= 0.8 && ratio2 <= 1.2 && deltaS[max] >= 90000 && deltaS[max] <= 110000)
                    {
                        double result = LSM(fall, max, deltaS);
                        if (result < min)
                        {
                            min = result;
                            smin = SJ;
                            alphamin = alpha;
                            gammamin = gamma;
                        }
                    }
                }
            }
        }
    }
    cout << "The best pair of (α,γ,S0) is:" << endl
         << "(" << alphamin << ", " << gammamin << ", " << smin << ")" << endl;
}
// This is the function LSM
double LSM(int fall, int max, double a[])
{
    int distance = (fall - max) / 2;
    double Least_squares = 0;
    double standard[12] = {19000, 19500, 20000, 20000, 22000, 30000, 38000, 40000, 81000, 100000, 84000, 46000};
    for (int i = 12; i > 0; i--)
    {
        Least_squares += (a[fall - (12 - i) * distance] - standard[i - 1]) * (a[fall - (12 - i) * distance] - standard[i - 1]);
    }
    return Least_squares;
}