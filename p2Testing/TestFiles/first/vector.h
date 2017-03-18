// Author: Sean Davis

#ifndef VECTOR_H
  #define VECTOR_H

#define INITIAL_COURSE_SIZE 100
#define COURSE_SIZE 6
#define SUBJECT_SIZE 4

void initialize(char ***subjects, char ***courses, int **CRNs, int *size);
void resize(char ***subjects, char ***courses, int **CRNs, int *size);
void deallocate(char **subjects, char **courses, int *CRNs, int size);


#endif
