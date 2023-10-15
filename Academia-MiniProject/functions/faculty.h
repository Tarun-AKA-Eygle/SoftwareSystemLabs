#ifndef STUDENT_FUNCTIONS
#define STUDENT_FUNCTIONS

#include "common.h"
struct Faculty loggedInFaculty;

// Function Prototypes =================================

bool faculty_operation_handler(int connFD);
bool change_faculty_password(int connFD);
bool add_course(int connFD);
bool view_all_course(int connFD);
// =====================================================

// Function Definition =================================

bool faculty_operation_handler(int connFD)
{
    if (login_handler_faculty(connFD, &loggedInFaculty))
    {
        ssize_t writeBytes, readBytes;            // Number of bytes read from / written to the client
        char readBuffer[1000], writeBuffer[1000]; // A buffer used for reading & writing to the client
        
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, STUDENT_LOGIN_SUCCESS);
        while (1)
        {
            strcat(writeBuffer, "\n");
            strcat(writeBuffer, FACULTY_MENU);
            writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));

            if (writeBytes == -1)
            {
                perror("Error while writing FACULTY_MENU to client!");
                return false;
            }
            bzero(writeBuffer, sizeof(writeBuffer));

            bzero(readBuffer, sizeof(readBuffer));
            readBytes = read(connFD, readBuffer, sizeof(readBuffer));
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for FACULTY_MENU");
                return false;
            }
            
            int choice = atoi(readBuffer);
            switch (choice)
            {
            case 1:
                view_all_course(connFD);
                break;
            case 2:
                add_course(connFD);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                change_faculty_password(connFD);
                break;
            case 6:
                writeBytes = write(connFD, CUSTOMER_LOGOUT, strlen(CUSTOMER_LOGOUT));
                return false;
                break;
            default:
                
            }
        }
    }
    else
    {
        // CUSTOMER LOGIN FAILED
        return false;
    }
    return true;
}

