// OXO220016
//Ominakhon Omonullaeva
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

//calculates most missed
void MostMissed(int question, double *missedPtr){
   
    missedPtr += question;// moves pointer to index/location of question
    *missedPtr += 1;//adds one to counter for each question
    
    
}//close mostmissed

//calculates students score
double calcScore(char *stuAns, char *testAns, int size){
    double correct= 0;
    double stuScore;
    
    //adds up how many are correct
    for(int i = 0; i < size; i++){
        if(*stuAns == *testAns){
            correct++;
        }
        stuAns++;
        testAns++;
    }
    
    stuScore = (correct / size)* 100;
    
    return stuScore;
}//close calcscore

//outputs wrong answers
void wrongAns(char stuAns[], char testAns[], int size, double missedArray[]){
    char *stuPtr = stuAns;
    char *testPtr = testAns;
    
    //outputs question number
    for(int i = 0; i < size; i++){
        if(*stuPtr != *testPtr){
            
            int question = i;
            cout << question + 1;
            
            // calls function to find the amount of times question was missed
            MostMissed(question, missedArray);
            
            
            if(i+1 < size){
                cout << " ";
            }
        }
        stuPtr++;
        testPtr++;
    }
    
    //resets pointer
    cout << endl;
    stuPtr = stuAns;
    testPtr = testAns;
    
    //outputs wrong answer
    for(int i = 0; i < size; i++){
        if(*stuPtr != *testPtr){
            
            if(i+1 >= 10){
                cout << " ";
            }
            
            cout << stuAns[i];
            
            if(i+1 < size){
                cout << " ";
            }
        }
        stuPtr++;
        testPtr++;
    }
    
    //resets pointer
    cout << endl;
    stuPtr = stuAns;
    testPtr = testAns;
    
    //outputs correct answer
    for(int i = 0; i < size; i++){
        if(*stuPtr != *testPtr){
            
            if(i+ 1 >= 10){
                cout << " ";
            }
            
            cout << testAns[i];
            
            if(i+1 < size){
                cout << " ";
            }
        }
        stuPtr++;
        testPtr++;
    }
    
    cout << endl;
}//close wrong answer function



