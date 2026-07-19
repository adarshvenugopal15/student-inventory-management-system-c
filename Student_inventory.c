#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for Student Records (Linked List Node)
// DSA Insight: Linked list allows dynamic sizing and O(1) insertions/deletions at head, unlike arrays.
typedef struct Student {
    int id;
    char name[50];
    float gpa;
    struct Student* next;
} Student;

// Struct for Inventory Items (Linked List Node)
// DSA Insight: Separate linked list for modularity; can be extended to a hash table for O(1) lookups.
typedef struct Item {
    int id;
    char name[50];
    int quantity;
    struct Item* next;
} Item;

// Global heads for linked lists (in a real system, encapsulate in a class/struct for OOP-like design)
Student* studentHead = NULL;
Item* itemHead = NULL;

// Function to create a new student node
Student* createStudent(int id, char* name, float gpa) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->gpa = gpa;
    newStudent->next = NULL;
    return newStudent;
}

// Function to add a student (Insert at head for O(1) time)
// DSA Insight: Head insertion is efficient for stacks/queues; total time O(1).
void addStudent() {
    int id;
    char name[50];
    float gpa;
    printf("Enter Student ID: ");
    scanf("%d", &id);
    printf("Enter Student Name: ");
    scanf("%s", name);
    printf("Enter GPA: ");
    scanf("%f", &gpa);
    
    Student* newStudent = createStudent(id, name, gpa);
    if (newStudent) {
        newStudent->next = studentHead;
        studentHead = newStudent;
        printf("Student added successfully!\n");
    }
}

// Function to display all students (Traverse linked list)
// DSA Insight: O(n) traversal; efficient for small n, but could use pagination for large lists.
void displayStudents() {
    if (!studentHead) {
        printf("No students to display.\n");
        return;
    }
    Student* temp = studentHead;
    printf("Student Records:\n");
    while (temp) {
        printf("ID: %d, Name: %s, GPA: %.2f\n", temp->id, temp->name, temp->gpa);
        temp = temp->next;
    }
}

// Function to search student by ID (Linear search)
// DSA Insight: O(n) worst-case; if sorted, could switch to binary search (O(log n)) for optimization.
void searchStudent() {
    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);
    Student* temp = studentHead;
    while (temp) {
        if (temp->id == id) {
            printf("Found: ID: %d, Name: %s, GPA: %.2f\n", temp->id, temp->name, temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.\n");
}

// Function to delete a student by ID
// DSA Insight: O(n) due to traversal; uses pointer manipulation to unlink nodes safely.
void deleteStudent() {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    Student* temp = studentHead;
    Student* prev = NULL;
    while (temp) {
        if (temp->id == id) {
            if (prev) {
                prev->next = temp->next;
            } else {
                studentHead = temp->next;
            }
            free(temp);
            printf("Student deleted successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Student not found.\n");
}

// Quicksort helper for sorting students by GPA (Recursive, in-place)
// DSA Insight: O(n log n) average case; recursive partitioning shows divide-and-conquer mastery.
void quicksortStudents(Student** headRef) {
    if (!*headRef || !(*headRef)->next) return;  // Base case: 0 or 1 node
    
    Student* pivot = *headRef;
    Student* lessHead = NULL, *lessTail = NULL;
    Student* greaterHead = NULL, *greaterTail = NULL;
    Student* temp = pivot->next;
    
    while (temp) {
        Student* next = temp->next;
        if (temp->gpa <= pivot->gpa) {
            if (!lessHead) {
                lessHead = lessTail = temp;
            } else {
                lessTail->next = temp;
                lessTail = temp;
            }
        } else {
            if (!greaterHead) {
                greaterHead = greaterTail = temp;
            } else {
                greaterTail->next = temp;
                greaterTail = temp;
            }
        }
        temp = next;
    }
    
    // Recurse on partitions
    quicksortStudents(&lessHead);
    quicksortStudents(&greaterHead);
    
    // Reassemble list
    *headRef = lessHead;
    if (lessTail) lessTail->next = pivot;
    pivot->next = greaterHead;
    if (greaterTail) greaterTail->next = NULL;
}

// Function to sort students by GPA
void sortStudents() {
    quicksortStudents(&studentHead);
    printf("Students sorted by GPA!\n");
}

// Similar functions for Inventory (mirrored for brevity; in real code, refactor to avoid duplication)
Item* createItem(int id, char* name, int quantity) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (!newItem) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

void addItem() {
    int id, quantity;
    char name[50];
    printf("Enter Item ID: ");
    scanf("%d", &id);
    printf("Enter Item Name: ");
    scanf("%s", name);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);
    
    Item* newItem = createItem(id, name, quantity);
    if (newItem) {
        newItem->next = itemHead;
        itemHead = newItem;
        printf("Item added successfully!\n");
    }
}

void displayItems() {
    if (!itemHead) {
        printf("No items to display.\n");
        return;
    }
    Item* temp = itemHead;
    printf("Inventory Items:\n");
    while (temp) {
        printf("ID: %d, Name: %s, Quantity: %d\n", temp->id, temp->name, temp->quantity);
        temp = temp->next;
    }
}

// Main menu-driven function
int main() {
    int choice;
    while (1) {
        printf("\n--- Student Record / Inventory System ---\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Delete Student\n5. Sort Students by GPA\n");
        printf("6. Add Item to Inventory\n7. Display Inventory\n8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: sortStudents(); break;
            case 6: addItem(); break;
            case 7: displayItems(); break;
            case 8: 
                // Free memory to prevent leaks (good practice)
                while (studentHead) {
                    Student* temp = studentHead;
                    studentHead = studentHead->next;
                    free(temp);
                }
                while (itemHead) {
                    Item* temp = itemHead;
                    itemHead = itemHead->next;
                    free(temp);
                }
                printf("Exiting...\n");
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}