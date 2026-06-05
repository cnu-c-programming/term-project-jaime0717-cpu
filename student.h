typedef struct Student {
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

extern Student* head;

void handle_add(int id, char* name, int score);

void handle_delete(int id);

void handle_update(int id, int score);

void handle_find(int id);

void handle_list(void);

void handle_stats(void);

void handle_help(void);

void handle_clear(void);

void handle_exit(void); 