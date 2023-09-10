/*
============================================================================
Name : 13.c
Author : Tarun Sharma
Description : A program to wait for a STDIN for 10 seconds using select.
Date: 22th Aug, 2023.
============================================================================
*/
#include <stdio.h>
       #include <stdlib.h>
       #include <sys/select.h>

       int
       main(void)
       {
           fd_set rfds;
           struct timeval tv;
           int retval;

           /* Watch stdin (fd 0) to see when it has input. */

           FD_ZERO(&rfds);
           FD_SET(0, &rfds);

           /* Wait up to five seconds. */

           tv.tv_sec = 10;
           tv.tv_usec = 0;

           retval = select(1, &rfds, NULL, NULL, &tv);
           /* Don't rely on the value of tv now! */

           if (retval == -1)
               perror("select()");
           else if (retval)
               printf("Data is available now.\n");
               /* FD_ISSET(0, &rfds) will be true. */
           else
               printf("No data within ten seconds.\n");

           exit(EXIT_SUCCESS);
       }
