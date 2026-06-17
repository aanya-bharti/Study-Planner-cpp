#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
using namespace std;

struct chapter{
    string name;
    int difficulty;
    bool completed;
};
struct Subject{
    string name;
    vector <chapter> chapters;
};

void datadisplay(const vector<Subject> &subjects){
    cout<<"\n==== STUDY PLAN SUMMARY ====\n"<<endl;
    for(int i=0;i<subjects.size();i++){
        cout<<i<<"."<<"Subject: "<<subjects[i].name<<endl;
        for(int j=0;j<subjects[i].chapters.size();j++){
            cout<<j<<"."<<"Chapter: "<<subjects[i].chapters[j].name<<endl;
            cout<<"Difficulty: "<<subjects[i].chapters[j].difficulty<<endl;
            cout<<"Completed: "<<(subjects[i].chapters[j].completed ? "Yes" : "No")<<endl;
        }
    }
}

void saveData(const vector<Subject>& subjects){
    ofstream file("study_plan.txt");
    if(!file){
        cout<<"Error opening file for writing!"<<endl;
        return;
    }
    cout << "Saving data now..." << endl;
    file<< subjects.size()<<endl;

    for(int i=0;i<subjects.size();i++){
        file<<subjects[i].name<<endl;
        file<<subjects[i].chapters.size()<<endl;
        for(int j=0;j<subjects[i].chapters.size();j++){
            file<<subjects[i].chapters[j].name<<endl;
            file<<subjects[i].chapters[j].difficulty<<endl;
            file<<subjects[i].chapters[j].completed<<endl;
        }
    }
    file.close();
}

void loadData(vector<Subject>& subjects){
    subjects.clear();
    int numsubjects;
    ifstream file("study_plan.txt");
    if(!file){
        cout<<"No saved data found!"<<endl;
        return;
    }
    file>>numsubjects;
    file.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input
    for(int i=0;i<numsubjects;i++){
        Subject subject1;
        getline(file,subject1.name);
        int numchapters;
        file>>numchapters;
        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input
        for(int j=0;j<numchapters;j++){
            chapter chapter1;
            getline(file,chapter1.name);
            file>>chapter1.difficulty;
            file>>chapter1.completed;
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input
            subject1.chapters.push_back(chapter1);
        }
        subjects.push_back(subject1);
    }
}

void showProgress(const vector<Subject>& subjects){
    cout<<"\n==== PROGRESS SUMMARY ====\n"<<endl;
    for(int i=0;i<subjects.size();i++){
        int completedChapters=0;
        for(int j=0;j<subjects[i].chapters.size();j++){
            if(subjects[i].chapters[j].completed){
                completedChapters++;
            }
        }
        float ProgressPercentage = (subjects[i].chapters.size() > 0) ? (static_cast<float>(completedChapters) / subjects[i].chapters.size()) * 100 : 0;
        cout<<"Subject: "<<subjects[i].name<<endl;
        cout<<"Completed Chapters: "<<completedChapters<<"/"<<subjects[i].chapters.size()<<endl;
        cout<<"Progress: "<<ProgressPercentage<<"%"<<endl;
    }
}

void NewStudyPlan(vector<Subject> &subjects){
    int numsubjects;
    cout<<"How many subjects are you studying?"<<endl;
    cin>>numsubjects;
    for(int i=0;i<numsubjects;i++){
        Subject subject1;
        string subjectname;
        cout<<"What is the name of subject "<<i+1<<"?"<<endl;
        cin>>subjectname;
        subject1.name=subjectname;
        cout<<"How many chapters are there in "<<subjectname<<"?"<<endl;
        int numchapters;
        cin>>numchapters;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        for(int j=0;j<numchapters;j++){
            chapter chapter1;
            cout<<"What is the name of chapter "<<j+1<<"?"<<endl;
            getline(cin,chapter1.name);
            cout<<"On a scale of 1-5, how difficult is "<<chapter1.name<<"?"<<endl;
            cin>>chapter1.difficulty;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            chapter1.completed=false;
            subject1.chapters.push_back(chapter1);
        }
        subjects.push_back(subject1);    
    }}

void deletechapter(vector <Subject> &subjects){
    datadisplay(subjects);
    int subjectIndex, chapterIndex;
    cout<<"Enter the Subject index of the chapter yopu want to delete: ";
    cin>>subjectIndex;
    cout<<"Enter the Chapter index of the chapter you want to delete: ";
    cin>>chapterIndex;
    if(subjectIndex >= 0 && subjectIndex < subjects.size() && chapterIndex >= 0 && chapterIndex < subjects[subjectIndex].chapters.size()) {
        subjects[subjectIndex].chapters.erase(subjects[subjectIndex].chapters.begin() + chapterIndex);
        cout << "Chapter deleted successfully!" << endl;
    } else {
        cout << "Invalid indices!" << endl;
    }
}

void deleteSubject(vector <Subject> &subjects){
    datadisplay(subjects);
    int subjectIndex;
    cout<<"Enter the Subject index of the subject you want to delete: ";
    cin>>subjectIndex;
    if(subjectIndex >= 0 && subjectIndex < subjects.size()) {
        subjects.erase(subjects.begin() + subjectIndex);
        cout << "Subject deleted successfully!" << endl;
    } else {
        cout << "Invalid index!" << endl;
    }
}


int main(){
    cout<<"welcome to your personalized study plan generator!"<<endl;
    cout<<"What would you like to be called?"<<endl;
    string nameperson;
    cin>>nameperson;
    cout<<"Hi "<<nameperson<<endl;
    vector<Subject> subjects;
    int option;
    cout<<"==== MENU ====\n"<<endl;
    cout<<"1. Create a new study plan"<<endl;
    cout<<"2. Load existing study plan"<<endl;
    cout<<"Enter your choice: ";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input
    if(option==1){
        cout<<"Let's create your study plan!"<<endl;
        NewStudyPlan(subjects);
    }
    else if(option==2){
        loadData(subjects);
        cout<<"Study plan loaded successfully!"<<endl;}
    
    while(true){
        int choice;
        cout<<"\n==== MENU ====\n"<<endl;
        cout<<"1. Display Study Plan Summary"<<endl;
        cout<<"2. Mark Chapter as Completed"<<endl;
        cout<<"3. Save Study Plan"<<endl;
        cout<<"4. Load Study Plan"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"6. Show Progress"<<endl;
        cout<<"7. Delete a Chapter"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input
        switch(choice){
            case 1:
                datadisplay(subjects);
                break;
            case 2:
                datadisplay(subjects);
                int subjectIndex, chapterIndex;
                cout<<"Enter the subject index: ";
                cin>>subjectIndex;
                cout<<"Enter the chapter index): ";
                cin>>chapterIndex;
                if(subjectIndex>=0 && subjectIndex<subjects.size() && chapterIndex>=0 && chapterIndex<subjects[subjectIndex].chapters.size()){
                    subjects[subjectIndex].chapters[chapterIndex].completed=true;
                    cout<<"Chapter marked as completed!"<<endl;
                }else{
                    cout<<"Invalid indices!"<<endl;
                }
                saveData(subjects);
                break;
            case 3:
                saveData(subjects);
                break;
            case 4:
                loadData(subjects);
                break;
            case 5:
                cout<<"Exiting program. Goodbye!"<<endl;
                return 0;
            case 6:
                showProgress(subjects);
                break;
            case 7:
                deletechapter(subjects);
                saveData(subjects);
                break;
            default:
                cout<<"Invalid choice! Please try again."<<endl;
        }
        
    }
    return 0;
}
    


   
    



