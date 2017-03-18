// Author: Sean Davis
#include <stdio.h>
#include <string.h>
#include "course.h"
#include "vector.h"
#define NUM_CHOICES 2
#define COURSE_FILE_ARG 1

void display_info(char **subjects, char **courses, int *CRNs, int count);
int get_choice(void);

int main(int argc, char **argv)
{
  char **subjects, **courses;
  int *CRNs, count, size;

  read_courses(&subjects, &courses, &CRNs, &count, &size, argv[COURSE_FILE_ARG]);
  display_info(subjects, courses, CRNs, count);

  deallocate(subjects, courses, CRNs, size);
  return 0;
}  // main()

int get_choice(void)
{
  int choice;

  do
  {
    printf("\nRSVP Menu\n");
    printf("0. Done.\n");
    printf("1. Find by CRN.\n");
    printf("2. Find by subject.\n");
    printf("Your choice (0 - %d): ", NUM_CHOICES);
    scanf("%d", & choice);

    if(choice < 0 || choice > NUM_CHOICES)
      printf("Your choice is outside the acceptable range.  Please try again.\n");
  }  while(choice < 0 || choice > NUM_CHOICES);

  return choice;
} // get_choice


void display_info(char **subjects, char **courses, int *CRNs, int count)
{
  int choice;

  do
  {
    choice = get_choice();

    if(choice == 1)
      find_CRN(subjects, courses, CRNs, count);
    else
      if(choice == 2)
        find_subject(subjects, courses, CRNs, count);

  } while(choice != 0);

} // display_info()

