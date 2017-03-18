// Author: Sean Davis
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "course.h"
#include "vector.h"


void find_CRN(char **subjects, char **courses, int *CRNs, int count)
{
  int i, CRN;
  printf("Please enter a CRN: ");
  scanf("%d", &CRN);

  for(i = 0; i < count; i++)
    if(CRNs[i] == CRN)
    {
      printf("%s %s\n", subjects[i], courses[i]);
      break;
    } // if CRN matches

  if(i == count)
    printf("CRN %d not found.\n", CRN);

} // find_CRN()

void find_subject(char **subjects, char **courses, int *CRNs, int count)
{
  char subject[SMALL_ARRAY_SIZE];
  int i, found = 0;

  printf("Please enter a subject: ");
  do
  {
    scanf("%s", subject);
  } while(strlen(subject) == 0);

  for(i = 0; i < count; i++)
  {
    if(strcmp(subject, subjects[i]) == 0)
    {
      printf("%d %s %s\n", CRNs[i], subjects[i], courses[i]);
      found = 1;
    } // if subject matches
  } // for i

  if(!found)
    printf("No courses were found for %s.\n", subject);

} // find_subjects()


void  read_courses(char ***subjects, char***courses, int **CRNs, int *count,
  int *size, const char *filename)
{
  char line[LARGE_ARRAY_SIZE];
  FILE *fp = fopen(filename, "r");


  if(fp == NULL)
  {
    printf("%s not readable.\n", filename);
    exit(1);
  } // if file not openable

  initialize(subjects, courses, CRNs, size);
  *count = 0;

  while(fgets(line, LARGE_ARRAY_SIZE, fp))
  {
    if(isdigit(line[0]) && isdigit(line[CRN_END]))
    {
      if(*count == *size)
        resize(subjects, courses, CRNs, size);
      (*CRNs)[*count] = atoi(strtok(line, "\t"));
      strcpy((*subjects)[*count], strtok(NULL, "\t"));

      if((*subjects)[*count][0] == '^')
        strcpy((*subjects)[*count], strtok(NULL, "\t"));

      strcpy((*courses)[*count], strtok(NULL, "\t"));
      (*count)++;
    } // if line starts with CRN
  } // while more in file

} // read_courses()