// =====================================================
bool change_faculty_password(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];


    int CourseFileDescriptor;

    off_t offset;
    int lockingStatus;

    
    writeBytes = write(connFD, STUDENT_MOD_PASSWORD, strlen(STUDENT_MOD_PASSWORD));
    if (writeBytes == -1)
    {
        perror("Error while writing STUDENT_MOD_PASSWORD message to client!");
        return false;
    }
    readBytes = read(connFD, &readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error while getting response for Faculty's new name from client!");
        return false;
    }
    char hashedPassword[1000];
    strcpy(hashedPassword, crypt(readBuffer, SALT_BAE));
    strcpy(loggedInFaculty.password, hashedPassword);

    
    CourseFileDescriptor = open(FACULTY_FILE, O_WRONLY);
    if (CourseFileDescriptor == -1)
    {
        perror("Error while opening Faculty file");
        return false;
    }
    offset = lseek(CourseFileDescriptor, loggedInFaculty.id * sizeof(struct Faculty), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required Faculty record!");
        return false;
    }

    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Faculty), getpid()};
    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lockingStatus = fcntl(CourseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on Faculty record!");
        return false;
    }

    writeBytes = write(CourseFileDescriptor, &loggedInFaculty, sizeof(struct Faculty));
    if (writeBytes == -1)
    {
        perror("Error while writing update Faculty info into file");
    }

    lock.l_type = F_UNLCK;
    fcntl(CourseFileDescriptor, F_SETLKW, &lock);

    close(CourseFileDescriptor);

    writeBytes = write(connFD, ADMIN_MOD_STUDENT_SUCCESS, strlen(ADMIN_MOD_STUDENT_SUCCESS));
    if (writeBytes == -1)
    {
        perror("Error while writing ADMIN_MOD_STUDENT_SUCCESS message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read

    return true;
}
bool  add_course(int connFD){
    ssize_t readBytes, writeBytes;
    char readBuffer[1000], writeBuffer[1000];

    struct Course newCourse, previousCourse;

    int CourseFileDescriptor = open(COURSE_FILE, O_RDONLY);
    if (CourseFileDescriptor == -1 && errno == ENOENT)
    {
        // Course file was never created
        newCourse.id = 0;
    }
    else if (CourseFileDescriptor == -1)
    {
        perror("Error while opening Course file");
        return -1;
    }
    else
    {
        int offset = lseek(CourseFileDescriptor, -sizeof(struct Course), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last Course record!");
            return false;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Course), getpid()};
        int lockingStatus = fcntl(CourseFileDescriptor, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on Course record!");
            return false;
        }

        readBytes = read(CourseFileDescriptor, &previousCourse, sizeof(struct Course));
        if (readBytes == -1)
        {
            perror("Error while reading Course record from file!");
            return false;
        }

        lock.l_type = F_UNLCK;
        fcntl(CourseFileDescriptor, F_SETLK, &lock);

        close(CourseFileDescriptor);

        newCourse.id = previousCourse.id + 1;
    }

    sprintf(writeBuffer, "%s", FACULTY_ADD_COURSE_NAME);
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));

    if (writeBytes == -1)
    {
        perror("Error writing FACULTY_ADD_COURSE_NAME message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error reading FACULTY_ADD_COURSE_NAME response from client!");
        ;
        return false;
    }
    
    strcpy(newCourse.name, readBuffer);

    sprintf(writeBuffer, "%s", FACULTY_ADD_COURSE_DEPARTMENT);
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));

    if (writeBytes == -1)
    {
        perror("Error writing FACULTY_ADD_COURSE_DEPARTMENT message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error reading FACULTY_ADD_COURSE_DEPARTMENT response from client!");
        ;
        return false;
    }

    strcpy(newCourse.department, readBuffer);

    sprintf(writeBuffer, "%s", FACULTY_ADD_COURSE_SEAT);
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));

    if (writeBytes == -1)
    {
        perror("Error writing FACULTY_ADD_COURSE_SEAT message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error reading SEATS response from client!");
        return false;
    }

    newCourse.noOfSeats = atoi(readBuffer);
    newCourse.active=true;
    sprintf(writeBuffer, "%s", FACULTY_ADD_COURSE_CREDIT);
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));

    if (writeBytes == -1)
    {
        perror("Error writing FACULTY_ADD_COURSE_CREDIT message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error reading SEATS response from client!");
        return false;
    }

    newCourse.courseCredit = atoi(readBuffer);

    CourseFileDescriptor = open(COURSE_FILE, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    if (CourseFileDescriptor == -1)
    {
        perror("Error while creating / opening Student file!");
        return false;
    }
    writeBytes = write(CourseFileDescriptor, &newCourse, sizeof(newCourse));
    if (writeBytes == -1)
    {
        perror("Error while writing Student record to file!");
        return false;
    }

    close(CourseFileDescriptor);
    off_t offset;
    int lockingStatus;
    struct flock lock = {F_RDLCK, SEEK_SET, offset, sizeof(struct Faculty), getpid()};

    loggedInFaculty.course_id[loggedInFaculty.noOfCourse++]=newCourse.id;
    int facultyFileDescriptor = open(FACULTY_FILE, O_WRONLY);
    if (facultyFileDescriptor == -1)
    {
        perror("Error while opening Faculty file");
        return false;
    }
    offset = lseek(facultyFileDescriptor, loggedInFaculty.id * sizeof(struct Faculty), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required Faculty record!");
        return false;
    }

    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lockingStatus = fcntl(facultyFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on Faculty record!");
        return false;
    }

    writeBytes = write(facultyFileDescriptor, &loggedInFaculty, sizeof(struct Faculty));
    if (writeBytes == -1)
    {
        perror("Error while writing update Faculty info into file");
    }

    lock.l_type = F_UNLCK;
    fcntl(facultyFileDescriptor, F_SETLKW, &lock);

    close(facultyFileDescriptor);

    sprintf(writeBuffer, "%s%d", COURSE_CREATED,newCourse.id);
    strcat(writeBuffer, "\n^");
    writeBytes = write(connFD, writeBuffer, sizeof(writeBuffer));
    if (writeBytes == -1)
    {
        perror("Error writing COURSE_CREATED message to client!");
        return false;
    }


    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    return true;



}
bool view_all_course(int connFD)
{
    ssize_t readBytes, writeBytes;             // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[10000]; // A buffer for reading from / writing to the socket
    char tempBuffer[1000];
    int CourseID = -1;
    struct Course course;
    int courseFileDescriptor;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Course), getpid()};

  

    courseFileDescriptor = open(COURSE_FILE, O_RDONLY);
    if (courseFileDescriptor == -1)
    {
        // Customer File doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, FACULTY_ID_DOESNT_EXIT);
        strcat(writeBuffer, "^");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing FACULTY_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    
    lock.l_start = 0;

    int lockingStatus = fcntl(courseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the course file!");
        return false;
    }
    
    bzero(writeBuffer, sizeof(writeBuffer));
    for(int i=0;i<loggedInFaculty.noOfCourse;i++)
    {   
        lseek(courseFileDescriptor, 0, SEEK_SET);
        while (read(courseFileDescriptor, &course, sizeof(struct Course)) == sizeof(struct Course)){
            if(course.id==loggedInFaculty.course_id[i] && course.active==true){
                bzero(tempBuffer, sizeof(tempBuffer));
                sprintf(tempBuffer, "-------------------------------------------------\nCourse Details - \n\tCourse ID : %d\n\tCourse Name : %s\n\tCourse Department : %s\n\tCourse Seats : %d\n\tCourse Credit : %d", course.id, course.name, course.department,course.noOfSeats,course.courseCredit);
                strcat(writeBuffer, tempBuffer);
                strcat(writeBuffer, "\n");
            }
        }
    }
    strcat(writeBuffer, "\n^");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));   
    if (writeBytes == -1)
    {
        perror("Error writing faculty info to client!");
        return false;
    }
    lock.l_type = F_UNLCK;
    fcntl(courseFileDescriptor, F_SETLK, &lock);
    readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    return true;
    
}
bool remove_course(int connFD)
{
    ssize_t readBytes, writeBytes;             // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[10000]; // A buffer for reading from / writing to the socket
    char tempBuffer[1000];
    int CourseID = -1;
    struct Course course;
    int courseFileDescriptor;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Course), getpid()};

    off_t offset;
    int lockingStatus;

    writeBytes = write(connFD, FACULTY_MOD_COURSE_ID, strlen(FACULTY_MOD_COURSE_ID));
    if (writeBytes == -1)
    {
        perror("Error while writing FACULTY_MOD_COURSE_ID message to client!");
        return false;
    }
    bzero(readBuffer, sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (readBytes == -1)
    {
        perror("Error while reading student ID from client!");
        return false;
    }

    CourseID = atoi(readBuffer);
    courseFileDescriptor = open(COURSE_FILE, O_RDONLY);
    if (courseFileDescriptor == -1)
    {
        // Customer File doesn't exist
        bzero(writeBuffer, sizeof(writeBuffer));
        strcpy(writeBuffer, FACULTY_ID_DOESNT_EXIT);
        strcat(writeBuffer, "^");
        writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {   
            perror("Error while writing FACULTY_ID_DOESNT_EXIT message to client!");
            return false;
        }
        readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    
    lock.l_start = 0;

    int lockingStatus = fcntl(courseFileDescriptor, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the course file!");
        return false;
    }
    
    bzero(writeBuffer, sizeof(writeBuffer));
    for(int i=0;i<loggedInFaculty.noOfCourse;i++)
    {   
        lseek(courseFileDescriptor, 0, SEEK_SET);
        while (read(courseFileDescriptor, &course, sizeof(struct Course)) == sizeof(struct Course)){
            if(course.id==loggedInFaculty.course_id[i] && course.active==true){
                bzero(tempBuffer, sizeof(tempBuffer));
                sprintf(tempBuffer, "-------------------------------------------------\nCourse Details - \n\tCourse ID : %d\n\tCourse Name : %s\n\tCourse Department : %s\n\tCourse Seats : %d\n\tCourse Credit : %d", course.id, course.name, course.department,course.noOfSeats,course.courseCredit);
                strcat(writeBuffer, tempBuffer);
                strcat(writeBuffer, "\n");
            }
        }
    }
    strcat(writeBuffer, "\n^");
    writeBytes = write(connFD, writeBuffer, strlen(writeBuffer));   
    if (writeBytes == -1)
    {
        perror("Error writing faculty info to client!");
        return false;
    }
    lock.l_type = F_UNLCK;
    fcntl(courseFileDescriptor, F_SETLK, &lock);
    readBytes = read(connFD, readBuffer, sizeof(readBuffer)); // Dummy read
    return true;
    
}
#endif