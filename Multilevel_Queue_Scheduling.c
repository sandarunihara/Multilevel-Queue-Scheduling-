
#define MAX_PROCESSES 100


typedef struct process {
    int p_id;
    int priority;
    int burst_time;
    int remaining_time;
} Process;
int size=0;

void enqueueprocess(Process *q, int *size, Process p) {
    q[*size] = p;
    (*size)++;
}

Process dequeueprocess(Process *q, int *size) {
    Process ex = q[0];
    (*size)--;
    for (int i = 0; i < (*size); i++) {
        q[i] = q[i + 1];
    }
    return ex;
}


void roundRobin(Process *q,int *size,int quantumtime,int shift_time){
    while(shift_time!=0 && *size>0){
        if(shift_time>=quantumtime){
            Process tmp=dequeueprocess(q,size);
            if(tmp.remaining_time>=quantumtime){
                shift_time=shift_time-quantumtime;
                tmp.remaining_time=tmp.remaining_time-quantumtime;
                if(tmp.remaining_time==0){
                    printf("Process %d is executing and completed\n", tmp.p_id);
                }else{
                    enqueueprocess(q,size,tmp);
                     printf("Process %d is executed  %d seconds and remaining %d seconds\n", tmp.p_id,quantumtime,tmp.remaining_time);
                }
            }else{
                shift_time=shift_time-tmp.remaining_time;
                tmp.remaining_time=0;
                printf("Process %d is executing and completed\n", tmp.p_id);
            }
        }else{
            if(q[0].remaining_time<=shift_time){
                shift_time=shift_time-q[0].remaining_time;
                q[0].remaining_time=0;
                dequeueprocess(q,size);
                printf("Process %d is executing and completed\n", q[0].p_id);
            }else{
                q[0].remaining_time=q[0].remaining_time-shift_time;
                printf("Process %d is executed  %d seconds and remaining %d seconds\n", q[0].p_id,shift_time,q[0].remaining_time);
                shift_time=0;
                
            }
        }
    }
    printf("\n");

}


void shortestJobFirst(Process *q,int *size,int shift_time){
    while(shift_time!=0 && *size>0){
        int shortprocessID=0;
        for(int i=1;i<*size;i++){
            if(q[i].remaining_time<q[shortprocessID].remaining_time){
                shortprocessID=i;
            }
        }
        Process tmp=dequeueprocess(q+shortprocessID,size);
        if(tmp.remaining_time>=shift_time){
            tmp.remaining_time=tmp.remaining_time-shift_time;
            shift_time=0;
            if(tmp.remaining_time==0){
                printf("Process %d is executing and completed\n", tmp.p_id);
            }else{
                enqueueprocess(q,size,tmp);
                printf("Process %d is executed  %d seconds and remaining %d seconds\n", tmp.p_id,20,tmp.remaining_time);
            }
            
        }else{
            shift_time=shift_time-tmp.remaining_time;
            tmp.remaining_time=0;
            printf("Process %d is executing and completed\n", tmp.p_id);
        }
    }
        printf("\n");

}


void firstInFirstOut(Process *q,int *size,int shift_time){
    while(shift_time!=0 && *size>0){
        if(q[0].remaining_time>shift_time){
            q[0].remaining_time=q[0].remaining_time-shift_time;
            printf("Process %d is executed  %d seconds and remaining %d seconds\n", q[0].p_id,shift_time,q[0].remaining_time);
            shift_time=0; 
        }else{
            shift_time=shift_time-q[0].remaining_time;
            q[0].remaining_time=0;
            printf("Process %d is executing and completed\n", q[0].p_id);
            dequeueprocess(q,size);
        }
    }
        printf("\n");

}


int main(){

    Process q0[MAX_PROCESSES], q1[MAX_PROCESSES], q2[MAX_PROCESSES], q3[MAX_PROCESSES];
    int q0_size = 0, q1_size = 0, q2_size = 0, q3_size = 0;

    int num_processes,quantumtime,shift_time=20;
    printf("Enter the total number of processes: ");
    scanf("%d",&num_processes);

    printf("\n--------------------------------------------------\n\n");

    for(int i=1;i<=num_processes;i++){
        Process new_process;
        new_process.p_id=i;
        printf("Enter process %d burst time: ",i);
        scanf("%d",&new_process.burst_time);
        printf("Enter process priority(0-3): ");
        scanf("%d",&new_process.priority);
        new_process.remaining_time=new_process.burst_time;

        switch(new_process.priority){
            case 0:
                enqueueprocess(q0,&q0_size,new_process);
                printf("...Saved...\n");
                break;
            case 1:
                enqueueprocess(q1,&q1_size,new_process);
                printf("...Saved...\n");
                break;
            case 2:
                enqueueprocess(q2,&q2_size,new_process);
                printf("...Saved...\n");
                break;
            case 3:
                enqueueprocess(q3,&q3_size,new_process);
                printf("...Saved...\n");
                break;
        }

    }

    printf("\nEnter the time quantumtime for roundRobin queue: ");
    scanf("%d",&quantumtime);

    printf("\n--------------------------------------------------\n\n");

    while(q0_size>0 || q1_size>0 || q2_size>0 || q3_size>0){
        if(q0_size>0){
            roundRobin(q0,&q0_size,quantumtime,shift_time);
        }
        if(q1_size>0){
            shortestJobFirst(q1,&q1_size,shift_time);
        }
        if(q2_size>0){
            shortestJobFirst(q2,&q2_size,shift_time);
        }
        if(q3_size>0){
            firstInFirstOut(q3,&q3_size,shift_time);
        }

    }

    printf("\n------ALL PROCESS COMPLETE------\n\n");

}
