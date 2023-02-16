

/* File whosort.c */
main()
{
    int fds[2];
    pipe(fds);                  /*Crea un pipe */
    /* El primer hijo reconecta su entrada estándar (stdin) al flujo
       de salida del pipe y cierra el descriptor de la entrada del pipe 
    */
    if (fork()  == 0) {
        dup2(fds[0], 0);
        close(fds[1]);
        execpl("sort", "sort", NULL);
    }
    /* El segundo hijo reconecta su salida estándar (stdout) a la 
       entrada del pipe y cierra el descriptor de la salida del pipe 
    */
    else if ( fork() == 0) {
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("who", "who", NULL);
    }
    /* El padre cerrará ambos descriptores del pipe y esperará 
       la finalización de sus hijos 
    */
    else {
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
    }
}
