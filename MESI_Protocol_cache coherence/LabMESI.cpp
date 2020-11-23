#include <iostream> 
#include <unordered_map> 
#include <string> 
#include <list>
#include <iterator>
#include <algorithm>
#include <sstream>
using namespace std; 



#define N_PROCS 4
#define READ 0
#define WRITE 1

unordered_map<int, string> procs; 

bool all_invalid() {
    for (auto val : procs) {
        if (val.second.compare("I") != 0) {
            return false;
        }
    }
    return true;
}

bool one_exclusive() {
    for (auto val : procs) {
        if (val.second.compare("E") == 0) {
            return true;
        }
    }
    return false;
}

bool one_shared() {
    for (auto val : procs) {
        if (val.second.compare("S") == 0) {
            return true;
        }
    }
    return false;
}

bool one_modified() {
    for (auto val : procs) {
        if (val.second.compare("M") == 0) {
            return true;
        }
    }
    return false;
}

bool all_shared() {
    for (auto val : procs) {
        if (val.second.compare("S") != 0) {
            return false;
        }
    }
    return true;
}

struct Pair
{
    int proc;
    int action;
    Pair(int proc_index, int proc_action) :
            proc(proc_index), action(proc_action)
    {
    }
};
int main() 
{ 

    
    std::list<Pair> inputs =
    { Pair(1, READ), Pair(2, READ), Pair(3, READ), Pair(4, READ),
    Pair(1, READ),Pair(1, WRITE), Pair(1, READ), Pair(2, WRITE),
    Pair(3, READ),Pair(4,READ), Pair(4,WRITE), Pair(4,READ)};

    int last_proc_M_or_E = 0;

    cout<<"t0"<<endl;

    for (int i = 1 ; i <= N_PROCS ; i++) {
        procs[i] = "I";
        cout<<"Procesor "<<i<<" stare: I"<<endl;
    }

    int steps = 1;

    std::list<Pair>::iterator it;
    for (it = inputs.begin(); it != inputs.end(); it++) {
        cout<<endl<<"t"<<steps<<endl;

        int procc = it->proc;
        int command = it->action;

        string bus_action = "-";
        string block_source = "-";

        if (command == READ) {
            if (all_invalid() == true) {
                procs[procc] = "E";
                bus_action = "BusRd";
                block_source = "Mem";
                last_proc_M_or_E = procc;
            }
            else if (one_exclusive() == true){
                bool changed = false;

                for (int i = 1; i <= N_PROCS; i++) {
                    if ((i != procc) && (procs[i] == "E")) {
                        procs[i] = "S";
                        changed = true;
                    }
                }
                if (changed == true) {
                    procs[procc] = "S";
                    bus_action = "Flush";
                    int x = last_proc_M_or_E;
                    string str;
                    ostringstream temp;
                    temp << x;
                    str = temp.str();
                    block_source = "Cache" + str;
                }
            }
            else if (one_shared() == true) {
                if (all_shared() == false) {
                    procs[procc] = "S";
                    bus_action = "Flush*";
                    int x = last_proc_M_or_E;
                    string str;
                    ostringstream temp;
                    temp << x;
                    str = temp.str();
                    block_source = "Cache" + str;
                }
            }
            else if (one_modified() == true) {
                if (procs[procc] == "M") {
                        // do nothing
                }
                else
                {
                    for (int i = 1; i <= N_PROCS; i = i + 1) {
                        if ((i == procc) || (procs[i] == "M")) {
                            procs[i] = "S";
                        }
                    }

                    bus_action = "BusRd";
                    int x = last_proc_M_or_E;
                    string str;
                    ostringstream temp;
                    temp << x;
                    str = temp.str();
                    block_source = "Cache" + str;
                }
                
            }
        }
        else if (command == WRITE) {
            block_source = "Flush";
            if (one_shared() == true) {
                block_source = "Flush*";
            }

            procs[procc] = "M";
            last_proc_M_or_E = procc;


            for (int i = 1; i <= N_PROCS; i++) {
                    if (i != procc)
                        procs[i] = "I";
                }
                bus_action = "BusRdX";
        }
        string act = (command == 0) ? "READ" : "WRITE";
        cout<<"Actiune procesor "<<procc<<" este: "<< act<<endl;
        for (int i = 1 ; i <= N_PROCS ; i++) {
            cout<<"Procesor "<<i<<" stare: "<<procs[i]<<endl;
        }
        cout<<"Actiune magistrala: "<<bus_action<<endl;
        cout<<"Sursa date: "<<block_source<<endl;
        steps++;
    }

  
} 