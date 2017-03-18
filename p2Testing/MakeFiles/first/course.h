#ifndef COURSES_H
  #define COURSES_H

#define SUBJECT_SIZE 4
#define COURSE_SIZE 6
#define LARGE_ARRAY_SIZE 256
#define SMALL_ARRAY_SIZE 20
#define CRN_END 4


void find_CRN(char **subjects, char **courses, int *CRNs, int count);
void find_subject(char **subjects, char **courses, int *CRNs, int count);
void read_courses(char ***subjects, char***courses, int **CRNs, int *count,
  int *size, const char *filename);





#endif
