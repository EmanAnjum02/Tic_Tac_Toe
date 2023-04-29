#include "Project_2021148_2021276.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Ai_value(double a[], Net myNet)
{
    vector<double> vals;
    for (int i = 0; i < 9; i++) {
        vals.push_back(a[i]);
    }

    double probability[9];
    for (int i = 0; i < 9; i++) {
        probability[i] = 1;
    }

    for (int i = 0; i < 9; i++) {
        if (vals[i] == 0.01) {
            vals[i] = -1;
            myNet.feedForward(vals);
            probability[i] = myNet.getOutput();
            vals[i] = 0.01;
        }
    }

    int index;
    double min = 1;
    for (int i = 0; i < 9; i++) {
        if (probability[i] < min)
            min = probability[i];
        cout << probability[i]  << endl;
    }

    for (int i = 0; i < 9; i++) {
        if (min == probability[i])
            index = i;
    }

    return index;
}

void displaytable(double a[])
{
    // cout << "  0 | 1 | 2 "<< endl;
    // cout << "------------"<< endl;
    // cout << "  3 | 4 | 5 "<< endl;
    // cout << "------------"<< endl; 
    // cout << "  6 | 7 | 8 "<< endl;
    

    for (int i=0; i<9 ;i++)
    {
        if ((i+1)%3==0)
        {
            cout << setw(5) << a[i];
            cout << endl;
            
        }
        else 
        {
            cout << setw(5) << a[i];
        }

        
    }
}

void input_p_1(double a[])
{
    
    bool check=true;
    while(check)
    {
    
        cout << "\nplayer 1"<< endl;
        cout << "enter your desired position = ";
        int pos;
        cin >> pos;
        if (a[pos]!=0.01 || a[pos]!=-1)
        {
            a[pos]=1;
            check=false;
        }
        else 
        {
            cout<< "position entered is already filled try again "<< endl;
        }
        
    }
}


void input_p_2(double a[])
{
    
    bool check=true;
    while(check)
    {
    
        cout << "player 2"<< endl;
        cout << "enter your desired position = ";
        int pos;
        cin >> pos;
        if (a[pos]!=0.01 || a[pos]!=1 )
        {
            a[pos]=-1;
            check=false;
        }
        else 
        {
            cout<< "position entered is already filled try again "<< endl;
        }
        
    }
}

void input_AI(double a[], Net &myNet)
{
    
    bool check=true;
    while(check)
    {
    
        cout << "player 2"<< endl;
        // cout << "enter your desired position = ";
        int pos;
        pos=Ai_value(a,myNet);
        
        if (a[pos]!=0.01 || a[pos]!=1 )
        {
            a[pos]=-1;
            check=false;
        }
        else 
        {
            cout<< "position entered is already filled try again "<< endl;
        }
        
    }
}

bool check(double a[])
{  
    bool result= false;
   for ( int i=0; i< 7 ; i+=3)
   {
       if (a[i]!= 0.01 && (a[i]==a[i+1] && a[i]==a[i+2]))
       {
           cout << "b" << endl;
           if (a[i]==1)
           {
               cout << " Congrats player 1 you have WON the game "<< endl;
               result = true;
           }
           else 
           {
               cout << " Congrats player 2 you have WON the game "<< endl;
               return true;
           }
       }
   }

   for (int i=0 ; i<3 ; i++)
   {
       if (a[i]!=0.01 && (a[i]==a[i+3] && a[i]==a[i+6]))
       {
           cout << "c" << endl;
           if (a[i]==1)
           {
                cout << " Congrats player 1 you have WON the game "<< endl;\
                result = true;
           }
           else
           {
               cout << " Congrats player 2 you have WON the game "<< endl;
               result = true;
           }
       }
   }

   if ((a[0]!=0.01 || a[2]!=0.01) && ( (a[0]==a[4] && a[0]==a[8]) || (a[2]==a[4] && a[2]==a[6]) ) )
   {
       cout << "d" << endl;
        if (a[0]==1 || a[2]==1)
           {
                cout << " Congrats player 1 you have WON the game "<< endl;
                result = true;
           }
        else
           {
               cout << " Congrats player 2 you have WON the game "<< endl;
               result = true;
           }  
   }

    int draw = 0;
   for (int c=0;c<9;c++)
   {
       if(a[c]!=0.01)
       {
           draw++;
       }
   }
   if (draw == 9)
    result = true;

   return result;
}


void playgame(double a[], Net &myNet)
{
    while(!check(a))
    {
        displaytable(a);
       input_p_1(a);
       input_AI(a, myNet);
    }
}


int main ()
{
    
    TrainingData trainData("tic-tac-toe.txt");
    vector<unsigned> topology;
    trainData.getTopology(topology);

    Net myNet(topology);

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainData.isEof()) {
        ++trainingPass;
        // cout << "a";
        cout << endl << "Pass " << trainingPass;
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorVals("Inputs: ", inputVals);
        myNet.feedForward(inputVals);
        myNet.getResults(resultVals);
        showVectorVals("Outputs: ", resultVals);
        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets: ", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);
        cout << "Net recent average error: " << myNet.getRecentAverageError() << endl;
    }

    cout << endl << "Done" << endl;

    double arr[9];
    for (int i = 0; i < 9; i++) {
        arr[i] = 0.01;
    }
    playgame(arr, myNet);
    
    return 0;
}