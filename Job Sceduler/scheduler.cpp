
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

    public:
        Scheduler(IScheduleStartegy *strat){
            strategy=strat;
        }

        void addJob(Job job){
            jobs.push_back(job);
        }

        vector<Job> getSequence(){
            vector<Job>res = strategy->setStrategy(jobs);
            return res;
        }


};

int main(){

    
    IScheduleStartegy* strategy = new FIFOStartegy();

    Scheduler scheduler(strategy);

    scheduler.addJob({"JobA",1,User::admin,Priority::p0,3,7});
    scheduler.addJob({"JobB",1,User::root,Priority::p0,3,8});
    scheduler.addJob({"JobC",1,User::user,Priority::p1,1,3});

    vector<Job> scheduledSequence = scheduler.getSequence();
    for (const auto& job : scheduledSequence) {
        cout << job.name << " (Arrival: " << job.arivalTime << ")\n";
    }

    delete strategy;

    return 0;
}