//main
int main()
{
    //variables
    int count = 0;
    int scoreCount = 0;
    char *ansArray = nullptr;
    char *stuArray = nullptr;
    char ans;
    char stuAns;
    string student;
    string input;
    ifstream answerKey;
    ifstream studentResp;
    
    
    //user input files
    cout << "Enter answer key file: ";
    getline(cin, input);
    answerKey.open(input, ios::in| ios::app);
    cout << endl;
    
    cout << "Enter contest response file: ";
    getline(cin, input);
    studentResp.open(input, ios::in | ios::app);
    cout << endl;
    
    
    //makes sure files are open
    if (!answerKey.is_open()){
    cerr << "Error" << endl;
    return 0;
    }

    if (!studentResp.is_open()){
    cerr << "Error." << endl;
    return 0; 
    }
    
    
    //stores answer key in array
    while(answerKey >> ans){
       char *tempPtr;
       char *ansPtr;
       
    char* temp = new char[count + 1];
    
    tempPtr = temp;
    ansPtr = ansArray;

    for (int i = 0; i < count; i++){
        *tempPtr = *ansPtr;
        tempPtr++;
        ansPtr++;
        
        }//close for

    *tempPtr = ans;
    delete[] ansArray;
    ansArray = temp;
    count++;
    
    }//close while that populates answer key array
    
    //extra pointers and arrays
    double* allScores = new double[count];
    double *scorePtr = allScores;
    double* missed = new double[count];
    int numQuestions = count;
    count = 0;//reset count
    
    
   while(!studentResp.eof()){
        
        studentResp >> student; // holds student ID
        if(isdigit(stuAns)){
           student = stuAns + student;
       }
        
    //stores student answers in array
    while(studentResp >> stuAns && isalpha(stuAns)){
            
        char *tempPtr;
        char *stuPtr;
        
        char* temp = new char[count + 1];
        
        tempPtr = temp;
        stuPtr = stuArray;

     for (int i = 0; i < count; i++){
             *tempPtr = *stuPtr;
             tempPtr++;
             stuPtr++;
        }//close for

        *tempPtr = stuAns;
        delete[] stuArray;
        stuArray = temp;
        count++; 
        
        }// close while that populates student array
       
       //calculates and outputs score
       double score = calcScore(stuArray, ansArray, count);
       cout << student << " - " <<fixed << showpoint << setprecision(2) << score << endl;
       
       //if not perfect score find wrong answers
       if(score != 100){
           wrongAns(stuArray, ansArray, count, missed);
       }
       
       *scorePtr += score;// adds score to point in array
       
       //reset count
       count = 0;
       
       scorePtr++;//adds 1 to pointer
       scoreCount++; //adds 1 to how many student scores there are
       
    }//close student while
    
    sort(allScores, allScores + scoreCount); // sorts array
    scorePtr = allScores; //reset scorePtr
    
     cout << endl;// blank line
     
    //finds mean
    double sum = 0;
    //adds up all scores in array
    for(int i = 0; i < scoreCount; i++){
        scorePtr += i;
        sum += *scorePtr;
        scorePtr = allScores;
    }
    
   double mean = sum / scoreCount;
   cout << "Mean: " << mean << endl; // output mean
   
   
   //finds median
   double median = 0;
   
   //calculates median if length is even or odd
   if(scoreCount % 2 == 0){ //even length
        int middle = scoreCount / 2;//calculates middle index
        
        scorePtr += middle;
        median = *scorePtr;//adds first middle number to median
        
        scorePtr = allScores;//resets pointer
        
        scorePtr += middle - 1;
        median += *scorePtr;;// adds second middle number to median
        
        median /= 2;//divides by 2
       
       cout << "Median: " << median << endl;//output
       
       scorePtr = allScores;//reset pointer
       
   }else{ // odd length
       
       int middle = scoreCount / 2;
       scorePtr += middle;
       median = *scorePtr;
       
       cout << "Median: " << median << endl;
       
       scorePtr = allScores;//reset pointer
   }//closes median if else
    
    //Mode
    double mostNum = 0;
    double previousMode;
    vector<double> mode;
    
    //nested for loops to find mode
    for(double *i = allScores; i < allScores+ scoreCount; i++){ // resets which number it is at
        double num = *i;
        int modeCount = 0;
        
        for(double *j = allScores; j < allScores + scoreCount; j++){ // finds how many times num appears
            if(*j == num){
               modeCount++; //adds 1 if num appears
            }// close counter if
            
        }//close nested for loop
        
        //decides whether there is only one mode or multiple
        if(modeCount > mostNum && num != previousMode){
           
            mostNum = modeCount;
            mode.clear();
            mode.push_back(num);
            previousMode = num;
            
        }else if(modeCount == mostNum && num != previousMode){
            
            mostNum = modeCount;
            mode.push_back(num);
            previousMode = num;
            
        }//close replacement if
        
        scorePtr = allScores; // reset pointer
    }//close mode for loop
    
   //outputs all modes that were valid
    cout << "Mode: ";
    for( long unsigned int i = 0; i < mode.size(); i++){
        
            cout << mode[i];
            
            //decides whether or not to add comma
            if(i + 1 < mode.size()){
            cout << ", ";
            }
            
    }
    
    //new line and most missed questions
    cout << endl << endl;
    cout << "MOST MISSED QUESTIONS" << endl;
    double *missPtr = missed;
   
   //outputs all missed questions and percentage wrong
    for(int i = 0; i < numQuestions ; i++){
        
        double percent = *missPtr / scoreCount;
        percent *= 100;
        
        if(percent >= 60){
            cout << i + 1 << "  " << percent << "%" << endl;
        }
        
        missPtr++;
    }//close missed questions for loop
    
    //close files and delete arrays to avoid memory leaks
    delete[] missed;
    delete[] allScores;
    delete[] ansArray;
    delete[] stuArray;
    answerKey.close();
    studentResp.close();
    return 0;
    
}//close main