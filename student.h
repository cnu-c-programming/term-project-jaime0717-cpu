typedef struct Student {
    int id;
    char name[32];
    int score;
    struct Student* next;
} Student;

void save(void);

void reload(void);

void add(int id, char* name, int score, Student* head);

void delete_student(int id); //delete라는 함수가 이미 있어서 이름을 저렇게 처리.

void update(int id, int score);

void find(int id, Student* head);

void list(void);

void stats(void);

void help(void);

void clear(void);

void exit_student(void); // exit이라는 함수가 이미 있어서 이름을 저렇게 처리.