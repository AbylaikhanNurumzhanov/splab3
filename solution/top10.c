#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int A[2]; // pipe A  |
    pipe(A);
    pid_t pid1 = fork(); // grep
    if (!pid1) {
        dup2(A[1], 1); // duplicates descriptors from to another
        close(A[0]);
        close(A[1]);
        execlp("grep","grep", "10/Oct/2006", "log.txt", NULL);
        exit(EXIT_FAILURE);
    }
    
    int B[2]; // pipe B
    pipe(B);
    pid_t pid2 = fork();
    if (!pid2) { // cut
        dup2(A[0], 0);
        close(A[0]);
        close(A[1]);
        
        dup2(B[1], 1);
        close(B[0]);
        close(B[1]);
        
        execlp("cut","cut", "-f12", "-d ", "-", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(A[0]);
    close(A[1]);
    
    int C[2]; // pipe C
    pipe(C);
    
    pid_t pid3 = fork();
    if (!pid3) { // cut
        dup2(B[0], 0);
        close(B[0]);
        close(B[1]);
        
        dup2(C[1], 1);
        close(C[0]);
        close(C[1]);
        
        execlp("cut","cut", "-f1", "-d/", "-", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(B[0]);
    close(B[1]);
    
    
    int D[2]; // pipe D
    pipe(D);
    
    pid_t pid4 = fork();
    if (!pid4) { // sed
        dup2(C[0], 0);
        close(C[0]);
        close(C[1]);
        
        dup2(D[1], 1);
        close(D[0]);
        close(D[1]);
        
        execlp("sed", "sed", "s/[^A-Za-z]*//g", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(C[0]);
    close(C[1]);
    
    int E[2]; // pipe E
    pipe(E);
    
    pid_t pid5 = fork();
    if (!pid5) { // grep
        dup2(D[0], 0);
        close(D[0]);
        close(D[1]);
        
        dup2(E[1], 1);
        close(E[0]);
        close(E[1]);
        
        execlp("grep","grep", ".", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(D[0]);
    close(D[1]);
    
    int F[2]; // pipe F
    pipe(F);
    
    pid_t pid6 = fork();
    if (!pid6) { // sort
        dup2(E[0], 0);
        close(E[0]);
        close(E[1]);
        
        dup2(F[1], 1);
        close(F[0]);
        close(F[1]);
        
        execlp("sort","sort", "-k1", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(E[0]);
    close(E[1]);
    
    int G[2]; // pipe G
    pipe(G);
    
    pid_t pid7 = fork();
    if (!pid7) { // uniq
        dup2(F[0], 0);
        close(F[0]);
        close(F[1]);
        
        dup2(G[1], 1);
        close(G[0]);
        close(G[1]);
        
        execlp("uniq","uniq", "-c", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(F[0]);
    close(F[1]);
    
    int H[2]; // pipe H
    pipe(H);
    
    pid_t pid8 = fork();
    if (!pid8) { // sort
        dup2(G[0], 0);
        close(G[0]);
        close(G[1]);
        
        dup2(H[1], 1);
        close(H[0]);
        close(H[1]);
        
        execlp("sort", "sort", "-r", "-k1", "-n", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(G[0]);
    close(G[1]);
    
    int I[2]; // pipe I
    pipe(I);
    
    pid_t pid9 = fork();
    if (!pid9) { // cat
        dup2(H[0], 0);
        close(H[0]);
        close(H[1]);
        
        dup2(I[1], 1);
        close(I[0]);
        close(I[1]);
        
        execlp("cat", "cat","-n", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(H[0]);
    close(H[1]);
    
    int J[2]; // pipe J
    pipe(J);
    
    pid_t pid10 = fork();
    if (!pid10) { // awk
        dup2(I[0], 0);
        close(I[0]);
        close(I[1]);
        
        dup2(J[1], 1);
        close(J[0]);	
        close(J[1]);
        
        execlp("awk", "awk", " { print $1 \". \" $3 \" - \" $2 \" - \" int($2*100/342) \"%\" } ", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(I[0]);
    close(I[1]);
    
    
    pid_t pid11 = fork();
    if (!pid11) { // head
        dup2(J[0], 0);
        close(J[0]);
        close(J[1]);
        execlp("head", "head", NULL);
        exit(EXIT_FAILURE);
    }
    
    close(J[0]);
    close(J[1]);
    waitpid(pid11, 0, 0);
}
