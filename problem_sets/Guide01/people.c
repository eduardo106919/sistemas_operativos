#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "person.h"

int main(int argc, char **argv){
    if (argc < 3) {
        printf("Usage:\n");
        printf("Add new person: %s -i [name] [age]\n", argv[0]);
        printf("List first N people: %s -l [N]\n", argv[0]);
        printf("Change person age (name): %s -u [name] [age]\n", argv[0]);
        printf("Change person age (position): %s -o [position] [age]\n", argv[0]);

        return 1;
    }

    // open the community file
    int community = open("community", O_CREAT | O_RDWR, 0600);
    if (community == -1) {
        perror("community");
        return 1;
    }

    struct person john_doe;
    ssize_t bytes_read = 0;

    // add a person to the end of the file
    if (strcmp(argv[1], "-i") == 0) {
        off_t bytes = lseek(community, 0, SEEK_END);

        unsigned reg = bytes / sizeof(struct person);

        create_person(&john_doe, argv[2], atol(argv[3]));

        // write the content in the file
        write(community, &john_doe, sizeof(john_doe));
        fprintf(stdout, "register %u\n", reg);
    }

    // list the N first people
    if (strcmp(argv[1], "-l") == 0) {
        unsigned N = atol(argv[2]);

        unsigned i = 0;
        while (i < N && (bytes_read = read(community, &john_doe, sizeof(john_doe))) > 0) {
            show_person(&john_doe);
            i++;
        }
    }

    // change a person's age, by it's name
    if (strcmp(argv[1], "-u") == 0) {
        unsigned new_age = atol(argv[3]);

        while ((bytes_read = read(community, &john_doe, sizeof(john_doe))) > 0 && strcmp(john_doe.name, argv[2]) != 0);

        if (bytes_read > 0) {
            update_age(&john_doe, new_age);

            // go back one person
            lseek(community, - sizeof(john_doe), SEEK_CUR);

            // write back the changes
            write(community, &john_doe, sizeof(john_doe));
        }
    }

    // change a person's age, by it's position
    if (strcmp(argv[1], "-o") == 0) {
        unsigned position = atol(argv[2]);
        unsigned new_age = atol(argv[3]);

        // go to the selected position
        off_t bytes = lseek(community, position * sizeof(john_doe), SEEK_SET);

        // position is invalid
        if (bytes < lseek(community, 0, SEEK_END)) {
            // read the person
            read(community, &john_doe, sizeof(john_doe));
            update_age(&john_doe, new_age);

            // go back one position
            lseek(community, - sizeof(john_doe), SEEK_CUR);
            // write back the changes
            write(community, &john_doe, sizeof(john_doe));
        }
    }

    unlink("community");
    close(community);

    return 0;
}
