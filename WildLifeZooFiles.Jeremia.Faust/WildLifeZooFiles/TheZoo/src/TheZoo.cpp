//Jeremia Faust
//4/19/20


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <jni.h>
using namespace std;

int i=0;
vector<string> zooFile(100);//vector to store data from file

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal()
{
	//declared variables
	string animalData;
	string trackNumber;
	string animalName;
	string animalType;
	string animalSubType;
	string eggs;
	string Nurse;
	char userInput;
//accept user input and formats each variable.
	cout << ("Track Number: ")<<endl;
	cin >> trackNumber;
	trackNumber.insert(trackNumber.begin(), 7 - trackNumber.length(),'0');
	trackNumber.append( 1,' ');

	cin.ignore();
	cout << ("Enter Animal Name: ")<<endl;
	getline(cin,animalName);
	animalName.append( 17 - animalName.length(),' ');

	cout << ("Enter Animal Type: ") << endl;
	getline(cin,animalType);
	animalType.append( 17 - animalType.length() ,' ');

	cout << ("Enter Animal Sub-type: ")<<endl;
	getline(cin,animalSubType);
	animalSubType.append(17 - animalSubType.length(),' ');

	cout <<("Enter Number of Eggs: ")<<endl;
	cin >> eggs;
	eggs.append(1,' ');

	cout << ("Enter 1 if Nursing, 0 if not: ")<< endl;
	cin >> Nurse;

	// variable that appends user input into one line.
	animalData=trackNumber + animalName + animalType +animalSubType+eggs+Nurse;
	cout << "Do you want to save the current data? (y for yes)" << endl ;
	cout << "Track#" << "  Name" << "             Type"<< "             Sub_type" << "         Eggs" << " Nurse" << endl;
	cout << "**************************************************************************" << endl << animalData << endl ;
	cin >> userInput;
	//if statement to ive user the chance to not add data
	if (userInput == 'y'){
		zooFile.push_back(animalData); // add data to vector
		cout <<"Data Saved to memory" << endl;
	}
	else{
		cout << "Data not saved."<< endl;
		return;
	}
}


void RemoveAnimal()
{
	string dataLine;
	string trackNumber;
	string temp;
	int j;
	char userInput;
	vector<string>::iterator it = zooFile.begin();

	cout << ("Track Number: ")<<endl;
	cin >> trackNumber;
	trackNumber.insert(trackNumber.begin(), 7 - trackNumber.length(),'0');// formatt user input
//for loop that iterates through entire loop.
	for (j=0; j < zooFile.size();j++){
		dataLine=zooFile.at(j);
		dataLine=dataLine.substr(0, 7);

// nested if statement if a match has been found it will display the data and give user option not to remove data
		if (trackNumber == dataLine){
			cout << "Animal Data found. Are you sure you want to delete animal from file(y for yes)" << endl;
			cout << "Track#" << "  Name" << "             Type"<< "             Sub_type" << "         Eggs" << " Nurse" << endl;
			cout << "**************************************************************************" << endl << zooFile.at(j) << endl ;
			cin >> userInput;

			if (userInput == 'y'){
				it= zooFile.erase(it +j); // erases element from vector

				cout << "Data deleted from memory. " <<  endl;
				break;
			}
		else{
				cout << "Data not deleted." << endl;
				break;
			}


		}
	}
}

void LoadDataFromFile()
{
ifstream zoofile; // input file stream

zoofile.open("zoodata.txt"); //try to open file

// if statement that tests if file opens
if (zoofile.fail()){
	cout << "Could not open file." << endl;
}
else{
	string dataLine;
// while loop that put each line of file into vector
	while (getline(zoofile,dataLine)){

		zooFile.at(i) = dataLine;

		i++;

	}
	cout << "File opened" << endl;
	zooFile.resize(i);// resizes vector

}

}

void SaveDataToFile()
{
	fstream outzoofile; // output file stream
	string fileName = "zoodata.txt"; //variable to hold file name

	outzoofile.open(fileName.c_str(), ifstream::out | ifstream::trunc); // opens file ane deletes contents
	// if statement that tests if file opens
	if (outzoofile.fail()){
		cout << "Could not open file." << endl;
	}
	else{
//itereates each element in vector into file.
		for (int j=0; j < zooFile.size();j++){
			outzoofile << zooFile.at(j) << endl;

		}
		cout << "File Save successfully completed" << endl;
		}


	}



void DisplayMenu()
{
    int userInput;

// while loop iterates until user quits.
    while(userInput != 5){
    	//menu options
    	cout << "               Menu           "<< endl;
    	cout << "*******************************" << endl;

    	cout << "1. Display Animal Data."<< endl;
    	cout << "2. Add Record."<< endl;
    	cout << "3. Delete Record."<< endl;
    	cout << "4. Save Animal Data."<< endl;
    	cout << "5. Quit"<< endl << endl;

    	cout << "Please enter an option." << endl;
    	cin >> userInput;
    	//switch statement to make the menu work. It calls the functions base on user input.
    	switch (userInput){

    	case 1:// displays the animal data
    		cout << "                           Animal data.                              "<< endl;
    		cout << "**************************************************************************" << endl;
    		cout << "Track#" << "  Name" << "             Type"<< "             Sub_type" << "         Eggs" << " Nurse" << endl;
    		cout << "**************************************************************************" << endl ;
    		for (int k=0; k < zooFile.size();k++){

    					cout << zooFile.at(k)<<endl;
    		}
    		system ("Pause");
    		break;
    	case 2:
    		AddAnimal();
    		break;
    	case 3:
    		RemoveAnimal();
    		break;
    	case 4:
    		SaveDataToFile();
    		break;
    	case 5:
    		cout << "Have a good day!!"<< endl;
    		return;
    	default:
    		cout << "Invalid Input. Please try again." << endl ;
    		system ("Pause");
    		DisplayMenu();
    }

	}
}
void DisplayFileMenu(){
	int userInputFileControl;
	// this function is similar to DisplayMenu()but it controls the initial data by generating a new file or loading from a file.
	cout << "       		Welcome to the Wildlife Zoo Animal database:               "<< endl;
	cout << "**************************************************************************" << endl;
    	cout << "1. Load Animal Data From File."<< endl;
    	cout << "2. Generate Animal Data."<< endl << endl;
    	cout << "Please enter an option." << endl;
    	cin >> userInputFileControl;

    	switch (userInputFileControl){
    		case 1:
    			LoadDataFromFile();
    			break;
    		case 2:
    			GenerateData();
    			LoadDataFromFile();
    			break;
    		default:
    	    	cout << "Invalid Input. Please try again." << endl ;
    	    	system("Pause");
    	    	DisplayFileMenu();
    	    	}
    	 }




int main()
{

	DisplayFileMenu();
    DisplayMenu();


	return 1;
}
