#include <stdio.h>
#include <string.h>

struct Account{
    char username[50];
    char password[50];
};

struct Account accounts[100];
int accountCount = 0;

void loadAccountsFromFile();
void saveAccountsToFile();
void registerAccount();
void loginAccount();
int findAccountByUsername(const char *username);

int main(){
    loadAccountsFromFile();
    int choice;

    do{
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                loginAccount();
                break;

            case 2:
                registerAccount();
                break;

            case 3:
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le.\n");
                break;
        }

    }while(choice != 3);

    return 0;
}

void loadAccountsFromFile(){
    FILE *file = fopen("accounts.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return;
    }
    accountCount = fread(accounts, sizeof(Account), 100, file);
    fclose(file);
}

void saveAccountsToFile(){
    FILE *file = fopen("accounts.bin", "wb");
    if(file == NULL){
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(accounts, sizeof(Account), accountCount, file);
    fclose(file);
}

void registerAccount(){
    if(accountCount >= 100){
        printf("Danh sach tai khoan da day.\n");
        return;
    }

    Account newAccount;
    char confirmPassword[50];
    int exists;

    do{
        printf("\nNhap tai khoan: ");
        fgets(newAccount.username, sizeof(newAccount.username), stdin);
        newAccount.username[strcspn(newAccount.username, "\n")] = '\0';

        exists = (findAccountByUsername(newAccount.username) != -1);
        if (exists) {
            printf("Tai khoan da ton tai. Vui long nhap tai khoan khac.\n");
        }
    }while(exists);

    do{
        printf("Nhap mat khau: ");
        fgets(newAccount.password, sizeof(newAccount.password), stdin);
        newAccount.password[strcspn(newAccount.password, "\n")] = '\0';

        printf("Xac nhan lai mat khau: ");
        fgets(confirmPassword, sizeof(confirmPassword), stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0';

        if(strcmp(newAccount.password, confirmPassword) != 0){
            printf("Mat khau xac nhan khong khop. Vui long nhap lai.\n");
        }
    }while(strcmp(newAccount.password, confirmPassword) != 0);

    accounts[accountCount++] = newAccount;
    saveAccountsToFile();
    printf("Dang ky tai khoan thanh cong.\n");
}

void loginAccount(){
    char username[50];
    char password[50];

    printf("\nNhap tai khoan: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Nhap mat khau: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    int index = findAccountByUsername(username);
    if(index != -1 && strcmp(accounts[index].password, password) == 0){
        printf("Dang nhap thanh cong.\n");
    }else{
        printf("Dang nhap that bai. Tai khoan hoac mat khau khong chinh xac.\n");
    }
}

int findAccountByUsername(const char *username){
    for(int i = 0; i < accountCount; i++){
        if(strcmp(accounts[i].username, username) == 0){
            return i;
        }
    }
    return -1;
}
