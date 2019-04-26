//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU Lesser General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU Lesser General Public License for more details.

// Created by Petr Bena <petr@bena.rocks> in 2019

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int default_sleep = 2;

int err_usage()
{
    printf("Usage: mkzombie [children_count]\n");
    return 1;
}

int mkchild()
{
    printf("Spawning child...\n");
    pid_t p = fork();
    if (p != 0)
    {
        // we are in parent
        return 0;
    } else
    {
        // we are in children
        sleep(default_sleep);
        return 1;
    }
}

int main(int argc, char **argv)
{
    int childrens = 1;
    if (argc > 1)
    {
        childrens = atoi(argv[1]);
        if (childrens < 1)
            return err_usage();
    }
    while (childrens-- > 0)
    {
        if (mkchild() == 1)
            return 0;
    }

    printf("Waiting for children to die and become zombie...\n");
    sleep(default_sleep);
    printf("Zombies were created and will remain in process table until you terminate this process. Hit CTRL+C to terminate it and clean up zombies.\n");
    pause();

    return 0;
}
