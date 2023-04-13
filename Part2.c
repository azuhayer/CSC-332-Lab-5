#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>

// constant variable student
const int students = 10;

// constant variable Chapter which is also X
const int chapters = 2;

// constant variable Homework which is also Y
const int homeworks = 2;

// file name
const char *file = "source.txt"; // change the file name if needed

// Director process
void director(int grades[students][chapters * homeworks]) {

    // for the file reading
    int fd;

    // file reading value
    int readValue = 0;

    // Read Only 
    fd = open(file, O_RDONLY);

    // Error Handling
    if (-1 == fd) {
        printf("File can not be opened.");
        exit(0);
    }

    // File will open
    else {

        // reading each value in the file
        for (int i = 0; i < students; i++){
            for (int j = 0; j < chapters * homeworks; j++) {
                char value[8] = "";
                char str;
                while(readValue = read(fd, &str, 1)){
                if (readValue == 0){
                    break;
                }
                if (isdigit(str)){
                    strncat(value, &str, 1);
                }
                else{
                    break;
                }
            }
            grades[i][j] = atoi(value); 
        }
    }
    }
    close(fd);
}

// worker class
void worker(int grades[students][chapters * homeworks], int c, int h) {

    // the total
    float sum = 0.0;

    // max value
    int max;

    // checks for the max grades
    for (int i = 0; i < students; i++) {
        sum += grades[i][c * homeworks + h];
        if (max < grades[i][h]) {
            max = grades[i][h];
        }
    }

    // average of each homework
    float average = sum / students;

    //outputs the average of each homework and chapter for the 10 students
    printf("Average grades for Homework %d in Chapter %d: %.2f\n", h + 1, c + 1, average);
    exit(0); //exits the code
}

// manager class
void manager(int grades[students][chapters * homeworks], int c) {

    for (int homework = 0; homework < homeworks; homework++) {
        if (fork() == 0) {
            worker(grades, c, homework);
        }
        wait(NULL); // ends the process
    }
    exit(0); // exits the process
}

// main class
int main(int argc, char *argv[]) {
    int grades[students][chapters * homeworks];

    // declares the director class
    director(grades);

    for (int i = 0; i < chapters; i++) {
        if (fork() == 0) {

            // manager class that starts from 0
            manager(grades, i);
        }
        wait(NULL);
    }
    exit(0);
}


