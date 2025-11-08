#include<iostream>
#include<string>
using namespace std;

struct Task{
    int id;
    string description;
    bool completed;
    Task* next;
};

void addTask(Task*& head,int id,string description){
    Task* check=head;
    while(check){
        if(check->id==id){
            cout<<"Error: Task ID already exists!\n";
            return;
        }
        check=check->next;
    }
    
    Task* newTask=new Task{id,description,false,NULL};
    if(!head){
        head=newTask;
    }else{
        Task* temp=head;
        while(temp->next)temp=temp->next;
        temp->next=newTask;
    }
    cout<<"Task added successfully!\n";
}

void displayTasks(Task* head){
    if(!head){
        cout<<"No tasks found.\n";
        return;
    }
    
    int pendingCount=0,completedCount=0;
    Task* temp=head;
    
    cout<<"\n=== TASK LIST ===\n";
    while(temp){
        string status=temp->completed?"? Completed":"? Pending";
        cout<<"ID: "<<temp->id
             <<" | "<<status
             <<"\nDescription: "<<temp->description<<"\n\n";
        
        if(temp->completed)completedCount++;
        else pendingCount++;
        temp=temp->next;
    }
    cout<<"Summary: "<<pendingCount<<" pending, "<<completedCount<<" completed\n";
}

void markCompleted(Task* head,int id){
    Task* temp=head;
    while(temp){
        if(temp->id==id){
            if(temp->completed){
                cout<<"Task was already completed.\n";
            }else{
                temp->completed=true;
                cout<<"Task marked as completed.\n";
            }
            return;
        }
        temp=temp->next;
    }
    cout<<"Task not found.\n";
}

void markPending(Task* head,int id){
    Task* temp=head;
    while(temp){
        if(temp->id==id){
            if(!temp->completed){
                cout<<"Task was already pending.\n";
            }else{
                temp->completed=false;
                cout<<"Task marked as pending.\n";
            }
            return;
        }
        temp=temp->next;
    }
    cout<<"Task not found.\n";
}

void deleteTask(Task*& head,int id){
    if(!head){
        cout<<"No tasks to delete.\n";
        return;
    }
    
    if(head->id==id){
        Task* toDelete=head;
        head=head->next;
        delete toDelete;
        cout<<"Task deleted successfully.\n";
        return;
    }
    
    Task* temp=head;
    while(temp->next&&temp->next->id!=id){
        temp=temp->next;
    }
    
    if(temp->next){
        Task* toDelete=temp->next;
        temp->next=temp->next->next;
        delete toDelete;
        cout<<"Task deleted successfully.\n";
    }else{
        cout<<"Task not found.\n";
    }
}

void showPendingTasks(Task* head){
    if(!head){
        cout<<"No tasks found.\n";
        return;
    }
    
    bool found=false;
    Task* temp=head;
    cout<<"\n=== PENDING TASKS ===\n";
    while(temp){
        if(!temp->completed){
            cout<<"ID: "<<temp->id
                 <<"\nDescription: "<<temp->description<<"\n\n";
            found=true;
        }
        temp=temp->next;
    }
    if(!found)cout<<"No pending tasks.\n";
}

void cleanup(Task*& head){
    while(head){
        Task* temp=head;
        head=head->next;
        delete temp;
    }
}

int main(){
    Task* head=NULL;
    int choice,id;
    string description;

    cout<<"=== TASK MANAGEMENT SYSTEM ===\n";
    
    do{
        cout<<"\n1. Add Task\n2. Display All Tasks\n3. Show Pending Tasks\n"
             <<"4. Mark Task Completed\n5. Mark Task Pending\n6. Delete Task\n7. Exit\n"
             <<"Enter your choice: ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:
                cout<<"Enter Task ID: "; 
                cin>>id; 
                cin.ignore();
                cout<<"Enter Description: "; 
                getline(cin,description);
                addTask(head,id,description);
                break;
            case 2:
                displayTasks(head);
                break;
            case 3:
                showPendingTasks(head);
                break;
            case 4:
                cout<<"Enter Task ID to mark completed: "; 
                cin>>id;
                markCompleted(head,id);
                break;
            case 5:
                cout<<"Enter Task ID to mark pending: "; 
                cin>>id;
                markPending(head,id);
                break;
            case 6:
                cout<<"Enter Task ID to delete: "; 
                cin>>id;
                deleteTask(head,id);
                break;
            case 7:
                cout<<"Exiting program. Goodbye!\n";
                break;
            default:
                cout<<"Invalid choice. Please try again.\n";
        }
    }while(choice!=7);

    cleanup(head);
    
    return 0;
}
