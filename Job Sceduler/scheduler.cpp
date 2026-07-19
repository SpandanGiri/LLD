
#include<bits/stdc++.h>
using namespace std;

enum class User{
    root=0,
    admin =1,
    user=1
};

enum class Priority{
    p0 = 0,
    p1 = 1,
    p2 = 2,
};

class Job{
    
    public:
        string name;
        int id;
        User user;
        Priority priority;
        int arivalTime;
        int duration;

};

class IScheduleStartegy{

    public:
    ~IScheduleStartegy()=default;
    virtual vector<Job> setStrategy(vector<Job>jobs)=0;

};

class FIFOStartegy:public IScheduleStartegy{


    static bool  sortLogic(Job &j1,Job &j2){
        if(j1.arivalTime==j2.arivalTime)    return j1.priority<j2.priority;
        return j1.arivalTime<j2.arivalTime;
    }

        vector<Job>res;

        vector<Job> setStrategy(vector<Job>jobs){
            sort(jobs.begin(),jobs.end(),sortLogic);
            res=jobs;
            return res;
        }

};

class SJFStartegy:public IScheduleStartegy{


    static bool  sortLogic(Job &j1,Job &j2){
        if(j1.duration==j2.duration)    return j1.priority<j2.priority;
        return j1.duration<j2.duration;
    }
    
        vector<Job>res;

        vector<Job> setStrategy(vector<Job>jobs){
            sort(jobs.begin(),jobs.end(),sortLogic);
            res=jobs;
            return res;
        }

};

class Scheduler{

    vector<Job>jobs;
    IScheduleStartegy* strategy;
    vector<vector<Job>>threads;

    public:
        Scheduler(IScheduleStartegy *strat){
            strategy=strat;
        }

        void addJob(Job job){
            jobs.push_back(job);
        }

        vector<vector<Job>> getSequence(int numberOfThreads){

            vector<Job>res=strategy->setStrategy(jobs);

            vector<vector<Job>>threads(numberOfThreads);
            
            int i=0;
            for(auto job:res){
                threads[i%numberOfThreads].push_back(job);
                i++;
            }

            return  threads;
        }


};

int main(){

    
    IScheduleStartegy* strategy = new FIFOStartegy();

    Scheduler scheduler(strategy);

    scheduler.addJob({"JobA",1,User::admin,Priority::p0,3,7});
    scheduler.addJob({"JobB",28,User::root,Priority::p0,3,8});
    scheduler.addJob({"JobC",45,User::user,Priority::p1,1,3});
    scheduler.addJob({"JobD",12,User::user,Priority::p2,12,15});

    vector<vector<Job>> scheduledSequence = scheduler.getSequence(2);


    for (int i = 0; i < scheduledSequence.size(); i++) {
        cout << "Thread " << i << ": ";
        for (const Job& job : scheduledSequence[i]) {
            cout << job.name << " ";
        }
        cout << endl;
    }

    delete strategy;

    return 0;
}



