// Author: Sean Davis
#include "vector.h"
#include <stdlib.h>

void initialize(char ***subjects, char***courses, int **CRNs, int *size)
{
  int i;

  *subjects = (char**) malloc (INITIAL_COURSE_SIZE * sizeof(char*));
  *courses = (char**) malloc(INITIAL_COURSE_SIZE * sizeof(char*));
  *CRNs = (int*) malloc(INITIAL_COURSE_SIZE * sizeof(int));

  for(i = 0; i < INITIAL_COURSE_SIZE; i++)
  {
    (*subjects)[i] = (char*) malloc(SUBJECT_SIZE * sizeof(char));
    (*courses)[i] = (char*) malloc(COURSE_SIZE * sizeof(char));
  } // for i

  *size = INITIAL_COURSE_SIZE;
}  // initalize()


void resize(char ***subjects, char***courses, int **CRNs, int *size)
{
  int i, *CRNs2, size2 = *size * 2;
  char **subjects2, **courses2;


  subjects2 = (char**) malloc (size2 * sizeof(char*));
  courses2 = (char**) malloc(size2 * sizeof(char*));
  CRNs2 = (int*) malloc(size2 * sizeof(int));

  for(i = 0; i < *size; i++)
  {
    subjects2[i] = (*subjects)[i];
    courses2[i] = (*courses)[i];
    CRNs2[i] = (*CRNs)[i];
  } // for i

  free(*subjects);
  free(*courses);
  free(*CRNs);
  *subjects = subjects2;
  *courses = courses2;
  *CRNs = CRNs2;

  for(; i < size2; i++)
  {
    (*subjects)[i] = (char*) malloc(SUBJECT_SIZE * sizeof(char));
    (*courses)[i] = (char*) malloc(COURSE_SIZE * sizeof(char));
  } // for i

  *size = size2;
} // resize()

void deallocate(char **subjects, char **courses, int *CRNs, int size)
{
  int i;

  for(i = 0; i < size; i++)
  {
    free (courses[i]);
    free(subjects[i]);
  } // for i

  free(courses);
  free(subjects);
  free(CRNs);
} // resize()


