#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define CONSOLE_WIDTH 168
#define MAX_NAME_LENGTH 50
#define MAX_MENU_ITEMS 50
#define MAX_STAFF 10
#define MAX_ABSENT_DAY 25




typedef struct {
char name[MAX_NAME_LENGTH];
int price;
int category; //1 food 2 drinks 3 desserts 4 snacks
char design[100];
int color ;
int quantity;
} menuitem;

typedef struct {
    char name[50];
    int absentdays;
    float salary;
    int password;
} Staff;

typedef struct {
char username[MAX_NAME_LENGTH];
char email[MAX_NAME_LENGTH];
char password[MAX_NAME_LENGTH];
} user;

user usersinfo[200];
int maxusers =0;
int userindex;

menuitem menu[MAX_MENU_ITEMS] = {
    {"Pizza", 75.0, 1, "food_pizza.txt", 6}, {"Burger", 60.0, 1, "food_burger.txt", 0}, {"chickn", 50.0, 1, "food_chicken.txt", 0}, {"beef", 25.0, 1,"food_beef.txt", 0},
    {"Pepsi", 20.0, 2, "drinks_pepsi.txt", 1}, {"Water", 10.0, 2, "drinks_water.txt", 9}, {"lamon juice", 30.0, 2, "drinks_lamon_juice.txt", 6}, {"coffee cup", 25.0, 2, "drinks_coffee_cup.txt", 0},
    {"blueberry Cheesecake", 40.0, 3, "desserts_cheesecake.txt", 5}, {"Ice cream", 35.0, 3, "desserts_ice_cream.txt", 5}, {"Cookies & milk ", 25.0, 3, "desserts_cookies&milk.txt", 0}, {"waffle", 30.0, 3, "desserts_waffle.txt", 0},
    {"Fries", 30.0, 4, "snacks_fries.txt", 6}, {"Nachos", 45.0, 4, "snacks_nachos.txt", 6}, {"Nuggets", 55.0, 4, "snacks_nuggets.txt", 6}, {"donut", 40.0, 4, "snacks_ donut.txt", 0}
};
int menucount = 16;
int categorycount =4;

menuitem cart[MAX_MENU_ITEMS];
int cartcount = 0;
int total =0;

Staff staff[MAX_STAFF] = {
     {"Abdulrahman", 10, 3000, 1234},
     {"Azzam", 24, 200, 1234}, {"Majed", 5, 4000, 1234}, {"Nour", 0, 5000, 1234}
};
int staffCount = 4;
float totalSales = 0;

void clearscreen(){
system("cls");
system("color F0");
}

void pre_screen();

void back(char x[MAX_NAME_LENGTH]){
if(isdigit(x[1])){
if(atoi(x)==0)pre_screen();
}
}


void centerprint(char text[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    printf("%*s%s",spaces,"",text);
}

int wrongans(int *choise) {
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) {
            centerprint("    Invalid input! Please enter numbers only.\n", 4);
            Sleep(700);
            return 1;
        }
    }

    *choise = atoi(buffer);
    return 0;
}

