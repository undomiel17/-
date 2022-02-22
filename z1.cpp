#include <iostream>
#include <cmath>
#include <clocale>
#include <vector>
using namespace std;

double
f (double x)
{
  return pow (2, x) - 2 * cos (x);
}

double
df (double x)
{
  return pow (2, x) * log10 (2) + 2 * sin (x);
}

void
input (double &A, double &B, double &e, int &N)
{
  cout << "Задание 1" << endl;
  cout <<
    "Требуется найти корни нечётной кратности уравнения 2^x- 2*cos(x)"
    << endl;
  cout << "Введите координаты отрезка" << endl;
  while (true)
    {
      cout << "Начало" << endl;
      cin >> A;
      cout << "Конец" << endl;
      cin >> B;
      if (A < B)
	break;
      else
	cout << "Невозможный отрезок" << endl;
    }
  cout << "Введите степень точности" << endl;
  cin >> e;
  e = pow (10, -e);
  cout <<
    "Проведём разделение корней. Введите степень табулирования"<< endl;
  cin >> N;
}

void separation (double &A, double &B, double &h,  vector <double> &segment)
{
  long double  X1=A, X2=A+h;
    cout << "Промежутки, на которых у функции меняется знак: " << endl;

    for ( int i=0; X2<=B; i++)
    {
        if( f(X1)*f(X2)<=0 )
        {
            segment.push_back(i);
            cout << "[" << X1 << " ; " << X2 << "]"<<endl;
        }
        X1 = X2;
        X2 += h;
    }
    cout<<endl;
}

void bisection (double &A, double&B, double &h, vector <double> &segment, double &e){
  cout<<endl;
  cout<<"Метод бисекции" << endl;
    for ( int i=0; i<segment.size(); i++ )
    {
        double a = A+segment.at(i)*h, b = A+(segment.at(i)+1)*h;
        cout << "На отрезке [" << a << " ; " << b << "] корень ";
        while( b - a >= 2*e )
        {
            double c=(a+b)/2;
            if ( f(a)*f(c) <= 0)
                b = c;
            else a = c;
        }
        double root = (a+b)/2;
        cout << root << " с точностью " << (b-a)/2 << endl;
        cout<<"Невязка: "<<abs(f((root)-0))<<endl;
    }
}

void newton (double &A, double&B, double &h, vector <double> &segment, double &e){
  cout<<endl;
  cout<<"Метод Ньютона" << endl;
    for ( int i=0; i<segment.size(); i++ )
    {
        double a = A+segment.at(i)*h, b = A+(segment.at(i)+1)*h;
        cout << "На отрезке [" << a << " ; " << b << "] корень ";
        double x0 = (a+b)/2, x1;
        if (df(x0)!=0)
            x1=x0-f(x0)/df(x0);
            else {
                cout<<"error"<<endl;
                break;
            }
        while( abs(x0 - x1) >= e )
        {
            double x2;
            if (df(x1)!=0)
            x2=x1-f(x1)/df(x1);
            else {
                cout<<"error"<<endl;
                break;
            }
            x0=x1;
            x1=x2;
        }
        double root = x1;
        cout << root << " с точностью " << abs(x1-x0) << endl;
        cout<<"Невязка: "<<abs(f((root)-0))<<endl;
    }
}

void newton_mod (double &A, double&B, double &h, vector <double> &segment, double &e){
    cout<<endl;
    cout<<"Модифицированный метод Ньютона" << endl;
    for ( int i=0; i<segment.size(); i++ )
    {
        double a = A+segment.at(i)*h, b = A+(segment.at(i)+1)*h;
        cout << "На отрезке [" << a << " ; " << b << "] корень ";
        double x0 = (a+b)/2, x1, df_fix;
        if (df(x0)!=0) df_fix=df(x0);
            else {
                cout<<"error"<<endl;
                break;
            }
        x1=x0-f(x0)/df_fix;
        while( abs(x0 - x1) >= e )
        {
            double x2;
            x2=x1-f(x1)/df(x0);
            x0=x1;
            x1=x2;
        }
        double root = x1;
        cout << root << " с точностью " << abs(x1-x0) << endl;
        cout<<"Невязка: "<<abs(f((root)-0))<<endl;
    }
}

void secant (double &A, double&B, double &h, vector <double> &segment, double &e){
  cout<<endl;
  cout<<"Метод секущих" << endl;
    for ( int i=0; i<segment.size(); i++ )
    {
        double a = A+segment.at(i)*h, b = A+(segment.at(i)+1)*h;
        cout << "На отрезке [" << a << " ; " << b << "] корень ";
        double x0 = b, x1=x0-f(x0)/df(x0), x2=x1-f(x1)*(x1-x0)/(f(x1)-f(x0));

        while( fabs(f(x2)) >= e )
        {
            double x3;
            x3=x2-f(x2)*(x2-x1)/(f(x2)-f(x1));
            x0=x1;
            x1=x2;
            x2=x3;
        }
        double root = x2;
        cout << root << endl;
        cout<<"Невязка: "<<abs(f((root)-0))<<endl;

    }
}

int
main ()
{

  setlocale (LC_ALL, "Russian");
  double A, B, e;
  int N;
  input (A, B, e, N);
  double h=(B-A)/N;
  vector < double > segment;
  separation (A, B, h, segment);
  bisection (A, B, h, segment, e);
  newton (A, B, h, segment, e);
  newton_mod (A, B, h, segment, e);
  secant (A, B, h, segment, e);
  return 0;
}

