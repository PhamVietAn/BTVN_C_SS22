#include <stdio.h>
#include <string.h>

struct SinhVien{
    char id[50];
    char name[50];
    int age;
};

struct SinhVien sv[100];

int numberStudent = 0;

void getStudentByFile();
void printStudent();
void addStudent();
void saveStudent();
void updateStudent();
void deleteStudent();
void searchStudent();
void sortStudent();
int findStudentById(char id[]);

int main(){
    getStudentByFile();
    int choice;

    do{
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien.\n");
        printf("2. Them sinh vien.\n");
        printf("3. Sua thong tin sinh vien.\n");
        printf("4. Xoa thong tin sinh vien.\n");
        printf("5. Tim thong tin sinh vien.\n");
        printf("6. Sap xep danh sach sinh vien.\n");
        printf("7. Thoat\n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                printStudent();
                break;

            case 2:
                addStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                searchStudent();
                break;

            case 6:
                sortStudent();
                break;

            case 7:
                printf("\nThoat chuong trinh.\n");
                break;

            default:
                printf("\nLua chon khong hop le.\n");
                break;
        }

    }while(choice != 7);

    return 0;
}

void getStudentByFile(){
    FILE *file;
    file = fopen("sinhvien.bin", "rb");
    if (file == NULL) {
        printf("\nLoi mo file.\n");
        return;
    }
    numberStudent = fread(sv, sizeof(struct SinhVien), 100, file);
    fclose(file);
}

void printStudent(){
    if(numberStudent == 0){
        printf("\nKhong co sinh vien\n");
        return;
    }
    for(int i = 0; i < numberStudent; i++){
        printf("\nThong tin sinh vien thu %d\n", i + 1);
        printf("Ma sinh vien: %s\n", sv[i].id);
        printf("Ten sinh vien: %s\n", sv[i].name);
        printf("Tuoi: %d\n", sv[i].age);
    }
}

void addStudent(){
    if(numberStudent >= 100){
        printf("\nnDanh sach sinh vien da day.\n");
        return;
    }
    struct SinhVien sv1;
    int exists = 1;
    while(exists){
        printf("\nnNhap ma sinh vien: ");
        fgets(sv1.id, sizeof(sv1.id), stdin);
        sv1.id[strcspn(sv1.id, "\n")] = '\0';

        if(findStudentById(sv1.id) == -1){
            exists = 0;
        }else{
            printf("\nnMa sinh vien da ton tai. Vui long nhap ma khac.\n");
        }
    }

    printf("Nhap ten sinh vien: ");
    fgets(sv1.name, sizeof(sv1.name), stdin);
    sv1.name[strcspn(sv1.name, "\n")] = '\0';

    printf("Nhap tuoi sinh vien: ");
    scanf("%d", &sv1.age);
    getchar();

    sv[numberStudent] = sv1;
    numberStudent++;
    saveStudent();
}

void saveStudent(){
    FILE *file;
    file = fopen("sinhvien.bin", "wb");
    if(file == NULL){
        printf("Loi mo file.\n");
        return;
    }
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file);
    fclose(file);
}

void updateStudent(){
    char id[50];
    printf("\nNhap ma sinh vien can sua: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findStudentById(id);
    if(index == -1){
        printf("\nKhong tim thay sinh vien voi ma %s.\n", id);
        return;
    }

    printf("Nhap ten sinh vien moi: ");
    fgets(sv[index].name, sizeof(sv[index].name), stdin);
    sv[index].name[strcspn(sv[index].name, "\n")] = '\0';

    printf("Nhap tuoi sinh vien moi: ");
    scanf("%d", &sv[index].age);
    getchar();

    saveStudent();
    printf("Da cap nhat thong tin sinh vien.\n");
}

void deleteStudent() {
    char id[50];
    printf("\nNhap ma sinh vien can xoa: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findStudentById(id);
    if (index == -1) {
        printf("\nKhong tim thay sinh vien voi ma %s.\n", id);
        return;
    }

    for (int i = index; i < numberStudent - 1; i++) {
        sv[i] = sv[i + 1];
    }
    numberStudent--;
    saveStudent();
    printf("Da xoa sinh vien voi ma %s.\n", id);
}

void searchStudent() {
    char id[50];
    printf("\nNhap ma sinh vien can tim: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    int index = findStudentById(id);
    if (index != -1) {
        printf("\nThong tin sinh vien tim thay:\n");
        printf("Ma sinh vien: %s\n", sv[index].id);
        printf("Ten sinh vien: %s\n", sv[index].name);
        printf("Tuoi: %d\n", sv[index].age);
    } else {
        printf("Khong tim thay sinh vien voi ma %s.\n", id);
    }
}

void sortStudent() {
    struct SinhVien temp;
    for (int i = 0; i < numberStudent - 1; i++) {
        for (int j = i + 1; j < numberStudent; j++) {
            if (strcmp(sv[i].name, sv[j].name) > 0) {
                temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("\nDa sap xep danh sach sinh vien theo ten.\n");
}

int findStudentById(char id[]) {
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}
