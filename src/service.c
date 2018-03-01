#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // Access to POSIX API
#include <sys/types.h> // Used for unmask.
#include <sys/stat.h>
#include <signal.h>    // Handlers for signals reported during execution.
#include <syslog.h>    // Definitions for system error logging.
#include <errno.h>     // Macros for reporting and retrieving error conditions.
#include <fcntl.h>     // Open syscall for recording PID.
#include <string.h>

void daemonize(char * pid_file) {
    printf("Inicializando Trackermon...\n");
    pid_t pid; // Process ID and Session ID.
    int pid_fd = -1;

    // First fork: Child runs in the background, parent gets terminated.
    pid = fork(); // Creates a child process.
    if (pid < 0) {
        exit(EXIT_FAILURE); // Bad PID, terminates reporting error.
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS); // Let the parent process terminate.
    }
    if (setsid() < 0) { // Gets new Session ID for the child process.
        exit(EXIT_FAILURE); // Bad SID, terminates reporting error.
    }
    signal(SIGCHLD, SIG_IGN); // Ignores signal sent from child to parent.

    // Second fork: Ensures getting rid of the session leading process.
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0); // UNMASK: Changes the file mode mask.

    if(chdir("/") < 0) { // Changes the working directory to a more appropiate one.
        exit(EXIT_FAILURE);
    }

    // Close all open file descriptors inherited from the parent:
    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }

    // Reopen stdin (fd = 0), stdout (fd = 1), stderr (fd = 2) 
	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w+");
    stderr = fopen("/dev/null", "w+");

    char buffer[256];
    printf(pid_file, "\n");
    pid_fd = open(pid_file, O_RDWR|O_CREAT, 0640);
    if (pid_fd < 0) {
        printf("No pudo abrir PID.\n");
        // Can't open PID file.
        exit(EXIT_FAILURE);
    }
    if (lockf(pid_fd, F_TLOCK, 0) < 0) {
        printf("No pudo cerrar PID\n");
        // Can't lock PID file
        exit(EXIT_FAILURE);
    }
    // Get current PID:
    sprintf(buffer, "%d\n", getpid());
    // Write current PID to PID File:
    write(pid_fd, buffer, strlen(buffer));

    //openlog ("Trackermon", LOG_PID, LOG_DAEMON); // For debugging purposes.
} 

void handleSignal(int sig) {
    if (sig == SIGINT) {

    }
}