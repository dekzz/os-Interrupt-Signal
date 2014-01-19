#include <iostream>
#include <csignal>
#include <ctime>
using namespace std;

int current;
int line[8];
int waitLine[8];

void interruptHandler(int y)
{
 cout << "\nInterrupt attempt " << y <<  endl;
 for (int i=0; i<5; i++)
 {
  cout << "Interrupt " << y << ": " << i+1 << "/5" << endl;
  sleep(1);
 }
 cout << "Interrupt " << y << " failed!" << endl << endl;
}

void interruptRoutine(int sig)
{
 sigset(SIGINT, interruptRoutine);
 int i, x;
 bool replace = false;
 time_t t;
 time(&t);
 cout << "\nInterrupt on " << ctime(&t) << endl;
 cout << "Interrupt priority: ";
 cin >> i;
 waitLine[i] = 1;
 do
 {
  x = 0;
  for(int j = current+1; j < 8; j++)
  {
   if(waitLine[j] != 0)
   {
     x = j;
     replace = true;
   }
  }
  if(!replace)
  {
    cout << endl;
  }
  if(x > 0)
  {
    waitLine[x] = 0;
    line[x] = current;
    current = x;
    interruptHandler(x);
    current = line[x];
  }
 }while(x > 0);
}

int main()
{
 sigset (SIGINT, interruptRoutine);
 cout << "\nFATAL ERROR!" << endl << endl;
 for (int i = 10; i > -1; i--)
 {
  cout << "Crash in " << i << endl;
  sleep(1);
 }
 cout << "\nSystem crashed!" << endl << endl;

 return 0;
}