void centerbutton(char text[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    int starlen = length+3;
    printf("%*s+",spaces,"");
    for(int i = 0;i<=starlen;i++){
        printf("=");
    }
    printf("+\n");
    printf("%*s|  %s  |",spaces,"",text);
    printf("\n%*s+",spaces,"");
    for(int i = 0;i<=starlen;i++){
        printf("=");
    }
    printf("+\n\n");
}

void design(char filename[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    FILE *pf = fopen(filename,"r");
    char buffer[255];
    while(fgets(buffer,255,pf) != NULL)
    {
    centerprint(buffer,color);
    }
    printf("\n");
 }

void firstscreen();

void screens(int choise){
   while(1){
    int loopstart = menucount*(choise-1)/4;
    int loopend = loopstart + categorycount;
    clearscreen();
    design("layalina_menu.txt", 0);
    for(int i =loopstart; i<loopend;i++){
        char buffer[50];
        sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
        centerbutton(buffer,0);
        design(menu[i].design,menu[i].color);
    }
        centerbutton("0.    Back     ",4);
        centerprint("      Select an option : ",0);
        int itemnum,qty;
        if(wrongans(&itemnum) ==1)continue;
        if(itemnum ==0){
                firstscreen();
              }else if(itemnum<=loopstart||itemnum>loopend){
                    centerprint("    Invalid Choice !\n", 4);
                    Sleep(1000);
                    continue;
              }
        centerprint("      Enter quantity : ",0);
        if(wrongans(&qty) ==1)continue;
        if(qty<=0){
                centerprint("    Invalid Choice !\n", 4);
                Sleep(700);
        }else {
        centerprint("      Item added successfully",2);
        Sleep(700);
        int found = 0;
for (int i = 0; i < cartcount; i++) {
    if (strcmp(cart[i].name, menu[itemnum - 1].name) == 0) {
        cart[i].quantity += qty;
        found = 1;
        break;
    }
}

if (!found) {
    menu[itemnum - 1].quantity = qty;
    cart[cartcount] = menu[itemnum - 1];
    cartcount++;
}


        }
   }
}

void cartscreen(){
    while(1){
    clearscreen();
    design("cart1.txt", 0);

printf("\n\n");
char buffer[100];
if(cartcount == 0){
    centerprint("Your Cart Is Empty",4);
    Sleep(700);
    firstscreen();
}else{
for(int i =0;i<cartcount;i++){
     sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
     centerprint(buffer,0);
     total += cart[i].price*cart[i].quantity;
}
char totalmoney[100];
sprintf(totalmoney,"Total : %d$",total);
centerprint(totalmoney,0);
}
printf("\n");

centerbutton("0. Back",4);
centerbutton("99. Remove Item",4);
centerprint("      Select an option : ",0);
int choise;
if(wrongans(&choise) ==1)continue;
   if(choise == 0) {
        firstscreen();
   }else if(choise == 99){
   centerprint("Select Item Number :",4);
   int remove;
   if(wrongans(&remove) ==1)continue;
   if (remove <= 0 || remove > cartcount) {
        centerprint("    Invalid item number!\n", 4);
        Sleep(700);
        continue;
   }
remove--;
total -= cart[remove].price*cart[remove].quantity;
for (int i = remove; i < cartcount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartcount--;
    centerprint("    Item removed successfully.\n", 2);
    Sleep(700);
    continue;

    }else {centerprint("    Invalid Choice !\n", 4); Sleep(700);}
    }
}

void checkoutscreen(){
        while(1){
            int total;
            char address[220];
            int ensure;
            int back_now;
            clearscreen();
            design("checkout1.txt", 0);
            char buffer[100];
            if(cartcount == 0){
                centerprint("Nothing ):",4);
                Sleep(700);
                firstscreen();
            }else{
                for(int i =0;i<cartcount;i++){
                    sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
                    centerprint(buffer,0);
                    total += cart[i].price*cart[i].quantity;
                }
                char totalmoney[100];
                sprintf(totalmoney,"Total : %d$",total);
                centerprint(totalmoney,0);
                printf("\n");
                centerprint("enter your address: ", 0);
                fgets(address,sizeof(address),stdin);
                address[strcspn(address,"\n")] = 0;
                centerprint("enter 1 to ensure the process:", 0);
                if(wrongans(&ensure) ==1) continue;
                if(ensure==1){
                centerprint("thank you for your order ", 0);
                printf("\n");
                centerprint("the order will arrives in half an hour",0);
                printf("\n");
                design("thank_you.txt", 4);
                design("heart.txt", 4);
                exit(0);
                }else{
                centerprint("No Problem Take Your Time (:",2);
                Sleep(1000);
                firstscreen();
                }
        }
}
}

void Boss_screen(){
    while(1){
    int back_now;
        char buffer[100];
        clearscreen();
        design("boss.txt", 0);
        sprintf(buffer,"Today's sales: %d ", total); //total will be changed
        centerprint(buffer,0);
        printf("\n");
        centerprint("last month sales: 53450$", 0);
        printf("\n");
        centerprint("last month Restaurant expenses and workers' salaries: 36000$", 0);
        printf("\n");
        centerprint("last month profits: 17450$", 0);
        printf("\n");
        centerprint("Staff Summary:", 0);
        printf("\n");
        for (int i = 0; i <staffCount; i++) {
            sprintf(buffer, "%s - working days: %d, Salary: %.2f$, password: %d",
                staff[i].name,
                25 - staff[i].absentdays,
                staff[i].salary,
                staff[i].password);
            centerbutton(buffer, 0);
        }
        centerbutton("0. Back",4);
        centerprint("    Select an option : ", 0);
        if(wrongans(&back_now) ==1)continue;
        if(back_now == 0) firstscreen();
        else centerprint("    Invalid Choice !\n", 4);

    }
}

void staff_screen(){

    while(1){
        int staff_number;
        int staff_password;
        clearscreen();
        design("staff.txt", 0);
        centerbutton("1. Abdulrahman", 0);
        centerbutton("2. Azzam", 0);
        centerbutton("3. Majed", 0);
        centerbutton("4. Nour", 0);
        centerbutton("0. Back",4);
        centerprint("Select an option :",0);
        if(wrongans(&staff_number) ==1) continue;
        if(staff_number==0) firstscreen();
        if(!(staff_number<5 && staff_number>0)) {centerprint("invalid choise",4); Sleep(700); continue;}
        centerprint("Select staff password :",0);
        if(wrongans(&staff_password) ==1) continue;
        if(staff_password == staff[staff_number-1].password){
            clearscreen();
            char buffer[100];
            sprintf(buffer,"welcome %s \n",staff[staff_number-1].name);
            centerprint(buffer,0);
            sprintf(buffer,"last month you absent: %d \n ", staff[staff_number-1].absentdays);
            centerprint(buffer,0);
            sprintf(buffer,"and you salary: %.2f$ \n", staff[staff_number-1].salary);
            centerprint(buffer,0);
            centerprint("to know you salary for this month enter absent days(0-25):\n ", 0);
            int absent_days;
            centerprint("Select an option :",0);
            if(wrongans(&absent_days) ==1) continue;
            if (absent_days >= 0 && absent_days <= MAX_ABSENT_DAY) {
                sprintf(buffer, "your salary for this month:%d$ ", (MAX_ABSENT_DAY - absent_days) * 200);
                centerprint(buffer, 2);
                Sleep(1500);
                firstscreen();
                }
            else {
                centerprint("  Invalid Choice ! Please enter a value between 0 and 25.\n", 4);
                Sleep(700);
            }
            }
        else{

            centerprint("    you are not working here!!!\n", 4);
            Sleep(700);
        }
    }
}

void mode(){
    while(1){
        int mode_choise;
        clearscreen();
        design("mode.txt", 0);
        printf("\n\n");
        centerbutton("1. Boss mode", 4);
        centerbutton("2. staff mode", 0);
        centerbutton("0. Back", 4);
        centerprint("Select mode Number :",0);
        if(wrongans(&mode_choise) ==1) continue;
        if(mode_choise == 1){
            Boss_screen();
        }
        else if(mode_choise == 2){
            staff_screen();
        }
        else if(mode_choise == 0){
            firstscreen();
        }
        else{
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
    }
}

void firstscreen(){
   int choise;

        while (1) {
            clearscreen();
            design("welcome1.txt", 0);
            centerbutton("1. Food", 0);
            design("food.txt",0);
            centerbutton("2. Drinks", 0);
            design("drinks.txt",1);
            centerbutton("3. Desserts", 0);
            design("desserts.txt",5);
            centerbutton("4. Snacks", 0);
            design("snacks.txt",6);
            centerbutton("5. View Cart", 0);
            design("cart.txt",0);
            centerbutton("6. Checkout", 0);
            design("checkout.txt",2);
            centerbutton("7. mode", 0);
            centerbutton("8. Exit", 4);
            centerprint("    Select an option : ", 0);
            if(wrongans(&choise) ==1)continue;


            switch(choise){
                case 1: screens(choise);
                case 2: screens(choise);
                case 3: screens(choise);
                case 4: screens(choise);
                case 5: cartscreen();
                case 6: checkoutscreen();
                case 7: mode();
                case 8: exit(0);
                default:
                    centerprint("    Invalid Choice !\n", 4);
                    Sleep(700);
                              }
        }
}

void add_to_users (char info[MAX_NAME_LENGTH], char filename[MAX_NAME_LENGTH]){
FILE *pf = fopen(filename,"a");
fprintf(pf,info);
fclose(pf);
}

void login_screen(){
    while(1){
    char email[MAX_NAME_LENGTH];
    char targetemail[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    clearscreen();
    centerbutton("LOGIN",2);
    centerbutton("00. Back",4);
    centerprint("Enter Your Email :",0);
    fgets(email,sizeof(email),stdin);
    if(strcmp(email,"00\n")==0)pre_screen();
    int emailfound =0;
    for(int i=0;i<maxusers;i++){
        if(strcmp(email,usersinfo[i].email)==0){emailfound =1; userindex =i; break;}
    }
    if(!emailfound){centerprint("INVALID EMAIL !!",4); Sleep(700); continue;}
    centerprint("Enter Your Password :",0);
    fgets(password,sizeof(password),stdin);
    if(strcmp(password,"00\n")==0)pre_screen();
    if(strcmp(password,usersinfo[userindex].password)==0){centerprint("DONE",2); Sleep(700); firstscreen();}
    else{centerprint("WRONG PASSWORD !!",4); Sleep(700); continue;}
    }
}

void scan_emails(){
FILE *pf = fopen("emails.txt","r");
int i =0;
while(fgets(usersinfo[i].email,sizeof(usersinfo[i].email),pf) !=NULL){
    i++;
    maxusers++;
}
fclose(pf);
}

void scan_usernames(){
FILE *pf = fopen("usernames.txt","r");
int i =0;
while(fgets(usersinfo[i].username,sizeof(usersinfo[i].username),pf) !=NULL){
    i++;
}
fclose(pf);
}

void scan_passwords(){
FILE *pf = fopen("passwords.txt","r");
int i =0;
while(fgets(usersinfo[i].password,sizeof(usersinfo[i].password),pf) !=NULL){
    i++;
}
fclose(pf);
}

void register_screen(){
    while(1){
    char username[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    clearscreen();
centerbutton("Register Screen",2);
centerbutton("00. Back",4);
centerprint("Enter Your username :",0);
fgets(username,sizeof(username),stdin);
if(strcmp(username,"00\n")==0)pre_screen();
centerprint("Enter Your email :",0);
fgets(email,sizeof(email),stdin);
int isregistered =0;
for(int i=0;i<maxusers;i++){
    if(strcmp(email,usersinfo[i].email)==0){
            centerprint("Email is already registered !",4);
    Sleep(700);
    isregistered =1;
    break;
     }
}
   if(isregistered)continue;
if(strcmp(email,"00\n")==0)pre_screen();
centerprint("Enter Your Password :",0);
fgets(password,sizeof(password),stdin);
if(strcmp(password,"00\n")==0)pre_screen();

add_to_users(email,"emails.txt");
add_to_users(username,"usernames.txt");
add_to_users(password,"passwords.txt");
centerbutton("Register Done",2);
Sleep(1000);

scan_emails();
scan_passwords();
scan_usernames();
login_screen();
}
}
void pre_screen(){
    while(1){
clearscreen();
centerbutton("1. LOGIN",0);
centerbutton("2. REGISTER",0);
centerbutton("0. EXIT",4);
centerprint("Select an option :",0);
int choise;
if(wrongans(&choise) ==1)continue;
switch(choise){
case 1 : login_screen();
case 2 : register_screen();
case 0 : exit(0);
default: {centerprint("INVALID CHOISE !!",4); Sleep(700);}
}
    }
}



int main(){
    scan_emails();
    scan_passwords();
    scan_usernames();
    pre_screen();
    return 0;
}//control+z
