// Lab 4 — Student management module: IMPLEMENTATION
// Task: implement the functions marked TODO. Run "make test" to check.
#include <stdlib.h>
#include <string.h>
#include "student.h"

// ===================== 4.1 Struct =====================

// Create a Student. Names longer than MAX_NAME - 1 characters are truncated
// (hint: strncpy then set '\0' at the end yourself, or use snprintf).
Student make_student(int id, const char *name, float gpa) {
    Student s = {id, {0}, gpa};
    strncpy(s.name, name, MAX_NAME);
    s.name[MAX_NAME - 1] = '\0';
    return s;
}

// Print one line in the form:  "  1001  Nguyen Van An                  3.45"
void print_student(const Student *s) {
    printf("%6d  %-30s %.2f\n", s->id, s->name, s->gpa);
}

// ===================== 4.2 Linked list =====================

// Insert at the front of the list, return the new head
Node *list_push_front(Node *head, Student s) {
    Node* newhead = malloc(sizeof(Node));
    (*newhead)=(Node){s, head};
    return newhead;
}

// Insert at the end of the list, return head (changes if the list was empty)
Node *list_push_back(Node *head, Student s) {
    Node* last = malloc(sizeof(Node));
    *last = (Node){s, NULL};

    if (head == NULL) return last;
    Node* cur = head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = last;
    return head;
}

// Number of elements
int list_length(const Node *head) {
    if (head == NULL) return 0;
    int count = 0;
    while (head != NULL) {
        head = head->next;
        count++;
    }
    return count;
}

// Find by id; return a pointer to the Student in the list (so it can be modified), or NULL
Student *list_find(Node *head, int id) {
    if (head == NULL) return NULL;
    do {
        if (head->data.id == id) return &head->data;
        head = head->next;
    }
    while (head != NULL);
    return NULL;
}

// Remove the first node with the matching id (remember to free it), return the new head.
// If the id is not found, leave the list unchanged.
Node *list_remove(Node *head, int id) {
    if (head == NULL) return NULL;
    Node* prev = NULL;
    Node* cur = head;
    do {
        if (cur->data.id == id) break;
        prev = cur;
        cur = cur->next;
    }
    while (cur != NULL);
    if (prev == NULL){
        head = cur->next;
        free(cur);
    }
    if (prev != NULL && cur != NULL) {
        prev->next = cur->next;
        free(cur);
    }
    return head;
}

// Print the whole list
void list_print(const Node *head) {
    for (const Node *p = head; p != NULL; p = p->next)
        print_student(&p->data);
}

// Free the whole list
void list_free(Node *head) {
    if (head == NULL) return;
    Node* prev;
    Node* cur = head;
    do {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    while (cur != NULL);
}

// ===================== 4.3 Function pointers =====================

// Comparison functions for qsort: a, b are pointers to Student.
// Return < 0 if a comes before b, 0 if equal, > 0 if a comes after b.

int compare_by_id(const void *a, const void *b) {
    const Student *x = a, *y = b;
    return x->id - y->id; // example
}

int compare_by_name(const void *a, const void *b) {
    const Student *x = a, *y = b;
    return strcmp(x->name, y->name);
}

// GPA in descending order (higher GPA first). Careful: gpa is a float, do not return x->gpa - y->gpa!
int compare_by_gpa_desc(const void *a, const void *b) {
    const Student *x = a, *y = b;
    if (y->gpa == x->gpa) return 0;
    return (y->gpa < x->gpa) ? -1 : 1;
}

// Copy at most max elements of the list into the array out, return the number copied
int list_to_array(const Node *head, Student out[], int max) {
    if (head == NULL || max == 0) return 0;
    int i = 0;
    do {
        out[i++] = head->data;
        head = head->next;
    }
    while (head != NULL && i < max);
    return i;
}

// Sort the array using the comparison function cmp
void sort_students(Student arr[], int n, StudentCompare cmp) {
    qsort(arr, n, sizeof(Student), cmp);
}

// Excellent student: gpa >= 3.6
int is_excellent(const Student *s) {
    return s->gpa >= 3.6;
}

// Count the students that satisfy pred
int count_if(const Node *head, StudentPredicate pred) {
    if (head == NULL) return 0;
    int i = 0;
    do {
        i += pred(&(head->data));
        head = head->next;
    }
    while (head != NULL);
    return i;
}
