#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // Access to POSIX API
#include <sys/types.h> // Used for unmask.
#include <sys/stat.h>
#include <signal.h>    // Handlers for signals reported during execution.
#include <syslog.h>    // Definitions for system error logging.
#include <errno.h>     // Macros for reporting and retrieving error conditions.
#include <string.h>

void daemonize() {
    pid_t pid; // Process ID and Session ID.

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

    openlog ("Trackermon", LOG_PID, LOG_DAEMON);
} 